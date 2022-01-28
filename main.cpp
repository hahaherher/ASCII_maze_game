#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <vector>
using namespace std;


struct sANDe
{
    COORD s;
    COORD e;
    COORD result_position;
    vector<COORD> walls;
    vector<COORD> stars;
};
sANDe print_maze(char way[],HANDLE color);
bool hitWall(sANDe se,CONSOLE_SCREEN_BUFFER_INFO b_info,char direction);
bool hitStar(sANDe se,CONSOLE_SCREEN_BUFFER_INFO info,char direction);

int main()
{
    system("chcp 437");
    HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);
    //print guide
    cout<<endl;
    SetConsoleTextAttribute(color, 0xC7);//end point, light red
    cout<<"E";
    SetConsoleTextAttribute(color, 0x07);//black
    cout<<":end point"<<endl;
    SetConsoleTextAttribute(color, 0xE6);//yellow
    cout<<"*";
    SetConsoleTextAttribute(color, 0x07);//black
    cout<<":star"<<endl<<endl;

    cout<<"input \"R\" to restart from start point"<<endl;
    cout<<"input \"up arrow\" to go up"<<endl;
    cout<<"input \"down arrow\" to go down"<<endl;
    cout<<"input \"left arrow\" to go left"<<endl;
    cout<<"input \"right arrow\" to go right"<<endl<<endl;
    cout<<"Collect the stars as more as you can :-) !!"<<endl<<endl;

    //print maze1;
    sANDe se1 = print_maze("maze1.txt",color);
    SetConsoleCursorPosition(color, se1.s);
    //control cursor
    int ch;//save input button
    COORD ori_start_position = se1.s;
    int star=0;//save the number of star player collect
    while (1)
    {
        CONSOLE_SCREEN_BUFFER_INFO b_info;
        GetConsoleScreenBufferInfo(color, &b_info);
        //set cursor background color
        SetConsoleTextAttribute(color, 0x4e);//red
        cout<<" ";
        SetConsoleCursorPosition(color, se1.s);

        if(b_info.dwCursorPosition.X==se1.e.X&&b_info.dwCursorPosition.Y==se1.e.Y)
        {
            SetConsoleCursorPosition(color, se1.result_position);
            SetConsoleTextAttribute(color, 0x4e);//red
            cout<<"you win!"<<endl<<"you get "<<star<<" stars!"<<endl;
            break;
        }
        ch = getch();
        switch (ch)//檢測輸入鍵
        {
        case 114: //R
            SetConsoleTextAttribute(color, 0x07);//black
            cout<<" ";
            SetConsoleCursorPosition(color, se1.s);
            se1.s = ori_start_position;
            break;
        case 72://UP button
            if(hitWall(se1,b_info,'u')==false)
            {
                if(hitStar(se1,b_info,'r')==true){
                    star++;
                }
                //set background color after cursor leave
                SetConsoleTextAttribute(color, 0x07);//black
                cout<<" ";
                SetConsoleCursorPosition(color, se1.s);
                se1.s.Y--;

            }
            break;
        case 80://DOWN button
            if(hitWall(se1,b_info,'d')==false)
            {
                if(hitStar(se1,b_info,'r')==true){
                    star++;
                }
                //set background color after cursor leave
                SetConsoleTextAttribute(color, 0x07);//black
                cout<<" ";
                SetConsoleCursorPosition(color, se1.s);
                se1.s.Y++;
            }
            break;
        case 77://RIGHT button
            if(hitWall(se1,b_info,'r')==false)
            {
                if(hitStar(se1,b_info,'r')==true){
                    star++;
                }
                //set background color after cursor leave
                SetConsoleTextAttribute(color, 0x07);//black
                cout<<" ";
                SetConsoleCursorPosition(color, se1.s);
                se1.s.X++;
            }
            break;
        case 75://LEFT button
            if(hitWall(se1,b_info,'l')==false)
            {
                if(hitStar(se1,b_info,'r')==true){
                    star++;
                }
                //set background color after cursor leave
                SetConsoleTextAttribute(color, 0x07);//black
                cout<<" ";
                SetConsoleCursorPosition(color, se1.s);
                se1.s.X--;
            }
            break;
        }

        SetConsoleCursorPosition(color,se1.s);
    }
    system("pause");
    return 0;
}
sANDe print_maze(char way[],HANDLE color)
{
    sANDe se;
    fstream f_maze;
    f_maze.open(way,ios::in);//read mode

    while(!f_maze.eof())
    {
        char line[256];
        f_maze.getline(line,256,'\n');//getline(char *,int,char) 表示該行字元達到256個或遇到換行就結束

        for(int i=0; i<strlen(line); i++)
        {
            char temp = line[i];
            if(temp=='S')
            {
                SetConsoleTextAttribute(color, 0x67);//start point, yellow
                //save start point
                CONSOLE_SCREEN_BUFFER_INFO b_info;
                GetConsoleScreenBufferInfo(color, &b_info);
                se.s= b_info.dwCursorPosition;
                //set edges
                COORD temp;
                temp.X = b_info.dwCursorPosition.X;
                temp.Y = b_info.dwCursorPosition.Y-1;
                se.walls.push_back(temp);
                temp.X = b_info.dwCursorPosition.X-1;
                se.walls.push_back(temp);
                temp.X = b_info.dwCursorPosition.X+1;
                se.walls.push_back(temp);
            }
            else if(temp=='E')
            {
                SetConsoleTextAttribute(color, 0xC7);//End point, light red
                //save end point
                CONSOLE_SCREEN_BUFFER_INFO b_info;
                GetConsoleScreenBufferInfo(color, &b_info);
                se.e= b_info.dwCursorPosition;
                //set edges
                COORD temp;
                temp.X = b_info.dwCursorPosition.X+1;
                temp.Y = b_info.dwCursorPosition.Y-1;
                se.walls.push_back(temp);
                temp.Y = b_info.dwCursorPosition.Y+1;
                se.walls.push_back(temp);
            }
            else if(temp=='>')
            {
                SetConsoleTextAttribute(color, 0x77);//normal wall, white
                //save wall point
                CONSOLE_SCREEN_BUFFER_INFO b_info;
                GetConsoleScreenBufferInfo(color, &b_info);
                se.walls.push_back(b_info.dwCursorPosition);
            }else if(temp=='*'){
                SetConsoleTextAttribute(color, 0xE6);
                //save star point
                CONSOLE_SCREEN_BUFFER_INFO b_info;
                GetConsoleScreenBufferInfo(color, &b_info);
                se.stars.push_back(b_info.dwCursorPosition);
            }
            cout<<temp;
            SetConsoleTextAttribute(color, 0x07);//space, black
        }
        cout<<endl;
    }
    cout<<endl;
    //save result position
    CONSOLE_SCREEN_BUFFER_INFO b_info;
    GetConsoleScreenBufferInfo(color, &b_info);
    se.result_position = b_info.dwCursorPosition;
    f_maze.close();
    return se;
}
bool hitWall(sANDe se,CONSOLE_SCREEN_BUFFER_INFO info,char direction)
{
    short x = info.dwCursorPosition.X;
    short y = info.dwCursorPosition.Y;
    int d_x=0,d_y=0;
    switch(direction)
    {
    case 'u':
        d_y=-1; //up
        break;
    case 'd':
        d_y=1; //down
        break;
    case 'r':
        d_x=1; //right
        break;
    case 'l':
        d_x=-1; //left
        break;
    }
    for(int i=0; i<se.walls.size(); i++)
    {
        if(y+d_y==se.walls[i].Y&&x+d_x==se.walls[i].X)
        {
            return true;
        }
    }
    return false;
}
bool hitStar(sANDe se,CONSOLE_SCREEN_BUFFER_INFO info,char direction)
{
    short x = info.dwCursorPosition.X;
    short y = info.dwCursorPosition.Y;
    int d_x=0,d_y=0;
    switch(direction)
    {
    case 'u':
        d_y=-1; //up
        break;
    case 'd':
        d_y=1; //down
        break;
    case 'r':
        d_x=1; //right
        break;
    case 'l':
        d_x=-1; //left
        break;
    }
    for(int i=0; i<se.stars.size(); i++)
    {
        if(y+d_y==se.stars[i].Y&&x+d_x==se.stars[i].X)
        {
            return true;
        }
    }
    return false;
}
