#pragma once
#include <windows.h>


#define TANKUP 0
#define TANKDOWN 2
#define TANKLEFT 1
#define TANKRIGHT 3

extern char g_mapEditorM[6][20];
//�ڵ�ͼ�༭��������ʾ����Ϣ
extern char g_mapLevel[12][20];
//�ؿ�
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
//̹�˷�����������
//�ڶ�άX��Y��
//����ά�����̹������ı仯
const int ammoDIR[4][2][1] = {
	{ { -1 }, { 0 } },
	{ { 0 }, { -1 } },
	{ { 1 }, { 0 } },
	{ { 0 }, { 1 } }
};

//�ڵ������������ң�
//����άͬ��

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

//�ڵ��ṹ��
//�ڵ�����
//�ڵ�����
//�ڵ�ɱ�˷�Χ
//�ڵ�����
//�ڵ��������±�
//����ָʾ��̹ͬ��

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

//̹�˽ṹ��
//̹������
//̹��װ��
//̹�˵�ҩ
//̹��Ѫ��
//̹������
//̹�˷���
//����ָʾ��0=�ϣ�1=��2=�£�3=��
//����flag

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

