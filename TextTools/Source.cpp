#include <string>
#include <iostream>
#include "Coordinates.h"
#include "TextDraw.h"
#include "TextArt.h"
#include <fstream>
#include "MySound.h"
using namespace std;


class point
{
public:
    int x, y;

};


class Stack
{
public:
    point arr[10000000];
    int H=0;
    void push(int x, int y)
    {
        arr[H].x = x;
        arr[H].y = y;
        H++;              //move new Header position
    }
    point pop()
    {
        H--;            //Header is lower due to popping 
        return arr[H];
    }

    point peek()       //Did I come from there?
    {
        return arr[H - 1];
    }


};


BoardData board[25][50];
Coordinates coor;
Coordinates b;
int xpos, ypos;
Stack S;
int points;

bool IDidNOTComeFrom(int x, int y)    //returns true if (x,y) if different from top of stack 
{
    point p = S.peek();
    if (x != p.x || y != p.y)
        return true;
    else
        return false;
}

void MoveMouse()
{
    if (((board[ypos][xpos + 1].symbol == 32) || (board[ypos][xpos+1].color == 13)) && IDidNOTComeFrom(xpos + 1, ypos))  //is right empty
    {
        S.push(xpos, ypos);
        xpos++;
        if (board[ypos][xpos].color == 13)
        {
            points++;
            board[ypos][xpos].symbol == 32;
          
        }
  
    }
    else if (((board[ypos-1][xpos ].symbol == 32) || (board[ypos-1][xpos ].color == 13)) && IDidNOTComeFrom(xpos, ypos - 1))    //up 
    {
        S.push(xpos, ypos);
        ypos--;//
        if (board[ypos][xpos].color == 13)
        {
            points++;
            board[ypos][xpos].symbol == 32;

        }
    }
    else if (((board[ypos + 1][xpos].symbol == 32) || (board[ypos + 1][xpos].color == 13)) && IDidNOTComeFrom(xpos, ypos + 1))    //down
    {
        S.push(xpos, ypos);
        ypos++;
        if (board[ypos][xpos].color == 13)
        {
            points++;
            board[ypos][xpos].symbol == 32;

        }

    }
    else if (((board[ypos][xpos-1].symbol == 32) || (board[ypos][xpos-1].color == 13)) && IDidNOTComeFrom(xpos - 1, ypos))      //left
    {
        S.push(xpos, ypos);
        xpos--;
        if (board[ypos][xpos].color == 13)
        {
            points++;
            board[ypos][xpos].symbol == 32;

        }

    }
    

    else
    {
        board[ypos][xpos].symbol = 1;
        point P;
        P = S.pop();
        xpos = P.x;
        ypos = P.y;
    }

}

void LoadMaze(string filename, BoardData Interface[50][50])
{
    int rows, columns;
    ifstream input(filename);
    if (!input)
        return;
    input >> rows >> columns;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            input >> Interface[i][j].symbol >> Interface[i][j].color >> Interface[i][j].bgcolor;
    }
    input.close();
}

void DisplayMaze(int x, int y, int rows, int columns, BoardData Interface[50][50])
{
    Coordinates C;
    for (int i =0 ; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            C.gotoxy(j + x, i + y);
            C.setForeGroundAndBackGroundColor(Interface[i][j].color, Interface[i][j].bgcolor);
            cout << char(Interface[i][j].symbol);
        }
    }
}



void DisplayMouse()
{
 
    coor.gotoxy(xpos, ypos);
    cout << "X";

}

void HideMouse()
{
   
    coor.gotoxy(xpos, ypos);
    cout << " ";
}


void main()
{


    LoadMaze("files/Maze.txt", board); //loads maze design from file 
    DisplayMaze(0, 0, 25, 50, board);  

    xpos = 0;
    ypos = 1;

   DisplayMouse();
    while (!((xpos==49)&& (ypos == 19)))
    {
        coor.ShowConsoleCursor(false);
        DisplayMouse();
        Sleep(45);
        HideMouse();
        MoveMouse();
       


    }
  
    MySound S;
    S.Play(L"files/Ta Da-Windows.wav", NULL, SND_LOOP);
    b.gotoxy(10, 10);
    cout << "Total Points:" << points;
    while (1);

}



