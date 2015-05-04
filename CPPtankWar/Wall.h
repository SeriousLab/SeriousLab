#pragma once
#include <windows.h>

void initialPreDefinedMaps();

extern wchar_t* wallType[10];
extern WORD wallColor[10];
extern int g_map_skiiYard[40][80];
extern int g_map_planetEdge[40][80];
extern int g_map_mineField[40][80];
extern int g_map_watchOnly[40][80];
extern int g_map_ironGreatWall[40][80];
extern int g_map_inTheJungle[40][80];
extern int rawMap[40][80];


class CWall
{
public:
	CWall();
	~CWall();
};

