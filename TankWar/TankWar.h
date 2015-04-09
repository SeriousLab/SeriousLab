#pragma once
#include "data.h"
#include "mapEditor.h"
#include "logic.h"

extern HANDLE hStdIn;
extern HANDLE hStdOut;
extern CONSOLE_SCREEN_BUFFER_INFO csbiInitiatWindow;
extern int gameMap[35][60];

void printMessage(char(*pmt)[20], int numOfEle);
bool initializeWindow();
bool readMap(char(*filename)[20], int(*pMap)[60]);
bool printMap();
void printTank(tanks *tank,bool iswipe);