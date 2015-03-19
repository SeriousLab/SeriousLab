// Minesweep.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
time_t pTime;
int mineMap[20][26] = { 0 };
bool flagMap[20][26] = { 0 };
bool openedMap[20][26] = { 0 };
void generateMap();
void printMap();
bool markIndicator();
bool currentPosition(int x, int y, WORD color);
void openSurrand(int x, int y);
void gameOver(int x, int y);
void printCurrentCell(int x, int y);
void gamePlay();


const int nMine = 80;
const int xM[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
const int yM[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int counter = 0;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
int mineCount = 0;
HANDLE hStdin;
INPUT_RECORD irInBuf[128];
DWORD cNumRead;
DWORD saveOldMode;
COORD exitCord = { 0, 20 };


int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned int)time(&pTime));
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hStdin, &saveOldMode);
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	generateMap();
	SetConsoleMode(hStdin, ENABLE_MOUSE_INPUT);
	markIndicator();
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 26; y++)
		{
			printf("■");
		}
		printf("\n");
	}
	gamePlay();
	//printMap();


	return 0;
}

void generateMap(){
	for (int n = 1; n < nMine; n++)
	{
		mineMap[rand() % 20][rand() % 26] = 99;         //地图里随机99个位置生成雷，小概率情况下会随机到相同的位置，少一俩雷将就玩吧；
	}
}

//测试地雷标记输出
//void printMap(){
//	for (int x = 0; x < 20; x++)
//	{
//		for (int y = 0; y < 26; y++)
//		{
//			if (mineMap[x][y] == 0)
//			{
//				currentPosition(y, x, csbiInfo.wAttributes);
//				printf("■");
//			}
//			if ((mineMap[x][y] >= 1) && (mineMap[x][y] <= 8))
//			{
//				switch (mineMap[x][y])
//				{
//				case 1:
//				{
//						  currentPosition(y, x, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
//						  printf("１");
//						  break;
//				}
//				case 2:
//				{
//						  currentPosition(y, x, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
//						  printf("２");
//						  break;
//				}
//				case 3:
//				{
//						  currentPosition(y, x, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
//						  printf("３");
//						  break;
//				}
//				case 4:
//				{
//						  currentPosition(y, x, FOREGROUND_RED | FOREGROUND_INTENSITY);
//						  printf("４");
//						  break;
//				}
//				case 5:
//				{
//						  currentPosition(y, x, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
//						  printf("５");
//						  break;
//				}
//				case 6:
//				{
//						  currentPosition(y, x, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
//						  printf("６");
//						  break;
//				}
//				case 7:
//				{
//						  currentPosition(y, x, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
//						  printf("７");
//						  break;
//				}
//				case 8:
//				{
//						  currentPosition(y, x, csbiInfo.wAttributes);
//						  printf("８");
//						  break;
//				}
//				default:
//					break;
//				}
//			}
//			if (mineMap[x][y] == 99)
//			{
//				currentPosition(y, x, csbiInfo.wAttributes);
//				//printf("¤");
//				printf("■");
//			}
//		}
//		printf("\n");
//	}
//}

