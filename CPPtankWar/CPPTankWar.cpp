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
#include <vector>
#include "Tank.h"
#include "Cannon.h"

using std::vector;

bool exitTest;
bool isINGAME;
bool isEditor;
bool isMistMode;
int(*pDefaultMap)[80];
vector<COORD> vecPortal;
vector<CTank> vecTank;
vector<CCannon> vecCan;
HANDLE hOut;
HANDLE hIn;
int tankPOSmap[40][80] = { 0 };

int _tmain(int argc, _TCHAR* argv[])
{
	exitTest = false;
	isINGAME = true;
	INPUT_RECORD irGameMode[128];
	DWORD gameMODE;
	time_t pTime;
	srand((unsigned int)time(&pTime));
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	drawWindow(hIn, hOut);
	tuiPOPUP gameWelcom(welcomMessage, _countof(welcomMessage));
	gameWelcom.popUP();
	tuiPOPUP gameOperationInfo(gamePlayinfo, _countof(gamePlayinfo));

	initialPreDefinedMaps();

	while (!exitTest)
	{
		ReadConsoleInput(hIn, irGameMode, 128, &gameMODE);
		for (unsigned int i = 0; i < gameMODE; i++)
		{
			if (irGameMode[i].Event.KeyEvent.bKeyDown)
			{

				switch (irGameMode[i].Event.KeyEvent.wVirtualKeyCode)
				{
				case 0x31:case VK_NUMPAD1:
				{
							  gameOperationInfo.popUP();
							  Sleep(3000);
							  isINGAME = true;
							  gamePlay(hIn, hOut, false);
							  gameWelcom.popUP();
							  break;
				}
				case 0x32:case VK_NUMPAD2:
				{
							  gameOperationInfo.popUP();
							  Sleep(3000);
							  isINGAME = true;
							  gamePlay(hIn, hOut, true);
							  gameWelcom.popUP();
							  break;
				}
				case 0x33:case VK_NUMPAD3:
				{
							  break;
				}
				case 0x34:case VK_NUMPAD4:
				{
							  break;
				}
				case 0x35:case VK_NUMPAD5:
				{
							  break;
				}
				case 0x36:case VK_NUMPAD6:
				{
							  isEditor = true;
							  mapEditor(hIn, hOut);
							  gameWelcom.popUP();
							  break;
				}
				case 0x37:case VK_NUMPAD7:
				{
							  break;
				}
				case 0x38:case VK_NUMPAD8:
				{
							  break;
				}
				case 0x39:case VK_NUMPAD9:
				{
							  break;
				}
				case VK_ESCAPE:
				{
								  COORD exitTemp = { 0, 0 };
								  for (int i = 0; i < 40; i++)
								  {
									  exitTemp.Y = i;
									  FillConsoleOutputAttribute(hOut, 0, 160, exitTemp, &gameMODE);
								  }
								  CloseHandle(hIn);
								  CloseHandle(hOut);
								  return 0;
				}
				default:
					break;
				}
			}
		}
	}
	/*int tttt = 0;
	std::cin >> tttt;*/
	//drawMap(g_map_watchOnly, hOut);
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
			if (pMap[x][y] == MINE)
			{
				continue;
			}
			if (pMap[x][y] == PORTAL)
			{
				COORD portalCO = { y*2, x };
				vecPortal.push_back(portalCO);
			}
			COORD temp = { 2 * y, x };
			WriteConsoleOutputAttribute(hOUT, &wallColor[pMap[x][y] / 11111 % 10], 1, temp, &dwDRAWnRW);
			WriteConsoleOutputCharacter(hOUT, wallType[(pMap[x][y] / 11111) % 10], 1, temp, &dwDRAWnRW);
			temp.X++;
			WriteConsoleOutputAttribute(hOUT, &wallColor[pMap[x][y] / 11111 % 10], 1, temp, &dwDRAWnRW);
		}
	}
}

void gamePlay(HANDLE hIN, HANDLE hOUT, bool isDualPlayer)
{
	pDefaultMap = g_map_mineField;
	INPUT_RECORD irGame[128];
	DWORD gameNUM;
	drawMap(pDefaultMap, hOUT);
	SetConsoleActiveScreenBuffer(hOUT);
	COORD playerOneBirth = { 10, 4 };
	for (int i = 0; i < 6; i++)
	{
		CTank temp(i % 4, playerOneBirth, i + 1, i < 2 ? true : false, i < 2 ? false : true, i + 1);
		vecTank.push_back(temp);
	}
	//CTank playerOne(UP, playerOneBirth, 1, true, false, 1);

	while (isINGAME)
	{
		for (unsigned int i = 0; i < vecTank.size();i++)
		{
			if (vecTank[i].m_computerControl)
			{
				vecTank[i].tankMove(rand() % 4);
				if (!vecTank[i].m_isAlive)
				{
					vecTank.erase(vecTank.begin() + i);
				}
			}
		}
		Sleep(250 / (vecTank.size() + 1));
		if (!_kbhit())
		{
			continue;
		}
		ReadConsoleInput(hIN, irGame, 128, &gameNUM);
		for (unsigned int i = 0; i < gameNUM; i++)
		{
			if (irGame[i].Event.KeyEvent.bKeyDown)
			{
				switch (irGame[i].Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_UP:
				{
							  vecTank[0].tankMove(UP);
							  break;
				}
				case VK_DOWN:
				{
								vecTank[0].tankMove(DOWN);
								break;
				}
				case VK_LEFT:
				{
								vecTank[0].tankMove(LEFT);
								break;
				}
				case VK_RIGHT:
				{
								 vecTank[0].tankMove(RIGHT);
								 break;
				}
				case VK_SPACE:
				{
								 break;
				}
				case 0x57:
				{
							 if (isDualPlayer)
							 {
								 ;
							 }
							 break;
				}
				case 0x53:
				{
							 if (isDualPlayer)
							 {
								 ;
							 }
							 break;
				}
				case 0x41:
				{
							 if (isDualPlayer)
							 {
								 ;
							 }
							 break;
				}
				case 0x44:
				{
							 if (isDualPlayer)
							 {
								 ;
							 }
							 break;
				}
				case VK_ESCAPE:
				{
								  isINGAME = false;
								  break;
				}
				case VK_TAB:
				{

				}
				default:
					break;
				}
			}
		}
	}
}

void gameLayerSWAP()
{

}

void setDefaultMap()
{

}

