#pragma once
#include <windows.h>
#include <vector>

class CCannon
{
public:
	CCannon(COORD startPOS,int startDirection);
	~CCannon();
	
private:
	COORD m_cannonPos;
	COORD m_cannonLastPos;
	int m_cannonDirection;
	static const int cannonMove[4][2][1];

	void printCannon()
	{

	}
};

extern std::vector<CCannon> vecCan;