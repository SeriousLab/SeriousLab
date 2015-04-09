#include "stdafx.h"
#include "data.h"
#include "TankWar.h"
#include <math.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

tanks player1;
tanks player2;
ammos ammoArray[60];
tanks enemyTank[3];
int enemyTankCount = 0;

void initializeTank()
{
	time_t ptime;
	srand((unsigned int)time(&ptime));
	player1.tankPosition.X = 20;
	player1.tankPosition.Y = 2;
	player1.directionIndex = TANKUP;
	player1.previousIndex = player1.directionIndex;
	for (int i = 0; i < 3; i++)
	{
		enemyTank[i].isDead = true;
	}
}

void tankMoveTest()
{
	INPUT_RECORD irMOVE[128] = { 0 };
	DWORD numRead;
	int iTime = 10000;
	while (true)
	{
		iTime--;
		if (!iTime)
		{
			randomTankMove();
			iTime = 10000;
		}

		if (!_kbhit())
		{
			continue;
		}
		ReadConsoleInput(hStdIn, irMOVE, 128, &numRead);
		for (unsigned int m = 0; m < numRead; m++)
		{
			if (irMOVE[m].Event.KeyEvent.bKeyDown)
			{
				switch (irMOVE[m].Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_UP:
				{
							  keyProcess(TANKUP, &player1);
							  continue;
				}
				case VK_DOWN:
				{
								keyProcess(TANKDOWN, &player1);
								continue;
				}
				case VK_LEFT:
				{
								keyProcess(TANKLEFT, &player1);
								continue;
				}
				case VK_RIGHT:
				{
								 keyProcess(TANKRIGHT, &player1);
								 continue;
				}
				default:
					continue;
				}
			}
		}
	}
}

void keyProcess(int moveDirection, tanks *tank)
{
	tank->directionIndex = moveDirection;
	printTank(tank, true);
	if (tank->directionIndex != tank->previousIndex)
	{
		if (isBlocked(*tank))
		{
			goto reverseJump;
		}
		printTank(tank, false);
		tank->previousIndex = tank->directionIndex;
		return;
	}
reverseJump:
	tank->tankPosition.X += ammoDIR[moveDirection][0][0];
	tank->tankPosition.Y += ammoDIR[moveDirection][1][0];
	if (isBlocked(*tank))
	{
		tank->tankPosition.X -= ammoDIR[moveDirection][0][0];
		tank->tankPosition.Y -= ammoDIR[moveDirection][1][0];
		tank->directionIndex = tank->previousIndex;
	}
	tank->previousIndex = tank->directionIndex;
	printTank(tank, false);
}

bool isBlocked(tanks tank)
{
	if (gameMap[tank.tankPosition.X + ammoDIR[tank.directionIndex][0][0]][tank.tankPosition.Y + ammoDIR[tank.directionIndex][1][0]] != 0)
	{
		return true;
	}
	for (int i = 0; i < 5; i++)
	{
		if (gameMap[tank.tankPosition.X + tankDIR[tank.directionIndex][0][i]][tank.tankPosition.Y + tankDIR[tank.directionIndex][1][i]] != 0)
		{
			return true;
		}
	}
	return false;
}

bool fireAmmo(tanks tank)
{
	for (int i = 0; i < 60; i++)
	{
		if (ammoArray[i].isAvailable == true)
		{
			ammoArray[i].isAvailable = false;
			ammoArray[i].ammoPosition.X = tank.tankPosition.X + 2 * ammoDIR[tank.directionIndex][0][0];
			ammoArray[i].ammoPosition.Y = tank.tankPosition.Y + 2 * ammoDIR[tank.directionIndex][1][0];
			ammoArray[i].isFriendly = tank.isFriendly;
			ammoArray[i].directionIndex = tank.directionIndex;
			ammoArray[i].ammoType = tank.tankAmmo;
			return true;
		}
	}
	return false;
}

void randomTankMove()
{
	if (enemyTankCount < 3)
	{
		for (int i = 0; i < 3; i++)
		{
			if (enemyTank[i].isDead == true)
			{
				enemyTank[i].directionIndex = rand() % 4;
				enemyTank[i].isDead = false;
				enemyTank[i].isFriendly = false;
				enemyTank[i].tankType = 1;
				enemyTank[i].tankPosition.X = 5 * i + 4;
				enemyTank[i].tankPosition.Y = 2;
				enemyTankCount++;
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		keyProcess(rand() % 4, &enemyTank[i]);
	}
}