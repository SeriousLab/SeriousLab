#include "stdafx.h"
#include "Tank.h"
#include <windows.h>
#include <vector>

const int tankDirect[4][2][6] = {
	{ { 0, -2, 0, 2, -2, 2 }, { -1, 0, 0, 0, 1, 1 } },
	{ { -2, 2, -2, 0, 2, 0 }, { -1, -1, 0, 0, 0, 1 } },
	{ { 0, 2, -2, 0, 0, 2 }, { -1, -1, 0, 0, 1, 1 } },
	{ { -2, 0, 0, 2, -2, 0 }, { -1, -1, 0, 0, 1, 1 } }
};

const WORD CTank::tankColor[2] = {
	FOREGROUND_INTENSITY,
	FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY
};

const int mistCO[2][81] = {
	{ -2, 0, 2, -4, -2, 0, 2, 4, -6, -4, -2, 0, 2, 4, 6, -8, -6, -4, -2, 0, 2, 4, 6, 8, -10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10, -10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10, -10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10, -8, -6, -4, -2, 0, 2, 4, 6, 8, -6, -4, -2, 0, 2, 4, 6, -4, -2, 0, 2, 4, -2, 0, 2 },
	{ -5, -5, -5, -4, -4, -4, -4, -4, -3, -3, -3, -3, -3, -3, -3, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5 }
};

const int tankPOSmove[4][2][1] = {
	{ { 0 }, { -1 } },
	{ { 0 }, { 1 } },
	{ { -2 }, { 0 } },
	{ { 2 }, { 0 } }
};

CTank::CTank(int directionT, COORD tankPOS, int tankID, bool isFriendly, bool isComputer, bool isSuper)
{
	m_tankLastPOS = m_tankPOS = tankPOS;
	m_tankLastDirection = m_tankDirection = directionT;
	m_isTraped = false;
	m_tankID = tankID;
	m_isTankFriendly = isFriendly;
	m_computerControl = isComputer;
	isZipped = false;
	stepCount = 0;
	m_isSuper = isSuper;
}


CTank::~CTank()
{
}

void CTank::printTank()
{
	DWORD dwDrawTank;
	if (isMistMode)
	{
		if (m_tankID==1||m_tankID==2)
		{
			for (int p = 0; p < 81; p++)
			{
				COORD tempMist = { m_tankPOS.X + mistCO[0][p], m_tankPOS.Y + mistCO[1][p] };
				WriteConsoleOutputAttribute(hOut, &wallColor[pDefaultMap[tempMist.Y][tempMist.X / 2] / 11111 % 10], 1, tempMist, &dwDrawTank);
				WriteConsoleOutputCharacter(hOut, wallType[pDefaultMap[tempMist.Y][tempMist.X / 2] / 11111 % 10], 1, tempMist, &dwDrawTank);
				tempMist.X++;
				WriteConsoleOutputAttribute(hOut, &wallColor[pDefaultMap[tempMist.Y][tempMist.X / 2] / 11111 % 10], 1, tempMist, &dwDrawTank);
			}
			for (int i = 0; i < 6; i++)
			{
				if (pDefaultMap[m_tankPOS.Y + tankDirect[m_tankDirection][1][i]][(m_tankPOS.X + tankDirect[m_tankDirection][0][i]) / 2] == BUSH)
				{
					continue;
				}
				COORD tempCO = { m_tankPOS.X + tankDirect[m_tankDirection][0][i], m_tankPOS.Y + tankDirect[m_tankDirection][1][i] };
				WriteConsoleOutputAttribute(hOut, &tankColor[(m_isTankFriendly ? 1 : 0)], 1, tempCO, &dwDrawTank);
				WriteConsoleOutputCharacter(hOut, L"¡ö", 1, tempCO, &dwDrawTank);
				tempCO.X++;
				WriteConsoleOutputAttribute(hOut, &tankColor[(m_isTankFriendly ? 1 : 0)], 1, tempCO, &dwDrawTank);
			}
		}
		else
		{
			for (int v = 0; v < 6; v++)
			{
				COORD tempCO = { m_tankPOS.X + tankDirect[m_tankDirection][0][v], m_tankPOS.Y + tankDirect[m_tankDirection][1][v] };
				for (int n = 0; n < 81; n++)
				{
					COORD tempMist = { m_tankPOS.X + mistCO[0][n], m_tankPOS.Y + mistCO[1][n] };
					if (tempCO.X == tempMist.X&&tempCO.Y == tempMist.Y)
					{
						if (pDefaultMap[m_tankPOS.Y + tankDirect[m_tankDirection][1][v]][(m_tankPOS.X + tankDirect[m_tankDirection][0][v]) / 2] == BUSH)
						{
							continue;
						}
						WriteConsoleOutputAttribute(hOut, &tankColor[(m_isTankFriendly ? 1 : 0)], 1, tempCO, &dwDrawTank);
						WriteConsoleOutputCharacter(hOut, L"¡ö", 1, tempCO, &dwDrawTank);
						tempCO.X++;
						WriteConsoleOutputAttribute(hOut, &tankColor[(m_isTankFriendly ? 1 : 0)], 1, tempCO, &dwDrawTank);
					}
				}
			}
		}
		
	}
}

