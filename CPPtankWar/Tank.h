#pragma once
#include <windows.h>
#include "CPPTankWar.h"
#include "mapEditor.h"
#include "Wall.h"
#include <vector>
//#include "Cannon.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3



class CTank
{
public:
	bool m_computerControl;
	bool m_isAlive;
	int m_tankLevel;
	int m_tankHealth;
	COORD m_tankPOS;
	int m_tankDirection;
	COORD m_tankLastPOS;
	int m_tankLastDirection;
	bool m_isTankFriendly;
	bool m_isTraped;
	bool isZipped;
	bool m_isSuper;
	int m_tankID;
	int stepCount;
	static const WORD tankColor[2];


	CTank(int directionT, COORD tankPOS, int tankID, bool isFriendly, bool isComputer, bool isSuper);
	~CTank();
	void zipTank(HANDLE hOut)
	{
		eraseTank(hOut);
		isZipped = true;
		m_tankPOS = vecPortal[rand() % vecPortal.size()];
		while (tankHitTest(hOut))
		{
			m_tankPOS = vecPortal[rand() % vecPortal.size()];
		}
		printTank(hOut);
		m_tankLastPOS = m_tankPOS;
		m_tankLastDirection = m_tankDirection;
		stepCount = 0;
	}

	void setTankID(int id)
	{
		m_tankID = id;
	}
	void tankMove(int Tankdirection,HANDLE hOut);

	bool tankHitTest(HANDLE hOut);
	void printTank(HANDLE hOut);
	void eraseTank(HANDLE hOut);

	
private:

	
};

extern std::vector<CTank> vecTank;
extern const int tankDirect[4][2][6];
extern const int tankPOSmove[4][2][1];
extern const int mistCO[2][81];