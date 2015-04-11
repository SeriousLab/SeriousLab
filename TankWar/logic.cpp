#include "stdafx.h"
#include "data.h"
#include "TankWar.h"
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

ammos ammoArray[60];
tanks allTank[5];
int enemyTankCount = 0;
int tankMap[35][60] = { 0 };
int ammoMap[35][60] = { 0 };
COORD birthPlace;
int gameLevel = 0;
bool gameInitial = true;
bool isDualPlayer = false;
bool isGamePlay = false;
int killCount = 0;

void initializeTank(bool isDualPlayer)
{
	time_t ptime;
	srand((unsigned int)time(&ptime));
	allTank[0].tankPosition.X = 20;
	allTank[0].tankPosition.Y = 2;
	allTank[0].directionIndex = TANKUP;
	allTank[0].previousIndex = allTank[0].directionIndex;
	allTank[0].tankID = 1;
	allTank[0].tankType = 3;
	allTank[0].tankAmmo = 33;
	allTank[0].isFriendly = true;
	allTank[1].tankPosition.X = 20;
	allTank[1].tankPosition.Y = 57;
	allTank[1].directionIndex = TANKUP;
	allTank[1].previousIndex = allTank[1].directionIndex;
	allTank[1].tankID = 2;
	allTank[1].tankType = 5;
	allTank[1].isFriendly = true;
	allTank[1].tankAmmo = 22;
	for (int i = 2; i < 5; i++)
	{
		allTank[i].isDead = true;
	}
	for (int q = 0; q < 60; q++)
	{
		ammoArray[q].isAvailable = true;
	}
	tankMap[allTank[0].tankPosition.X][allTank[0].tankPosition.Y] = allTank[0].tankID;
}

void tankMoveTest(bool gamePlay, bool isInitial, bool dualPlayer)
{
	printMap(gameLevel);
	if (gamePlay)
	{
		printMessage(g_gamePlayM, sizeof(g_gamePlayM) / sizeof(g_gamePlayM[0]));
	}
	else
	{
		printMessage(g_welcomeM, sizeof(g_welcomeM) / sizeof(g_welcomeM[0]));
	}
	INPUT_RECORD irMOVE[128] = { 0 };
	DWORD numRead;
	int iTime = 10000;
	int iAmmo = 2000;
	while (isInitial)
	{
		iTime--;
		iAmmo--;
		if (!iAmmo)
		{
			ammoIsHit();
			iAmmo = 2000;
		}
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
				if (gamePlay)
				{

					switch (irMOVE[m].Event.KeyEvent.wVirtualKeyCode)
					{
					case VK_UP:
					{
								  if (isTankDead(allTank[0]))
								  {
									  continue;
								  }
								  keyProcess(TANKUP, &allTank[0]);
								  continue;
					}
					case VK_DOWN:
					{
									if (isTankDead(allTank[0]))
									{
										continue;
									}
									keyProcess(TANKDOWN, &allTank[0]);
									continue;
					}
					case VK_LEFT:
					{
									if (isTankDead(allTank[0]))
									{
										continue;
									}
									keyProcess(TANKLEFT, &allTank[0]);
									continue;
					}
					case VK_RIGHT:
					{
									 if (isTankDead(allTank[0]))
									 {
										 continue;
									 }
									 keyProcess(TANKRIGHT, &allTank[0]);
									 continue;
					}
					case VK_SPACE:
					{
									 if (isTankDead(allTank[0]))
									 {
										 continue;
									 }
									 fireAmmo(allTank[0]);
									 continue;
					}
					case 0x57:
					{
								 if (dualPlayer == false)
								 {
									 continue;
								 }
								 if (isTankDead(allTank[1]))
								 {
									 continue;
								 }
								 keyProcess(TANKUP, &allTank[1]);
								 continue;
					}
					case 0x41:
					{
								 if (dualPlayer == false)
								 {
									 continue;
								 }
								 if (isTankDead(allTank[1]))
								 {
									 continue;
								 }
								 keyProcess(TANKLEFT, &allTank[1]);
								 continue;
					}
					case 0x44:
					{
								 if (dualPlayer == false)
								 {
									 continue;
								 }
								 if (isTankDead(allTank[1]))
								 {
									 continue;
								 }
								 keyProcess(TANKRIGHT, &allTank[1]);
								 continue;
					}
					case 0x53:
					{
								 if (dualPlayer == false)
								 {
									 continue;
								 }
								 if (isTankDead(allTank[1]))
								 {
									 continue;
								 }
								 keyProcess(TANKDOWN, &allTank[1]);
								 continue;
					}
					case VK_RETURN:
					{
									  if (dualPlayer == false)
									  {
										  continue;
									  }
									  if (isTankDead(allTank[1]))
									  {
										  continue;
									  }
									  fireAmmo(allTank[1]);
									  continue;
					}
					case 0x51:
					{
								 return;
					}
					case 0x52:
					{
								 for (int w = 0; w < 5; w++)
								 {
									 allTank[w].isDead = false;
								 }
								 continue;
					}
					default:
						continue;
					}
				}
				else
				{
					switch (irMOVE[m].Event.KeyEvent.wVirtualKeyCode)
					{
					case 0x31:case VK_NUMPAD1:
					{
								  isInitial = false;
								  isDualPlayer = false;
								  isGamePlay = true;
								  gameInitial = false;
								  //printMessage(g_gamePlayM, sizeof(g_gamePlayM) / sizeof(g_gamePlayM[0]));
								  continue;

					}
					case 0x32:case VK_NUMPAD2:
					{
								  isInitial = false;
								  isDualPlayer = true;
								  isGamePlay = true;
								  gameInitial = false;
								  //printMessage(g_gamePlayM, sizeof(g_gamePlayM) / sizeof(g_gamePlayM[0]));
								  continue;
					}
					case 0x33:case VK_NUMPAD3:
					{
								  mapEditor(&coSave);
								  isInitial = false;
								  isGamePlay = false;
								  gameLevel = 11;
								  continue;
					}
					case 0x51:
					{
								 return;
					}
					default:
						break;
					}
				}
			}
		}
	}
	tankMoveTest(isGamePlay, gameInitial, isDualPlayer);
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
	if (gameMap[tank.tankPosition.X][tank.tankPosition.Y] != 0)
	{
		return true;
	}
	for (int i = 0; i < 5; i++)
	{
		if (gameMap[tank.tankPosition.X + tankDIR[tank.directionIndex][0][i]][tank.tankPosition.Y + tankDIR[tank.directionIndex][1][i]] != 0)
		{
			return true;
		}
		if (tankMap[tank.tankPosition.X + tankDIR[tank.directionIndex][0][i]][tank.tankPosition.Y + tankDIR[tank.directionIndex][1][i]] != 0)
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
			ammoArray[i].ammoID = i + 1;
			ammoArray[i].lastCo.X = tank.tankPosition.X - ammoDIR[tank.directionIndex][0][0];
			ammoArray[i].lastCo.Y = tank.tankPosition.Y - ammoDIR[tank.directionIndex][1][0];
			ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = ammoArray[i].ammoID;
			return true;
		}
	}
	return false;
}

