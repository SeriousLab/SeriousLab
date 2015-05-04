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
	bool m_isTankFriendly;
	int m_tankLevel;
	int m_tankArmor;
	int m_tankHealth;
	int m_tankDirection;
	int m_tankLastDirection;
	int m_tankID;
	bool m_computerControl;
};

