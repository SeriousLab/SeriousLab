// CPPTankWar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include "mapEditor.h"
#include "CPPTankWar.h"
#include <stdlib.h>
#include <time.h>
#include "Wall.h"
#include "tuiPOPUP.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	time_t pTime;
	srand((unsigned int)time(&pTime));
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	drawWindow(hIn, hOut);
	tuiPOPUP gameWelcom(welcomMessage, _countof(welcomMessage));
	gameWelcom.popUP();
	int tttt = 0;
	std::cin >> tttt;
	initialPreDefinedMaps();
	drawMap(g_map_watchOnly, hOut);
	//mapEditor(hIn, hOut);
	CloseHandle(hIn);
	CloseHandle(hOut);
	return 0;
}

void drawWindow(HANDLE hIN, HANDLE hOUT)
{
	CONSOLE_FONT_INFOEX cfiGame;
	cfiGame.cbSize = sizeof cfiGame;
	cfiGame.nFont = 11;
	cfiGame.dwFontSize.X = 0;
	cfiGame.dwFontSize.Y = 14;
	cfiGame.FontFamily = 54;
	cfiGame.FontWeight = 400;
	wcscpy_s(cfiGame.FaceName, L"ÐÂËÎÌå");
	SetCurrentConsoleFontEx(hOUT, TRUE, &cfiGame);
	SMALL_RECT srWindow = { 0, 0, 159, 39 };
	COORD csbSize = { 160, 40 };
	SetConsoleScreenBufferSize(hOUT, csbSize);
	SetConsoleWindowInfo(hOUT, true, &srWindow);
	CONSOLE_CURSOR_INFO cciMAP;
	cciMAP.bVisible = FALSE;
	cciMAP.dwSize = 1;
	SetConsoleCursorInfo(hOUT, &cciMAP);
	MoveWindow(GetConsoleWindow(), 20, 20, 1140, 683, TRUE);
	SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 20, 20, 1140, 683, SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOSENDCHANGING | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOZORDER);
}

void drawMap(int(*pMap)[80], HANDLE hOUT)
{
	DWORD dwDRAWnRW = 0;
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 80; y++)
		{
			if (pMap[x][y]==MINE)
			{
				continue;
			}
			COORD temp = { 2 * y, x };
			WriteConsoleOutputAttribute(hOUT, &wallColor[pMap[x][y] / 11111 % 10], 1, temp, &dwDRAWnRW);
			WriteConsoleOutputCharacter(hOUT, wallType[(pMap[x][y] / 11111) % 10], 1, temp, &dwDRAWnRW);
			temp.X++;
			WriteConsoleOutputAttribute(hOUT, &wallColor[pMap[x][y] / 11111 % 10], 1, temp, &dwDRAWnRW);
		}
	}
}