void randomTankMove()
{
	if (enemyTankCount < 3)
	{
		for (int i = 2; i < 5; i++)
		{
			if (allTank[i].isDead == true)
			{
				allTank[i].directionIndex = rand() % 4;
				allTank[i].isDead = false;
				allTank[i].isFriendly = false;
				allTank[i].tankType = rand() % 6 + 1;
				allTank[i].tankPosition.X = 5 * i + 4;
				allTank[i].tankPosition.Y = 2;
				allTank[i].tankID = i + 1;
				allTank[i].tankAmmo = allTank[i].tankType * 11;
				allTank[i].tankHealth = allTank[i].tankType * 11;
				enemyTankCount++;
				tankMap[allTank[i].tankPosition.X][allTank[i].tankPosition.Y] = allTank[i].tankID;
				for (int s = 0; s < 5; s++)
				{
					tankMap[allTank[i].tankPosition.X + tankDIR[allTank[i].directionIndex][0][s]][allTank[i].tankPosition.Y + tankDIR[allTank[i].directionIndex][1][s]] = allTank[i].tankID;
				}
			}
		}
	}
	for (int i = 2; i < 5; i++)
	{
		if (allTank[i].isDead == false)
		{
			if (rand() % 10 == 3)
			{
				fireAmmo(allTank[i]);
			}
			tankMap[allTank[i].tankPosition.X][allTank[i].tankPosition.Y] = 0;
			for (int s = 0; s < 5; s++)
			{
				tankMap[allTank[i].tankPosition.X + tankDIR[allTank[i].directionIndex][0][s]][allTank[i].tankPosition.Y + tankDIR[allTank[i].directionIndex][1][s]] = 0;
			}
			keyProcess(rand() % 4, &allTank[i]);
			tankMap[allTank[i].tankPosition.X][allTank[i].tankPosition.Y] = allTank[i].tankID;
			for (int s = 0; s < 5; s++)
			{
				tankMap[allTank[i].tankPosition.X + tankDIR[allTank[i].directionIndex][0][s]][allTank[i].tankPosition.Y + tankDIR[allTank[i].directionIndex][1][s]] = allTank[i].tankID;
			}
		}
	}
}

