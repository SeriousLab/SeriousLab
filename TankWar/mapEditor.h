#include <windows.h>
#pragma once

#define BRICK 11
#define IRON 33
#define OBS 99
#define WOLFPACK 66
#define EMPTY 0
//不同砖块用不同数字表示


void selectBrickType(KEY_EVENT_RECORD ker, int *currentBrick);
void drawBricks(HANDLE hstdout, MOUSE_EVENT_RECORD mer, int(*pMap)[60], int* nCurrentBrick);
void mapEditor(COORD *saveCo);

