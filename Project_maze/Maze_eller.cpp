
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

int maze[20][26] = { 0 };
time_t pTime;
void initialingMaze();
void randomRightWalls(int x, int y);
void randomBottomWalls(int x, int y);
void printMap();
int getMove();
void resetGame();
bool isWall(int x, int y, int moveDirection);
bool playerPosition(int x, int y);
bool isEndPoint(int x, int y);
void printCount();

int xPos = 2;
int yPos = 1;
int xDirection[4] = { -1, 0, 1, 0 };
int yDirection[4] = { 0, 1, 0, -1 };
long stepCounter = 0;
long gameCounter = 0;

int main()
{

	srand((unsigned int)time(&pTime));
	gameCounter--;
	resetGame();
	while (true)
	{
		if (isEndPoint(xPos, yPos))
		{
			resetGame();
		}
		if (!_kbhit())
		{
			continue;
		}
		switch (getMove())
		{
		case 72:
		{
				   if (isWall(xPos, yPos, 0))
				   {
					   playerPosition(xPos, yPos);
					   printf("  ");
					   yPos -= 1;
					   playerPosition(xPos, yPos);
					   printf("¡â");
					   stepCounter++;
					   printCount();
					   break;
				   }
				   break;
		}
		case 80:
		{
				   if (isWall(xPos, yPos, 2))
				   {
					   playerPosition(xPos, yPos);
					   printf("  ");
					   yPos += 1;
					   playerPosition(xPos, yPos);
					   printf("¡â");
					   stepCounter++;
					   printCount();
					   break;
				   }
				   break;
		}
		case 77:
		{
				   if (isWall(xPos, yPos, 1))
				   {
					   playerPosition(xPos, yPos);
					   printf("  ");
					   xPos += 2;
					   playerPosition(xPos, yPos);
					   printf("¡â");
					   stepCounter++;
					   printCount();
					   break;
				   }
				   break;
		}
		case 75:
		{
				   if (isWall(xPos, yPos, 3))
				   {
					   playerPosition(xPos, yPos);
					   printf("  ");
					   xPos -= 2;
					   playerPosition(xPos, yPos);
					   printf("¡â");
					   stepCounter++;
					   printCount();
					   break;
				   }
				   break;
		}
		case 82:case 114:
		{
					gameCounter--;
					resetGame();
					break;
		}
		case 81:case 113:
		{
					system("cls");
					printf("Thanks for trying this game, see you next time!\n");
					return 0;
		}
		default:
			break;
		}
	}
	return 0;
}


void initialingMaze(){
	int x = 0;
	int y = 0;
	for (x = 0; x < 20; x++)
	{
		for (y = 0; y < 26; y++)
		{
			maze[x][y] = 0;
		}
	}
	for (int t = 1; t < 25; t += 2)
	{
		maze[1][t] = rand();
	}
	for (x = 1; x < 18; x += 2)
	{
		for (y = 1; y < 25; y += 2)
		{
			if (maze[x][y] == 0)
			{
				maze[x][y] = rand() % 65533 + 1;
			}
		}
		for (y = 1; y < 24; y += 2)
		{
			randomRightWalls(x, y);
		}
		for (y = 1; y < 24; y += 2)
		{
			randomBottomWalls(x, y);
			if (x == 17)
			{
				if ((maze[x][y + 1] + maze[x + 1][y + 1]) == 0 && (maze[x - 1][y + 1] + maze[x][y + 1] == 0))
				{
					maze[18][y + 1] = maze[18][y] = 1;
				}
			}
		}
		for (y = 1; y < 25; y++)
		{
			maze[19][y] = 0;
		}
	}
	maze[18][25] = 1;
	maze[18][24] = 1;
}

void randomRightWalls(int x, int y){
	bool cue = rand() % 2;

	if (maze[x][y] != maze[x][y + 2])
	{
		if (cue)
		{
			maze[x][y + 1] = maze[x][y];
			if (y + 2 != 25)
			{
				maze[x][y + 2] = maze[x][y];
			}
			else if (y + 2 == 25)
			{
				maze[x][y + 1] = maze[x][y];
			}
		}
		return;
	}
	maze[x][y + 1] = 0;
}

void randomBottomWalls(int x, int y){
	bool cue = rand() % 3;

	if (maze[x][y] != maze[x][y + 2])
	{
		maze[x + 2][y] = maze[x + 1][y] = maze[x][y];
		return;
	}
	else
	{
		if (cue)
		{
			maze[x + 2][y] = maze[x + 1][y] = maze[x][y];

		}
	}
}

void printMap(){
	system("cls");
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 26; y++)
		{
			if ((bool)maze[x][y])
			{
				printf("  ");
			}
			else
			{
				printf("¡ö");
			}
		}
		printf("\n");
	}
	printf("\n");
}

bool playerPosition(int x, int y)
{
	CONSOLE_CURSOR_INFO CurInfo = { 1 };

	COORD cPos;
	cPos.X = x;
	cPos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cPos);
	CurInfo.bVisible = false;
	HANDLE hHand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	return TRUE;
}

int getMove(){
	char m = 0;
	m = _getch();
	if (m < 0)
	{
		m = _getch();
		return m;
	}
	return m;
}

void printInfo(){
	printf("Use arrow keys to control your movement\n");
	printf("Press 'r' or 'R' to reset the map, and press 'q' or 'Q' to quit\n");
	printf("Enjoy!\n");

}

void resetGame(){
	xPos = 2;
	yPos = 1;
	stepCounter = 0;
	gameCounter++;
	initialingMaze();
	printMap();
	printInfo();
	playerPosition(xPos, yPos);
	printf("¡â");
	printCount();
}

bool isWall(int x, int y, int moveDirection){
	if (maze[y + xDirection[moveDirection]][x / 2 + yDirection[moveDirection]] == 0)
	{
		return false;
	}
	return true;
}

bool isEndPoint(int x, int y){
	if (y == 18 && x / 2 == 25)
	{
		return true;
	}
	return false;
}

void printCount(){
	playerPosition(60, 10);
	printf("Steps: %d", stepCounter);
	playerPosition(60, 11);
	printf("Games played: %d", gameCounter);
	playerPosition(52, 18);
	printf("¡û The exit");
	playerPosition(xPos, yPos);
}