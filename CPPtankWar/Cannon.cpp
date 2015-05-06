#include "stdafx.h"
#include "Cannon.h"

const int CCannon::cannonMove[4][2][1] = {
	{ { 0 }, { -1 } },
	{ { 0 }, { 1 } },
	{ { -2 }, { 0 } },
	{ { 2 }, { 0 } }
};
CCannon::CCannon(COORD startPOS, int startDirection)
{
	m_cannonDirection = startDirection;
	m_cannonPos = startPOS;
	m_cannonLastPos.X = startPOS.X + cannonMove[startDirection][0][0];
	m_cannonLastPos.Y = startPOS.Y + cannonMove[startDirection][1][0];
}


CCannon::~CCannon()
{
}