void CTank::eraseTank()
{
	DWORD dwErase;
	if (isMistMode)
	{
		for (int p = 0; p < 81; p++)
		{
			COORD tempMist = { m_tankPOS.X + mistCO[0][p], m_tankPOS.Y + mistCO[1][p] };
			WriteConsoleOutputAttribute(hOut, &wallColor[EMPTY], 1, tempMist, &dwErase);
			WriteConsoleOutputCharacter(hOut, wallType[EMPTY], 1, tempMist, &dwErase);
			tempMist.X++;
			WriteConsoleOutputAttribute(hOut, &wallColor[EMPTY], 1, tempMist, &dwErase);
		}
	}
	for (int i = 0; i < 6; i++)
	{
		COORD tempErase = { m_tankLastPOS.X + tankDirect[m_tankLastDirection][0][i], m_tankLastPOS.Y + tankDirect[m_tankLastDirection][1][i] };
		WriteConsoleOutputAttribute(hOut, &wallColor[(pDefaultMap[tempErase.Y][tempErase.X / 2] / 11111) % 10], 1, tempErase, &dwErase);
		WriteConsoleOutputCharacter(hOut, wallType[(pDefaultMap[tempErase.Y][tempErase.X / 2] / 11111) % 10], 1, tempErase, &dwErase);
		tempErase.X++;
		WriteConsoleOutputAttribute(hOut, &wallColor[(pDefaultMap[tempErase.Y][tempErase.X / 2] / 11111) % 10], 1, tempErase, &dwErase);
	}
}

bool CTank::tankHitTest()
{
	if (!m_isTraped)
	{

		for (int i = 0; i < 6; i++)
		{
			switch (pDefaultMap[m_tankPOS.Y + tankDirect[m_tankDirection][1][i]][(m_tankPOS.X + tankDirect[m_tankDirection][0][i]) / 2])
			{
			case BEDROCK:case BRICKWALL:case IRONWALL:
			{
							 return true;
			}
			case TRAP:
			{
						 m_isTraped = true;
						 return false;
						 break;
			}
			case MINE:
			{
						 pDefaultMap[m_tankPOS.Y + tankDirect[m_tankDirection][1][i]][(m_tankPOS.X + tankDirect[m_tankDirection][0][i]) / 2] = 0;
						 eraseTank();
						 m_isAlive = false;
						 return true;
			}
			case PORTAL:
			{
						   if (stepCount < 3 && isZipped)
						   {
							   break;
						   }
						   else if (stepCount >= 3 && isZipped)
						   {
							   isZipped = false;
							   break;
						   }
						   else
						   {
							   zipTank();
						   }

			}
			default:
				break;
			}
		}
		return false;
	}
	else
	{
		bool trapTest = true;
		for (int i = 0; i < 6; i++)
		{
			switch (pDefaultMap[m_tankPOS.Y + tankDirect[m_tankDirection][1][i]][(m_tankPOS.X + tankDirect[m_tankDirection][0][i]) / 2])
			{
			case BEDROCK:case BRICKWALL:case IRONWALL:
			{
							 return true;
			}
			case TRAP:
			{
						 trapTest = false;
			}
			default:
				break;
			}
		}
		return trapTest;
	}
	return false;
}

void CTank::tankMove(int Tankdirection)
{
	eraseTank();
	m_tankLastPOS = m_tankPOS;
	m_tankPOS.X += tankPOSmove[Tankdirection][0][0];
	m_tankPOS.Y += tankPOSmove[Tankdirection][1][0];
	m_tankDirection = Tankdirection;
	if (!tankHitTest())
	{
		printTank();
		m_tankLastPOS = m_tankPOS;
		m_tankLastDirection = m_tankDirection;
		stepCount++;
	}
	else
	{
		if (!m_isAlive)
		{
			return;
		}
		m_tankPOS.X -= tankPOSmove[Tankdirection][0][0];
		m_tankPOS.Y -= tankPOSmove[Tankdirection][1][0];
		if (m_computerControl)
		{
			m_tankLastDirection = m_tankDirection = rand() % 4;
			printTank();
			return;
		}
		m_tankLastDirection = m_tankDirection;
		m_tankDirection = Tankdirection;
		printTank();
	}
}