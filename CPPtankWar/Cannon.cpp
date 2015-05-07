#include "stdafx.h"
#include "Cannon.h"
#include "Tank.h"

const int CCannon::cannonMove[4][2][1] = {
	{ { 0 }, { -1 } },
	{ { 0 }, { 1 } },
	{ { -2 }, { 0 } },
	{ { 2 }, { 0 } }
};


const WORD CCannon::cannonColor[2] = { FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED };

CCannon::CCannon(COORD startPOS, int startDirection, bool isSuper, int cannonID)
{
	m_cannonDirection = startDirection;
	m_cannonPos.X = startPOS.X + cannonMove[startDirection][0][0];
	m_cannonPos.Y = startPOS.Y + cannonMove[startDirection][1][0];
	m_cannonLastPos.X = startPOS.X - cannonMove[startDirection][0][0];
	m_cannonLastPos.Y = startPOS.Y - cannonMove[startDirection][1][0];
	isSuperCannon = isSuper;
	isCannonAvailable = true;
	m_cannonID = cannonID;
}


CCannon::~CCannon()
{
}


void CCannon::eraseCannon()
{
	bool isInMist = false;
	for (int m = 0; m < 81; m++)
	{
		COORD tempMist = { vecTank[0].m_tankPOS.X + mistCO[0][m], vecTank[0].m_tankPOS.Y + mistCO[1][m] };
		if (m_cannonPos.X == tempMist.X&&m_cannonPos.Y == tempMist.Y)
		{
			isInMist = true;
		}
	}
	if (isInMist)
	{
		if (pDefaultMap[m_cannonLastPos.Y][m_cannonLastPos.X / 2] == MINE)
		{
			COORD tempCO = m_cannonLastPos;
			WriteConsoleOutputAttribute(hOut, &wallColor[EMPTY], 1, m_cannonLastPos, &dwCannonWritten);
			WriteConsoleOutputCharacter(hOut, wallType[EMPTY], 1, m_cannonLastPos, &dwCannonWritten);
			tempCO.X++;
			WriteConsoleOutputAttribute(hOut, &wallColor[EMPTY], 1, tempCO, &dwCannonWritten);
			return;
		}
		COORD tempCO = m_cannonLastPos;
		WriteConsoleOutputAttribute(hOut, &wallColor[(pDefaultMap[m_cannonLastPos.Y][m_cannonLastPos.X / 2] / 11111) % 10], 1, m_cannonLastPos, &dwCannonWritten);
		WriteConsoleOutputCharacter(hOut, wallType[(pDefaultMap[m_cannonLastPos.Y][m_cannonLastPos.X / 2] / 11111) % 10], 1, m_cannonLastPos, &dwCannonWritten);
		tempCO.X++;
		WriteConsoleOutputAttribute(hOut, &wallColor[(pDefaultMap[m_cannonLastPos.Y][m_cannonLastPos.X / 2] / 11111) % 10], 1, tempCO, &dwCannonWritten);
	}
	else
	{
		COORD tempCO = m_cannonLastPos;
		WriteConsoleOutputAttribute(hOut, &wallColor[EMPTY], 1, m_cannonLastPos, &dwCannonWritten);
		WriteConsoleOutputCharacter(hOut, wallType[EMPTY], 1, m_cannonLastPos, &dwCannonWritten);
		tempCO.X++;
		WriteConsoleOutputAttribute(hOut, &wallColor[EMPTY], 1, tempCO, &dwCannonWritten);
		return;
	}
	
}

bool CCannon::cannonHitTest()
{
	for (unsigned int r = 0; r < vecCan.size();r++)
	{
		if ((vecCan[r].m_cannonPos.X == m_cannonPos.X)&&vecCan[r].m_cannonPos.Y==m_cannonPos.Y&&vecCan[r].m_cannonID!=m_cannonID)
		{
			vecCan[r].isCannonAvailable = false;
			isCannonAvailable = false;
			return true;
		}
	}
	for (unsigned int d = 0; d < vecTank.size();d++)
	{
		for (int b = 0; b < 6;b++)
		{
			COORD tempTankCO = { vecTank[d].m_tankPOS.X + tankDirect[vecTank[d].m_tankDirection][0][b], vecTank[d].m_tankPOS.Y + tankDirect[vecTank[d].m_tankDirection][1][b] };
			if (tempTankCO.X==m_cannonPos.Y&&tempTankCO.Y==m_cannonPos.Y)
			{
				vecTank[d].m_isAlive = false;
				isCannonAvailable = false;
				vecTank[d].eraseTank();
				return true;
			}
		}
	}
	switch (pDefaultMap[m_cannonPos.Y][m_cannonPos.X / 2])
	{
	case EMPTY:case MINE:case BUSH:case TRAP:case ICE:
	{
				   return false;
	}
	case 4444:
	{
				 //reserver for goods
				 break;
	}
	case BEDROCK:
	{
					isCannonAvailable = false;
					return true;
	}
	case BRICKWALL:
	{
					  isCannonAvailable = false;
					  pDefaultMap[m_cannonPos.Y][m_cannonPos.X / 2] = 0;
					  return true;
	}
	case IRONWALL:
	{
					 if (isSuperCannon)
					 {
						 pDefaultMap[m_cannonPos.Y][m_cannonPos.X / 2] = 0;
					 }
					 isCannonAvailable = false;
					 return true;

	}
	case PORTAL:
	{
				   m_cannonPos = vecPortal[rand() % vecPortal.size()];
				   m_cannonDirection = rand() % 4;
				   return false;
	}
	default:
		break;
	}
	return false;
}

void CCannon::printCannon()
{
	bool isInMist = false;
	for (int m = 0; m < 81;m++)
	{
		COORD tempMist = { vecTank[0].m_tankPOS.X + mistCO[0][m], vecTank[0].m_tankPOS.Y + mistCO[1][m] };
		if (m_cannonPos.X==tempMist.X&&m_cannonPos.Y==tempMist.Y)
		{
			isInMist = true;
		}
	}
	if (isInMist)
	{
		if (pDefaultMap[m_cannonPos.Y][m_cannonPos.X / 2] == BUSH)
		{
			return;
		}
		COORD tempCO = m_cannonPos;
		WriteConsoleOutputAttribute(hOut, &cannonColor[pDefaultMap == g_map_skiiYard ? 1 : 0], 1, m_cannonPos, &dwCannonWritten);
		WriteConsoleOutputCharacter(hOut, L"กั", 1, m_cannonPos, &dwCannonWritten);
		tempCO.X++;
		WriteConsoleOutputAttribute(hOut, &cannonColor[pDefaultMap == g_map_skiiYard ? 1 : 0], 1, tempCO, &dwCannonWritten);
	}
	else
	{
		return;
	}
	
}

void CCannon::cannonFly(int canID)
{
	m_cannonID = canID;
	m_cannonPos.X += cannonMove[m_cannonDirection][0][0];
	m_cannonPos.Y += cannonMove[m_cannonDirection][1][0];
	eraseCannon();
	if (!cannonHitTest())
	{
		printCannon();
		m_cannonLastPos = m_cannonPos;
		return;
	}
	else
	{
		return;
	}
}