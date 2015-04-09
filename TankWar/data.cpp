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

char g_mapEditorM[6][20] = {
	"按1选择土墙▓",
	"按2选择障碍■",
	"按3选择铁墙〓",
	"按4选择狼窝Ж",
	"按0选择擦除",
	"按q保存并退出编辑"
};

char g_mapLevel[11][20] = {
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
	LEVELTEN
};

char ammosType[5][3] = {
	"¤",
	"☉",
	"⊕",
	"⊙",
	"◎"
};