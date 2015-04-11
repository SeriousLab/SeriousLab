#pragma once
#include <windows.h>


#define TANKUP 0
#define TANKDOWN 2
#define TANKLEFT 1
#define TANKRIGHT 3

extern char g_mapEditorM[6][20];
//在地图编辑器边上显示的信息
extern char g_mapLevel[12][20];
//关卡
extern char g_welcomeM[10][20];
extern char ammosType[7][3];
extern WORD tankColor[10];
extern char g_gamePlayM[9][20];

const int tankDIR[4][2][5] = {
	{ { -1, 0, 0, 1, 1 }, { 0, -1, 1, -1, 1 } },
	{ { -1, -1, 0, 1, 1 }, { 0, 1, -1, 0, 1 } },
	{ { -1, -1, 0, 0, 1 }, { -1, 1, -1, 1, 0 } },
	{ { -1, -1, 0, 1, 1 }, { -1, 0, 1, -1, 0 } }
};
//坦克方向，上下左右
//第二维X轴Y轴
//第三维，相对坦克坐标的变化
const int ammoDIR[4][2][1] = {
	{ { -1 }, { 0 } },
	{ { 0 }, { -1 } },
	{ { 1 }, { 0 } },
	{ { 0 }, { 1 } }
};

//炮弹方向，上下左右，
//后两维同上

struct ammos
{
	COORD ammoPosition;
	COORD lastCo;
	int ammoType;
	int ammoRange;
	int directionIndex;
	int ammoID;
	bool isAvailable;
	bool isFriendly;
};

//炮弹结构体
//炮弹坐标
//炮弹类型
//炮弹杀伤范围
//炮弹方向
//炮弹的数组下标
//方向指示，同坦克

struct tanks
{
	COORD tankPosition;
	int tankArmor;
	int tankAmmo;
	int tankHealth;
	int tankType;
	int tankID;
	int directionIndex;
	int previousIndex;
	bool isDead;
	bool isFriendly;
};

//坦克结构体
//坦克坐标
//坦克装甲
//坦克弹药
//坦克血量
//坦克类型
//坦克方向
//方向指示，0=上，1=左，2=下，3=右
//死亡flag

const int wolfPackPos[9][2][1] = {
	{ { -1 }, { -1 } },
	{ { -1 }, { 0 } },
	{ { -1 }, { 1 } },
	{ { 0 }, { -1 } },
	{ { 0 }, { 0 } },
	{ { 0 }, { 1 } },
	{ { 1 }, { -1 } },
	{ { 1 }, { 0 } },
	{ { 1 }, { 1 } }
};

