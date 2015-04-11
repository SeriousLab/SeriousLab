#include "stdafx.h"
#include "data.h"



#define LOADGAME "initialization"
#define LEVELONE "twmOne"
#define LEVELTWO "twmTwo"
#define LEVELTHREE "twmThree"
#define LEVELFOUR "twmFour"
#define LEVELFIVE "twmFive"
#define LEVELSIX "twmSix"
#define LEVELSEVEN "twmSeven"
#define LEVELEIGHT "twmEight"
#define LEVELNINE "twmNine"
#define LEVELTEN "twmTen"
#define CUSTOMMAP "customMap"

char g_mapEditorM[6][20] = {
	"按1选择土墙▓",
	"按2选择障碍■",
	"按3选择铁墙〓",
	"按4选择狼窝Ж",
	"按0选择擦除",
	"按q保存并退出编辑"
};

char g_welcomeM[10][20] = {
	"按1开始单人游戏",
	"按2开始双人游戏",
	"按3进入地图编辑",
	"按q退出游戏",
	"",
	"",
	"Project:Tank War",
	"Proudly presented",
	"by: Sirius",
	"Enjoy!"
};

char g_gamePlayM[9][20] = {
	"□一级坦克",
	"□二级坦克",
	"□三级坦克",
	"□四级坦克",
	"□五级坦克",
	"□六级坦克"
};

char g_mapLevel[12][20] = {
	LOADGAME,
	LEVELONE,
	LEVELTWO,
	LEVELTHREE,
	LEVELFOUR,
	LEVELFIVE,
	LEVELSIX,
	LEVELSEVEN,
	LEVELEIGHT,
	LEVELNINE,
	LEVELTEN,
	CUSTOMMAP
};

char ammosType[7][3] = {
	"¤",
	"☉",
	"⊕",
	"⊙",
	"◎",
	"◎",
	"◎"
};

WORD tankColor[10] = {
	0x0002 | 0x0008,
	0x0001 | 0x0008,
	0x0002 | 0x0004 | 0x0008,
	0x0001 | 0x0004 | 0x0008,
	0x0001 | 0x0002 | 0x0008,
	0x0004 | 0x0008,
	0x0001 | 0x0002 | 0x0004,
	0x0001 | 0x0002 | 0x0004,
	0x0001 | 0x0002 | 0x0004,
	0x0001 | 0x0002 | 0x0004 |0x0008
};