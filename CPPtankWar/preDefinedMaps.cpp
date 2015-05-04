#include "stdafx.h"
#include "mapEditor.h"

int g_map_skiiYard[40][80] = { 0 };
int g_map_planetEdge[40][80] = { 0 };
int g_map_mineField[40][80] = { 0 };
int g_map_watchOnly[40][80] = { 0 };
int rawMap[40][80] = { 0 };

void initialPreDefinedMaps()
{
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 80; y++)
		{
			if (x == 0 || x == 39 || y == 0 || y == 79)
			{
				g_map_watchOnly[x][y] = BEDROCK;
				g_map_planetEdge[x][y] = BEDROCK;
				g_map_mineField[x][y] = BEDROCK;
				g_map_skiiYard[x][y] = BEDROCK;
				rawMap[x][y] = BEDROCK;
			}
			else
			{
				g_map_skiiYard[x][y] = ICE;
				if (!(rand() % 44))
				{
					g_map_planetEdge[x][y] = PORTAL;
				}
				if (!(rand() % 20))
				{
					g_map_mineField[x][y] = MINE;
				}
				if (x == 14 || x == 24)
				{
					g_map_watchOnly[x][y] = BEDROCK;
					if (!(rand() % 20))
					{
						g_map_watchOnly[x][y] = EMPTY;
					}
				}
			}
		}
	}

}

int g_map_ironGreatWall[40][80] = {
	{ 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 99999 },
	{ 99999, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 99999 },
	{ 99999, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 22222, 22222, 0, 0, 0, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 88888, 88888, 88888, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 88888, 88888, 88888, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 88888, 88888, 88888, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 22222, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 88888, 88888, 88888, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 88888, 88888, 88888, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 88888, 88888, 88888, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999 }
};

int g_map_inTheJungle[40][80] = {
	{ 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999 },
	{ 99999, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 99999 },
	{ 99999, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 99999 },
	{ 99999, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 99999 },
	{ 99999, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 0, 99999 },
	{ 99999, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 99999 },
	{ 99999, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 99999 },
	{ 99999, 0, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 55555, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 0, 55555, 55555, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 0, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 0, 55555, 55555, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 0, 0, 0, 0, 0, 55555, 0, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 0, 0, 0, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 0, 0, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 44444, 0, 44444, 0, 0, 55555, 55555, 55555, 55555, 0, 55555, 55555, 0, 0, 55555, 0, 0, 0, 0, 0, 55555, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 0, 0, 0, 0, 55555, 0, 55555, 0, 55555, 55555, 55555, 55555, 55555, 44444, 44444, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 0, 55555, 44444, 44444, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 0, 99999 },
	{ 99999, 0, 0, 44444, 44444, 0, 0, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 0, 55555, 0, 0, 0, 0, 55555, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 0, 0, 44444, 0, 44444, 0, 44444, 55555, 55555, 55555, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 0, 0, 55555, 55555, 44444, 55555, 55555, 55555, 55555, 55555, 44444, 55555, 55555, 55555, 55555, 44444, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 99999 },
	{ 99999, 0, 0, 44444, 44444, 44444, 0, 0, 0, 0, 44444, 44444, 55555, 55555, 55555, 0, 0, 0, 55555, 55555, 0, 55555, 55555, 0, 0, 0, 44444, 44444, 44444, 55555, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 55555, 55555, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 55555, 55555, 55555, 55555, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 99999 },
	{ 99999, 0, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 55555, 55555, 44444, 0, 44444, 44444, 44444, 44444, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 99999 },
	{ 99999, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 99999 },
	{ 99999, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 55555, 55555, 55555, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 99999 },
	{ 99999, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 99999 },
	{ 99999, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 55555, 44444, 55555, 55555, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 0, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 0, 44444, 44444, 0, 99999 },
	{ 99999, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 0, 44444, 44444, 44444, 0, 44444, 44444, 44444, 0, 44444, 44444, 44444, 44444, 0, 0, 0, 0, 0, 55555, 55555, 44444, 44444, 44444, 0, 0, 0, 55555, 55555, 55555, 44444, 44444, 44444, 0, 0, 0, 44444, 0, 44444, 44444, 44444, 0, 99999 },
	{ 99999, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 0, 44444, 44444, 44444, 44444, 0, 0, 0, 44444, 0, 0, 55555, 44444, 0, 44444, 0, 0, 0, 0, 0, 55555, 55555, 0, 0, 0, 0, 0, 0, 55555, 55555, 0, 55555, 44444, 0, 0, 0, 0, 0, 44444, 44444, 0, 0, 0, 0, 99999 },
	{ 99999, 0, 0, 0, 0, 44444, 44444, 44444, 44444, 44444, 44444, 44444, 0, 44444, 44444, 44444, 44444, 44444, 44444, 0, 44444, 44444, 44444, 44444, 0, 0, 44444, 44444, 0, 0, 44444, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 0, 0, 0, 55555, 55555, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 0, 0, 55555, 0, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 0, 0, 99999 },
	{ 99999, 0, 0, 44444, 44444, 44444, 55555, 55555, 0, 0, 0, 44444, 44444, 44444, 44444, 44444, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 55555, 0, 0, 0, 55555, 55555, 55555, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 0, 0, 55555, 55555, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 99999 },
	{ 99999, 0, 0, 0, 0, 55555, 55555, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 0, 55555, 55555, 55555, 0, 99999 },
	{ 99999, 0, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 0, 55555, 0, 55555, 55555, 55555, 55555, 0, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 99999 },
	{ 99999, 0, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 0, 0, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 99999 },
	{ 99999, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 0, 55555, 0, 0, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 99999 },
	{ 99999, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 99999 },
	{ 99999, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 0, 0, 0, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 99999 },
	{ 99999, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 99999 },
	{ 99999, 0, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 99999 },
	{ 99999, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 99999 },
	{ 99999, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 99999 },
	{ 99999, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 0, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 0, 99999 },
	{ 99999, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 99999 },
	{ 99999, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 0, 55555, 55555, 0, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 0, 0, 99999 },
	{ 99999, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 0, 55555, 55555, 55555, 55555, 0, 0, 0, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 0, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 55555, 0, 55555, 0, 0, 99999 },
	{ 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999 }
};

