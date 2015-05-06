#pragma once
#include <vector>

void drawWindow(HANDLE hIN, HANDLE hOUT);
void drawMap(int(*pMap)[80], HANDLE hOUT);
void gamePlay(HANDLE hIN, HANDLE hOUT, bool isDualPlayer);
void gameLayerSWAP();
void setDefaultMap();


extern bool exitTest;
extern bool isINGAME;
extern bool isEditor;

extern int(*pDefaultMap)[80];
extern std::vector<COORD> vecPortal;

extern HANDLE hOut;
extern HANDLE hIn;