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
	"��1ѡ����ǽ��",
	"��2ѡ���ϰ���",
	"��3ѡ����ǽ��",
	"��4ѡ�����ѧ�",
	"��0ѡ�����",
	"��q���沢�˳��༭"
};

char g_welcomeM[10][20] = {
	"��1��ʼ������Ϸ",
	"��2��ʼ˫����Ϸ",
	"��3�����ͼ�༭",
	"��q�˳���Ϸ",
	"",
	"",
	"Project:Tank War",
	"Proudly presented",
	"by: Sirius",
	"Enjoy!"
};

char g_gamePlayM[9][20] = {
	"��һ��̹��",
	"������̹��",
	"������̹��",
	"���ļ�̹��",
	"���弶̹��",
	"������̹��"
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
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��"
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