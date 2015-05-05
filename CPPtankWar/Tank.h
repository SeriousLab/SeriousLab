#pragma once
#include <windows.h>



class CTank
{
public:
	CTank();
	~CTank();
private:
	COORD m_tankPOS;
	COORD m_tankLastPOS;
	int m_tankLevel;
	int m_tankArmor;
	int m_tankHealth;
	int m_tankDirection;
	int m_tankLastDirection;
	int m_tankID;
	bool m_isTankFriendly;
	bool m_isAlive;
	bool m_computerControl;
	void tankMove()
	{

	}
	void tankHitTest()
	{

	}
	void printTank()
	{

	}
};

