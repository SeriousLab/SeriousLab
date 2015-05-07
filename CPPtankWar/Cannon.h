#pragma once
#include <windows.h>
#include <vector>
#include "CPPTankWar.h"
#include "Wall.h"
#include "mapEditor.h"

class CCannon
{
public:

	DWORD dwCannonWritten;
	COORD m_cannonPos;
	COORD m_cannonLastPos;
	int m_cannonDirection;
	int m_cannonID;
	bool isSuperCannon;
	static const int cannonMove[4][2][1];
	static const WORD cannonColor[2];


	CCannon(COORD startPOS, int startDirection, bool isSuper, int cannonID);
	~CCannon();

	bool isCannonAvailable;

	void cannonFly(int canID);

	void printCannon();

	void eraseCannon();

	friend class CTank;
	bool cannonHitTest();
private:

};

extern std::vector<CCannon> vecCan;