bool markIndicator(){
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 26; y++)
		{
			counter = 0;
			for (int n = 0; n < 8; n++)
			{
				if (mineMap[x][y] == 99)
				{
					break;				//判断是雷就跳过；
				}
				else
				{
					if (x + xM[n]<0 || x + xM[n]>19 || y + yM[n]<0 || y + yM[n]>25)
					{
						continue;
					}
					if (mineMap[x + xM[n]][y + yM[n]] == 99)
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

bool currentPosition(int x, int y, WORD color)
{
	CONSOLE_CURSOR_INFO CurInfo;

	COORD cPos;
	cPos.X = x * 2;
	cPos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cPos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	CurInfo.dwSize = 1;
	CurInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	return TRUE;
}

bool isFlaged(int x, int y){
	if (flagMap[x][y] == 1)
	{
		return true;
	}
	return false;
}

bool isMine(int x, int y){
	if (mineMap[x][y] == 99)
	{
		return true;
	}
	return false;
}

bool isOpen(int x, int y){
	if (openedMap[x][y] == 1)
	{
		return true;
	}
	return false;
}

void openSurrand(int x, int y){
	openedMap[x][y] = 1;
	printCurrentCell(x, y);
	for (int n = 1; n < 8; n += 2)
	{
		if (x + xM[n]<0 || y + yM[n]<0 || x + xM[n]>19 || y + yM[n]>25)
		{
			continue;
		}
		if (mineMap[x + xM[n]][y + yM[n]] == 0)
		{
			if (!isFlaged(x + xM[n], y + yM[n]))
			{
				if (!isOpen(x + xM[n], y + yM[n]))
				{
					openedMap[x + xM[n]][y + yM[n]] = 1;
					currentPosition(y + yM[n], x + xM[n], csbiInfo.wAttributes);
					printf("  ");
					openSurrand(x + xM[n], y + yM[n]);
				}
			}
		}
		else if (mineMap[x + xM[n]][y + yM[n]] == 99)
		{
			break;
		}
		else
		{
			if (!isFlaged(x + xM[n], y + yM[n]))
			{
				if (!isOpen(x + xM[n], y + yM[n]))
				{
					openedMap[x + xM[n]][y + yM[n]] = 1;
					printCurrentCell(x + xM[n], y + yM[n]);
					openSurrand(x + xM[n], y + yM[n]);
				}
			}

			break;
		}

	}
}

//测试用的
// void printOpenedMap(){
// 	for (int x = 0; x < 20;x++)
// 	{
// 		for (int y = 0; y < 26;y++)
// 		{
// 			if (openedMap[x][y] == 1)
// 			{
// 				printf("  ");
// 			}
// 			else
// 				printf("■");
// 		}
// 		printf("\n");
// 	}
// }

void gamePlay(){
	while (true)
	{
		if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead))
		{
			continue;
		}
		for (unsigned int i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].Event.MouseEvent.dwButtonState)
			{
			case 1:
			{
					  if (isOpen(irInBuf[i].Event.MouseEvent.dwMousePosition.Y, irInBuf[i].Event.MouseEvent.dwMousePosition.X / 2))
					  {
						  break;
					  }
					  if (isFlaged(irInBuf[i].Event.MouseEvent.dwMousePosition.Y, irInBuf[i].Event.MouseEvent.dwMousePosition.X / 2))
					  {
						  break;
					  }
					  if (mineMap[irInBuf[i].Event.MouseEvent.dwMousePosition.Y][irInBuf[i].Event.MouseEvent.dwMousePosition.X / 2] == 99)
					  {
						  gameOver(irInBuf[i].Event.MouseEvent.dwMousePosition.X, irInBuf[i].Event.MouseEvent.dwMousePosition.Y);
						  return;
					  }
					  else
					  {
						  openSurrand(irInBuf[i].Event.MouseEvent.dwMousePosition.Y, irInBuf[i].Event.MouseEvent.dwMousePosition.X / 2);
						  break;
					  }
			}
			case 2:
			{
					  if (isFlaged(irInBuf[i].Event.MouseEvent.dwMousePosition.Y, irInBuf[i].Event.MouseEvent.dwMousePosition.X / 2))
					  {
						  flagMap[irInBuf[i].Event.MouseEvent.dwMousePosition.Y][irInBuf[i].Event.MouseEvent.dwMousePosition.X / 2] = 0;
						  currentPosition(irInBuf[i].Event.MouseEvent.dwMousePosition.X / 2, irInBuf[i].Event.MouseEvent.dwMousePosition.Y, csbiInfo.wAttributes);
						  printf("■");
						  break;
					  }
					  else
					  {
						  flagMap[irInBuf[i].Event.MouseEvent.dwMousePosition.Y][irInBuf[i].Event.MouseEvent.dwMousePosition.X / 2] = 1;
						  currentPosition(irInBuf[i].Event.MouseEvent.dwMousePosition.X / 2, irInBuf[i].Event.MouseEvent.dwMousePosition.Y, FOREGROUND_RED |FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
						  printf("♀");
						  break;
					  }
			}
			default:
				break;
			}

		}
	}
}

void gameOver(int x, int y){
	for (int g = 0; g < 20; g++)
	{
		for (int h = 0; h < 26; h++)
		{
			if (mineMap[g][h] == 99)
			{
				printCurrentCell(g, h);
			}
		}
	}
	currentPosition(x / 2, y, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	printf("¤");
	currentPosition(0, 20, csbiInfo.wAttributes);
	return;
}

void printCurrentCell(int x, int y){
	switch (mineMap[x][y])
	{
	case 1:
	{
			  currentPosition(y, x, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			  printf("１");
			  break;
	}
	case 2:
	{
			  currentPosition(y, x, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			  printf("２");
			  break;
	}
	case 3:
	{
			  currentPosition(y, x, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			  printf("３");
			  break;
	}
	case 4:
	{
			  currentPosition(y, x, FOREGROUND_RED | FOREGROUND_INTENSITY);
			  printf("４");
			  break;
	}
	case 5:
	{
			  currentPosition(y, x, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			  printf("５");
			  break;
	}
	case 6:
	{
			  currentPosition(y, x, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			  printf("６");
			  break;
	}
	case 7:
	{
			  currentPosition(y, x, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			  printf("７");
			  break;
	}
	case 8:
	{
			  currentPosition(y, x, csbiInfo.wAttributes);
			  printf("８");
			  break;
	}
	case 99:
	{
			   currentPosition(y, x, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			   printf("¤");
			   break;
	}
	case 0:
	{
			  currentPosition(y, x, csbiInfo.wAttributes);
			  printf("  ");
			  break;
	}
	default:
		break;
	}
}