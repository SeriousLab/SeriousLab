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
bool isMapSelect;
bool isWatchOnly;
int(*pDefaultMap)[80];
vector<COORD> vecPortal;
vector<CTank> vecTank;
vector<CCannon> vecCan;
HANDLE hOut;
HANDLE hIn;
int tankPOSmap[40][80] = { 0 };
int player1LifeCount = 3;
int totalEnemyCount = 50;

int _tmain(int argc, _TCHAR* argv[])
{
	exitTest = false;
	isINGAME = true;
	isMistMode = false;
	isWatchOnly = false;
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
	pDefaultMap = g_map_inTheJungle;
	while (!exitTest)
	{
		time_t demoTest;
		time(&demoTest);
		if (demoTest - pTime > 7)
		{
			demoPlay();
			time(&pTime);
			pDefaultMap = g_map_inTheJungle;
			gameWelcom.popUP();
			vecTank.clear();
			vecCan.clear();
			vecPortal.clear();
		}
		if (!_kbhit())
		{
			continue;
		}
		time(&pTime);
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
							  time(&pTime);
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
							  isMapSelect = true;
							  mapSelect();
							  gameWelcom.popUP();
							  time(&pTime);
							  break;
				}
				case 0x34:case VK_NUMPAD4:
				{
							  unFinished();
							  time(&pTime);
							  gameWelcom.popUP();
							  break;
				}
				case 0x35:case VK_NUMPAD5:
				{
							  unFinished();
							  time(&pTime);
							  gameWelcom.popUP();
							  break;
				}
				case 0x36:case VK_NUMPAD6:
				{
							  isEditor = true;
							  mapEditor(hIn, hOut);
							  pDefaultMap = rawMap;
							  gameWelcom.popUP();
							  time(&pTime);
							  break;
				}
				case 0x37:case VK_NUMPAD7:
				{
							  unFinished();
							  gameWelcom.popUP();
							  time(&pTime);
							  break;
				}
				case 0x38:case VK_NUMPAD8:
				{
							  isMistMode = true;
							  gameOperationInfo.popUP();
							  Sleep(3000);
							  isINGAME = true;
							  gamePlay(hIn, hOut, true);
							  gameWelcom.popUP();
							  time(&pTime);
							  break;
				}
				case 0x39:case VK_NUMPAD9:
				{
							  unFinished();
							  time(&pTime);
							  gameWelcom.popUP();
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
				COORD portalCO = { y * 2, x };
				vecPortal.push_back(portalCO);
			}
			if (isMistMode)
			{
				COORD temp = { 2 * y, x };
				WriteConsoleOutputAttribute(hOUT, &wallColor[EMPTY], 1, temp, &dwDRAWnRW);
				WriteConsoleOutputCharacter(hOUT, wallType[EMPTY], 1, temp, &dwDRAWnRW);
				temp.X++;
				WriteConsoleOutputAttribute(hOUT, &wallColor[EMPTY], 1, temp, &dwDRAWnRW);
			}
			else
			{
				COORD temp = { 2 * y, x };
				WriteConsoleOutputAttribute(hOUT, &wallColor[pMap[x][y] / 11111 % 10], 1, temp, &dwDRAWnRW);
				WriteConsoleOutputCharacter(hOUT, wallType[(pMap[x][y] / 11111) % 10], 1, temp, &dwDRAWnRW);
				temp.X++;
				WriteConsoleOutputAttribute(hOUT, &wallColor[pMap[x][y] / 11111 % 10], 1, temp, &dwDRAWnRW);
			}
		}
	}
}

