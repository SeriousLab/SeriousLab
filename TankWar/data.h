#pragma once
#include <windows.h>


#define TANKUP 0
#define TANKDOWN 2
#define TANKLEFT 1
#define TANKRIGHT 3

extern char g_mapEditorM[6][20];
//�ڵ�ͼ�༭��������ʾ����Ϣ
extern char g_mapLevel[11][20];
//�ؿ�

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
	int ammoType;
	int ammoRange;
	int directionIndex;
	bool isAvailable;
	bool isFriendly;
};

//�ڵ��ṹ��
//�ڵ�����
//�ڵ�����
//�ڵ�ɱ�˷�Χ
//�ڵ�����
//����ָʾ��̹ͬ��

struct tanks
{
	COORD tankPosition;
	int tankArmor;
	int tankAmmo;
	int tankHealth;
	int tankType;
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

