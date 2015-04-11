// TankWar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "TankWar.h"

HANDLE hStdOut;
HANDLE hStdIn;
CONSOLE_SCREEN_BUFFER_INFO csbiInitiatWindow;
COORD coSave = { 0, 0 }, coWOLF;
int gameMap[35][60] = { 0 };

int _tmain(int argc, _TCHAR* argv[])
{
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	initializeWindow();
	//mapEditor(&coSave);
	printMap(0);
	printMessage(g_welcomeM, sizeof(g_welcomeM) / sizeof(g_welcomeM[0]));
	initializeTank(false);
	tankMoveTest(isGamePlay,gameInitial,isDualPlayer);
	CloseHandle(hStdOut);
	CloseHandle(hStdIn);
	return 0;
}

bool readMap(char(*filename)[20], int(*pMap)[60])
{
	FILE *ptrFile;
	errno_t errOpenFile;
	errOpenFile = fopen_s(&ptrFile, *filename, "r");
	if (!errOpenFile)
	{
		for (int x = 0; x < 35; x++)
		{
			for (int y = 0; y < 60; y++)
			{
				fscanf_s(ptrFile, "%d,", &pMap[x][y]);
			}
		}
		fscanf_s(ptrFile, "{%d,%d},", &coWOLF.X, &coWOLF.Y);
		fscanf_s(ptrFile, "{enemycount=%d}", &enemyTankCount);
		fclose(ptrFile);
		return true;
	}
	return false;
}

bool initializeWindow()
{
	system("cls");
	SMALL_RECT srInitiatWindow = { 0, 0, 139, 39 };
	GetConsoleScreenBufferInfo(hStdOut, &csbiInitiatWindow);
	csbiInitiatWindow.dwSize.X = 140;
	csbiInitiatWindow.dwSize.Y = 40;
	SetConsoleScreenBufferSize(hStdOut, csbiInitiatWindow.dwSize);
	SetConsoleWindowInfo(hStdOut, true, &srInitiatWindow);
	CONSOLE_CURSOR_INFO cciDrawMap;
	cciDrawMap.bVisible = false;
	cciDrawMap.dwSize = 1;
	SetConsoleCursorInfo(hStdOut, &cciDrawMap);
	return true;
}

void printMessage(char(*pmt)[20], int numOfEle)
{
	COORD coIndi = { 122, 2 };
	GetConsoleScreenBufferInfo(hStdOut, &csbiInitiatWindow);
	coSave = csbiInitiatWindow.dwCursorPosition;
	for (int i = 0; i < numOfEle; i++)
	{
		SetConsoleTextAttribute(hStdOut, tankColor[i]);
		SetConsoleCursorPosition(hStdOut, coIndi);
		printf("%s", *(pmt + i));
		coIndi.Y += 2;
	}
	csbiInitiatWindow.dwCursorPosition = coSave;
	SetConsoleCursorPosition(hStdOut, csbiInitiatWindow.dwCursorPosition);
	SetConsoleTextAttribute(hStdOut, tankColor[8]);
}

bool printMap(int gameLevel)
{
	system("cls");
	if (readMap((g_mapLevel+gameLevel), gameMap))
	{
		for (int x = 0; x < 35; x++)
		{
			for (int y = 0; y < 60; y++)
			{
				switch (gameMap[x][y])
				{
				case OBS:
				{
							printf("¡ö");
							break;
				}
				case BRICK:
				{
							  printf("¨ˆ");
							  break;
				}
				case IRON:
				{
							 printf("¡þ");
							 break;
				}
				case WOLFPACK:
				{
								 printf("§¨");
								 break;
				}
				case EMPTY:
				{
							  printf("  ");
							  break;
				}
				default:
					break;
				}
			}
			printf("\n");
		}

		if (gameLevel > 11)
		{
			gameLevel = 0;
		}
		gameLevel++;
		gameInitial = true;
		return true;
	}

	return false;
}

void printTank(tanks *tank, bool iswipe)
{
	COORD tempTankCo;
	tempTankCo.X = tank->tankPosition.Y * 2;
	tempTankCo.Y = tank->tankPosition.X;
	SetConsoleCursorPosition(hStdOut, tempTankCo);
	if (iswipe)
	{
		printf("  ");
		tankMap[tank->tankPosition.X][tank->tankPosition.Y] = 0;
	}
	else
	{
		SetConsoleTextAttribute(hStdOut, tankColor[tank->tankType - 1]);
		printf("¡õ");
		tankMap[tank->tankPosition.X][tank->tankPosition.Y] = tank->tankID;
		SetConsoleTextAttribute(hStdOut, tankColor[6]);
	}

	for (int i = 0; i < 5; i++)
	{
		tempTankCo.X = tank->tankPosition.Y;
		tempTankCo.Y = tank->tankPosition.X;
		if (iswipe)
		{
			tempTankCo.X += tankDIR[tank->previousIndex][1][i];
			tempTankCo.Y += tankDIR[tank->previousIndex][0][i];
			tankMap[tempTankCo.Y][tempTankCo.X] = 0;
		}
		else
		{
			tempTankCo.X += tankDIR[tank->directionIndex][1][i];
			tempTankCo.Y += tankDIR[tank->directionIndex][0][i];
			tankMap[tempTankCo.Y][tempTankCo.X] = tank->tankID;
		}
		tempTankCo.X *= 2;
		SetConsoleCursorPosition(hStdOut, tempTankCo);
		if (iswipe)
		{
			printf("  ");
		}
		else
		{
			printf("¡ö");
		}
	}
}

void printAmmo(ammos *ammo,bool isOld,bool isWipe)
{
	COORD ammoTempCo;
	if (isOld)
	{
		ammoTempCo.X = ammo->lastCo.Y * 2;
		ammoTempCo.Y = ammo->lastCo.X;
	}
	else
	{
		ammoTempCo.X = ammo->ammoPosition.Y * 2;
		ammoTempCo.Y = ammo->ammoPosition.X;
	}
	SetConsoleCursorPosition(hStdOut, ammoTempCo);
	if (isWipe)
	{
		printf("  ");
		if (isOld)
		{
			ammoMap[ammo->lastCo.X][ammo->lastCo.Y] = 0;
		}
		else
		{
			ammoMap[ammo->ammoPosition.X][ammo->ammoPosition.Y] = 0;
		}
	}
	else
	{
		printf("%s", ammosType[ammo->ammoType/11-1]);
		ammoMap[ammo->ammoPosition.X][ammo->ammoPosition.Y] = ammo->ammoID;
	}
}

void endGame(COORD wolf)
{
	SetConsoleCursorPosition(hStdOut, wolf);
	printf("  ");
}