void gamePlay(HANDLE hIN, HANDLE hOUT, bool isDualPlayer)
{
	INPUT_RECORD irGame[128];
	DWORD gameNUM;
	drawMap(pDefaultMap, hOUT);
	SetConsoleActiveScreenBuffer(hOUT);
	COORD playerOneBirth = { 10, 4 };
	for (int i = 0; i < 6; i++)
	{
		if (isWatchOnly)
		{
			COORD youCanWatch = { 20, 18 };
			CTank temp(i % 4, youCanWatch, i + 1, true, false, false);
			vecTank.push_back(temp);
			isWatchOnly = false;
			continue;
		}
		CTank temp(i % 4, playerOneBirth, i + 1, (i < 2 ? true : false), (i < 2 ? false : true), false);
		vecTank.push_back(temp);
	}
	vecTank[0].printTank(hOUT);

	while (isINGAME)
	{
		if (player1LifeCount < 0)
		{
			isINGAME = false;
			continue;
		}
		for (unsigned int q = 0; q < vecCan.size(); q++)
		{
			if (!vecCan[q].isCannonAvailable)
			{
				vecCan[q].eraseCannon();
				vecCan.erase(vecCan.begin() + q);
			}
		}
		for (unsigned int l = 0; l < vecCan.size(); l++)
		{
			vecCan[l].cannonFly(l);
		}
		for (unsigned int g = 2; g < vecTank.size(); g++)
		{
			if (!vecTank[g].m_isAlive)
			{
				vecTank[g].eraseTank(hOUT);
				vecTank.erase(vecTank.begin() + g);
			}
		}
		for (unsigned int i = 0; i < vecTank.size(); i++)
		{
			if (vecTank[i].m_computerControl)
			{
				if (vecTank[i].m_isAlive)
				{
					if (rand() < 1000 ? true : false)
					{
						tankFire(vecTank[i].m_tankPOS, vecTank[i].m_tankDirection, vecTank[i].m_isSuper, vecCan.size() + 1);
						vecTank[i].m_tankDirection = rand() % 4;
					}
				}
				vecTank[i].tankMove(vecTank[i].m_tankDirection, hOUT);
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
				/*if (!vecTank[0].m_isAlive)
				{
				vecTank[0].m_isAlive = true;
				player1LifeCount--;
				}*/
				switch (irGame[i].Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_UP:
				{
							  if (!vecTank[0].m_isAlive)
							  {
								  break;
							  }
							  vecTank[0].tankMove(UP, hOUT);
							  break;
				}
				case VK_DOWN:
				{
								if (!vecTank[0].m_isAlive)
								{
									break;
								}
								vecTank[0].tankMove(DOWN, hOUT);
								break;
				}
				case VK_LEFT:
				{
								if (!vecTank[0].m_isAlive)
								{
									break;
								}
								vecTank[0].tankMove(LEFT, hOUT);
								break;
				}
				case VK_RIGHT:
				{
								 if (!vecTank[0].m_isAlive)
								 {
									 break;
								 }
								 vecTank[0].tankMove(RIGHT, hOUT);
								 break;
				}
				case VK_SPACE:
				{
								 if (!vecTank[0].m_isAlive)
								 {
									 break;
								 }
								 tankFire(vecTank[0].m_tankPOS, vecTank[0].m_tankDirection, vecTank[0].m_isSuper, vecCan.size() + 1);
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
								  vecCan.clear();
								  vecTank.clear();
								  vecPortal.clear();
								  break;
				}
				case VK_TAB:
				{
							   unFinished();
							   SetConsoleActiveScreenBuffer(hOUT);
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

void tankFire(COORD tankPOS, int dire, bool isSuper, int cID)
{
	CCannon tempCannon(tankPOS, dire, isSuper, cID);
	vecCan.push_back(tempCannon);
}

void mapSelect()
{
	tuiPOPUP mapSelectPop(selectMap, _countof(selectMap));
	mapSelectPop.popUP();
	INPUT_RECORD irMAPS[128];
	DWORD numRead;
	while (isMapSelect)
	{
		if (!_kbhit())
		{
			continue;
		}
		ReadConsoleInput(hIn, irMAPS, 128, &numRead);
		for (unsigned int i = 0; i < numRead; i++)
		{
			if (irMAPS[i].Event.KeyEvent.bKeyDown)
			{

				switch (irMAPS[i].Event.KeyEvent.wVirtualKeyCode)
				{
				case 0x31:case VK_NUMPAD1:
				{
							  pDefaultMap = g_map_inTheJungle;
							  isMapSelect = false;
							  return;

				}
				case 0x32:case VK_NUMPAD2:
				{
							  pDefaultMap = g_map_ironGreatWall;
							  isMapSelect = false;
							  return;
				}
				case 0x33:case VK_NUMPAD3:
				{
							  pDefaultMap = g_map_mineField;
							  isMapSelect = false;
							  return;
				}
				case 0x34:case VK_NUMPAD4:
				{
							  pDefaultMap = g_map_planetEdge;
							  isMapSelect = false;
							  return;
				}
				case 0x35:case VK_NUMPAD5:
				{
							  pDefaultMap = g_map_skiiYard;
							  isMapSelect = false;
							  return;
				}
				case 0x36:case VK_NUMPAD6:
				{
							  pDefaultMap = g_map_watchOnly;
							  isWatchOnly = true;
							  isMapSelect = false;
							  return;
				}
				case 0x37:case VK_NUMPAD7:
				{
							  pDefaultMap = g_map_inTheJungle;
							  isMapSelect = false;
							  return;
				}
				default:
					break;
				}
			}
		}
	}
}

void demoPlay()
{
	HANDLE hDemo = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	COORD demoCO = { 160, 40 };
	SetConsoleScreenBufferSize(hDemo, demoCO);
	CONSOLE_CURSOR_INFO cciPUP;
	cciPUP.bVisible = false;
	cciPUP.dwSize = 1;
	SetConsoleCursorInfo(hDemo, &cciPUP);
	pDefaultMap = g_map_planetEdge;
	drawMap(pDefaultMap, hDemo);
	SetConsoleActiveScreenBuffer(hDemo);
	isMistMode = false;
	COORD xxx = { 10, 10 };
	for (int i = 0; i < 6; i++)
	{
		CTank temp(i % 4, xxx, i + 1, false, true, false);
		vecTank.push_back(temp);
		xxx.X += 6;
		xxx.Y += 3;
	}
	time_t startTime, endTime;
	time(&startTime);
	while (true)
	{
		for (unsigned int i = 0; i < vecTank.size(); i++)
		{
			if (vecTank[i].m_computerControl)
			{
				if (vecTank[i].m_isAlive)
				{
					if (rand() < 1000 ? true : false)
					{
						tankFire(vecTank[i].m_tankPOS, vecTank[i].m_tankDirection, vecTank[i].m_isSuper, vecCan.size() + 1);
						vecTank[i].m_tankDirection = rand() % 4;
					}
				}
				vecTank[i].tankMove(vecTank[i].m_tankDirection, hDemo);
			}
		}
		Sleep(80);
		time(&endTime);
		if ((endTime - startTime) > 10)
		{
			CloseHandle(hDemo);
			return;
		}
		if (_kbhit())
		{
			CloseHandle(hDemo);
			return;
		}

	}

}

void unFinished()
{
	tuiPOPUP inGameINFO(inGameInfo, _countof(inGameInfo));
	inGameINFO.popUP();
	Sleep(3000);
}