bool ammoIsHit()
{
	for (int i = 0; i < 60; i++)
	{
		if (ammoArray[i].isAvailable == false)
		{
			printAmmo(&ammoArray[i], true, true);
			if (gameMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] == 0)
			{
				if (tankMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] == 0)
				{
					if (ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] == 0)
					{
						ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = ammoArray[i].ammoID;
						continue;
					}
					else
					{
						if (ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] != ammoArray[i].ammoID)
						{

							if (ammoArray[ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].ammoType > ammoArray[i].ammoType)
							{
								ammoArray[ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].ammoType -= ammoArray[i].ammoType;
								ammoArray[i].isAvailable = true;
								continue;
							}
							else if (ammoArray[ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].ammoType == ammoArray[i].ammoType)
							{
								ammoArray[ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].isAvailable = true;
								ammoArray[i].isAvailable = true;
								ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = 0;
								printAmmo(&ammoArray[i], false, true);
								continue;
							}
							else
							{
								ammoArray[ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].isAvailable = true;
								ammoArray[i].ammoType -= ammoArray[ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].ammoType;
								ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = ammoArray[i].ammoID;
								printAmmo(&ammoArray[ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1], true, true);
								continue;
							}
						}
					}
				}
				else
				{
					if (allTank[tankMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].isFriendly == ammoArray[i].isFriendly)
					{
						ammoArray[i].isAvailable = true;
						ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = 0;
						continue;
					}
					else
					{
						if (allTank[tankMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].tankHealth > ammoArray[i].ammoType)
						{
							ammoArray[i].isAvailable = true;
							ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = 0;
							allTank[tankMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].tankHealth -= ammoArray[i].ammoType;
							continue;
						}
						else if (allTank[tankMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].tankHealth == ammoArray[i].ammoType)
						{
							ammoArray[i].isAvailable = true;
							ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = 0;
							allTank[tankMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].isDead = true;
							printTank(&allTank[tankMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1], true);
							continue;
						}
						else
						{
							allTank[tankMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].isDead = true;
							ammoArray[i].ammoType -= allTank[tankMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1].tankAmmo;
							printTank(&allTank[tankMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] - 1], true);
							continue;
						}
					}
				}
			}
			else
			{
				if (gameMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] == 99)
				{
					ammoArray[i].isAvailable = true;
					ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = 0;
					continue;
				}
				if (gameMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] == 66)
				{
					if (ammoArray[i].ammoType >= gameMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y])
					{
						for (int k = 0; k < 9; k++)
						{
							COORD ctemp = coWOLF;
							ctemp.X += wolfPackPos[k][0][0];
							ctemp.Y += wolfPackPos[k][1][0];
							endGame(ctemp);
						}
					}
					else
					{
						for (int l = 0; l < 9; l++)
						{
							gameMap[coWOLF.X + wolfPackPos[l][0][0]][coWOLF.Y + wolfPackPos[l][1][0]] -= ammoArray[i].ammoType;
						}
						ammoArray[i].isAvailable = true;
					}
				}
				else
				{
					if (gameMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] > ammoArray[i].ammoType)
					{
						gameMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] -= ammoArray[i].ammoType;
						ammoArray[i].isAvailable = true;
						ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = 0;
						continue;
					}
					else if (gameMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] == ammoArray[i].ammoType)
					{
						gameMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = 0;
						ammoArray[i].isAvailable = true;
						ammoMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = 0;
						printAmmo(&ammoArray[i], false, true);
						continue;
					}
					else
					{
						ammoArray[i].ammoType -= gameMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y];
						gameMap[ammoArray[i].ammoPosition.X][ammoArray[i].ammoPosition.Y] = 0;
						continue;
					}
				}
			}
		}
	}
	for (int c = 0; c < 60; c++)
	{
		if (ammoArray[c].isAvailable == false)
		{
			printAmmo(&ammoArray[c], false, false);
			ammoArray[c].lastCo = ammoArray[c].ammoPosition;
			ammoArray[c].ammoPosition.X += ammoDIR[ammoArray[c].directionIndex][0][0];
			ammoArray[c].ammoPosition.Y += ammoDIR[ammoArray[c].directionIndex][1][0];
		}
	}
	return true;
}

void findFirstAvailableBirthPlace(bool isenemy)
{
	if (isenemy)
	{
		for (int i = 2; i < 33; i++)
		{
			for (int j = 2; j < 58; j++)
			{
				for (int t = 0; t < 9; t++)
				{
					if (gameMap[i + wolfPackPos[t][0][0]][j + wolfPackPos[t][1][0]])
					{
						goto here;
					}
				}
				birthPlace.X = i;
				birthPlace.Y = j;
				return;
			here:
				;
			}
		}
	}
	else
	{
		for (int q = 32; q > 1; q--)
		{
			for (int y = 57; y > 1; y--)
			{
				for (int g = 0; g < 9; g++)
				{
					if (gameMap[q + wolfPackPos[g][0][0]][y + wolfPackPos[g][1][0]])
					{
						goto there;
					}
				}
				birthPlace.X = q;
				birthPlace.Y = y;
				return;
			there:
				;
			}
		}
	}
}

bool isTankDead(tanks tank)
{
	if (tank.isDead)
	{
		return true;
	}
	return false;
}