// Minesweep.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
time_t pTime;
int mineMap[20][26] = { 0 };
bool flagMap[20][26] = { 0 };
void generateMap();
void printMap();
bool markIndicator();
bool currentPosition(int x, int y, WORD color);

const int nMine = 99;
const int xM[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
const int yM[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int counter = 0;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned int)time(&pTime));
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	generateMap();
	markIndicator();
	printMap();
	return 0;
}

void generateMap(){
	for (int n = 1; n < nMine; n++)
	{
		mineMap[rand() % 18 + 1][rand() % 24 + 1] = 99;         //地图里随机99个位置生成雷，小概率情况下会随机到相同的位置，少一俩雷将就玩吧；
	}
}

void printMap(){
	for (int x = 0; x < 20;x++)
	{
		for (int y = 0; y < 26;y++)
		{
			if (mineMap[x][y]==0)
			{
				currentPosition(y, x, csbiInfo.wAttributes);
				printf("■");
			}
			if ((mineMap[x][y]>=1)&&(mineMap[x][y]<=8))
			{
				switch (mineMap[x][y])
				{
				case 1:
				{
						  currentPosition(y, x, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED|FOREGROUND_INTENSITY);
						  printf("１");
						  break;
				}
				case 2:
				{
						  currentPosition(y, x, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
						  printf("２");
						  break;
				}
				case 3:
				{
						  currentPosition(y, x, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
						  printf("３");
						  break;
				}
				case 4:
				{
						  currentPosition(y, x, FOREGROUND_RED|FOREGROUND_INTENSITY);
						  printf("４");
						  break;
				}
				case 5:
				{
						  currentPosition(y, x, FOREGROUND_BLUE | FOREGROUND_GREEN|FOREGROUND_INTENSITY);
						  printf("５");
						  break;
				}
				case 6:
				{
						  currentPosition(y, x, FOREGROUND_BLUE | FOREGROUND_RED|FOREGROUND_INTENSITY);
						  printf("６");
						  break;
				}
				case 7:
				{
						  currentPosition(y, x, FOREGROUND_GREEN | FOREGROUND_RED|FOREGROUND_INTENSITY);
						  printf("７");
						  break;
				}
				case 8:
				{
						  currentPosition(y, x, csbiInfo.wAttributes);
						  printf("８");
						  break;
				}
				default:
					break;
				}
			}
			if (mineMap[x][y]==99)
			{
				currentPosition(y, x, csbiInfo.wAttributes);
				printf("¤");
			}
		}
		printf("\n");
	}
}

bool markIndicator(){
	for (int x = 0; x < 20;x++)
	{
		for (int y = 0; y < 26;y++)
		{
			counter = 0;
			for (int n = 0; n < 8;n++)
			{
				if (mineMap[x][y]==99)
				{
					break;				//判断是雷就跳过；
				}
				else
				{
					if (mineMap[x+xM[n]][y+yM[n]]==99)
					{
						counter++;     //遍历周围八个格子，有雷计数器+1；
					}
				}
				mineMap[x][y] = counter;    //输出计数器的值；
			}
		}
	}
	return true;
}

bool currentPosition(int x, int y,WORD color)
{
	CONSOLE_CURSOR_INFO CurInfo;

	COORD cPos;
	cPos.X = x * 2;
	cPos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cPos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	CurInfo.dwSize = 1;
	CurInfo.bVisible = true;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	return TRUE;
}