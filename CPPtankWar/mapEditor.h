#pragma once
#include <windows.h>
#include "tuiPOPUP.h"

#define BRICKWALL 11111
#define IRONWALL 22222
#define TRAP 33333
#define RIVER 44444
#define BUSH 55555
#define MINE 66666
#define ICE 77777
#define PORTAL 88888
#define BEDROCK 99999
#define EMPTY 0

void mapEditor(HANDLE hIN, HANDLE hOUT);
void changeBrick(KEY_EVENT_RECORD ker, HANDLE hOLD,int(*pRawMap)[80],tuiPOPUP& editorPOP);
void drawONrawMap(MOUSE_EVENT_RECORD mer, int(*pRawMap)[80], HANDLE hOUT, int& brickT);
