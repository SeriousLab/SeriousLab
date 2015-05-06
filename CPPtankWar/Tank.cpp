#include "stdafx.h"
#include "Tank.h"
#include <windows.h>
#include <vector>

const int CTank::tankDirect[4][2][6] = {
	{ {0,-2,0,2,-2,2}, {-1,0,0,0,1,1} },
	{ {-2,2,-2,0,2,0}, {-1,-1,0,0,0,1} },
	{ {0,2,-2,0,0,2}, {-1,-1,0,0,1,1} },
	{ {-2,0,0,2,-2,0}, {-1,-1,0,0,1,1} }
};

const WORD CTank::tankColor[2] = {
	FOREGROUND_INTENSITY,
	FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_RED|BACKGROUND_INTENSITY
};

const int CTank::tankPOSmove[4][2][1] = {
	{ {0}, {-1} },
	{ {0}, {1} },
	{ {-2}, {0} },
	{ {2}, {0} }
};

CTank::CTank(int directionT, COORD tankPOS, int tankID, bool isFriendly, bool isComputer, int tankLevel)
{
	m_tankLastPOS = m_tankPOS = tankPOS;
	m_tankLastDirection = m_tankDirection = directionT;
	m_isTraped = false;
	m_tankID = tankID;
	m_isTankFriendly = isFriendly;
	m_computerControl = isComputer;
	m_tankLevel = tankLevel;
	m_tankHealth = m_tankLevel * 11;
	isZipped = false;
	stepCount = 0;
}


CTank::~CTank()
{
}

void CTank::printTank()
{
	for (int i = 0; i < 6; i++)
	{
		if (pDefaultMap[m_tankPOS.Y + tankDirect[m_tankDirection][1][i]][(m_tankPOS.X + tankDirect[m_tankDirection][0][i]) / 2] == BUSH)
		{
			continue;
		}
		COORD tempCO = { m_tankPOS.X + tankDirect[m_tankDirection][0][i], m_tankPOS.Y + tankDirect[m_tankDirection][1][i] };
		DWORD dwDrawTank;
		WriteConsoleOutputAttribute(hOut, &tankColor[(m_isTankFriendly ? 1 : 0)], 1, tempCO, &dwDrawTank);
		WriteConsoleOutputCharacter(hOut, L"¡ö", 1, tempCO, &dwDrawTank);
		tempCO.X++;
		WriteConsoleOutputAttribute(hOut, &tankColor[(m_isTankFriendly ? 1 : 0)], 1, tempCO, &dwDrawTank);
	}
}

void CTank::eraseTank()
{
	for (int i = 0; i < 6; i++)
	{
		DWORD dwErase;
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
		m_tankLastDirection = m_tankDirection;
		m_tankDirection = Tankdirection;
		printTank();
	}
}