#include "stdafx.h"
#include "tuiPOPUP.h"

const COORD tuiPOPUP::csbSizePUP = { 160, 40 };
const COORD tuiPOPUP::topLeftPOP = { 20, 5 };
WORD const popUPBack[4] = { BACKGROUND_GREEN | BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_INTENSITY,0 };

wchar_t* editorMessage[20] = {
	L" ",
	L"�� 1 ѡ��שǽ �� , һ�ڸ���������",
	L" ",
	L"�� 2 ѡ����ǽ �� , �������Ǹ�ǽ��",
	L" ",
	L"�� 3 ѡ������ �� , ��ȥ�ͱ������",
	L" ",
	L"�� 4 ѡ����� �� , ��ʵֻ�Ǹ�װ��",
	L" ",
	L"�� 5 ѡ��ݴ� �� , �����˶�èè��",
	L" ",
	L"�� 6 ѡ����� �� , ��������������",
	L" ",
	L"�� 7 ѡ����� �� , ������������",
	L" ",
	L"�� 8 ѡ��ص� �� , ֪��˲���ƶ�ô",
	L" ",
	L"�� 9 ѡ����� �� , �˵�Ҳը������",
	L" ",
	L"�� 0 ��ʼ����   , ֪��͸Ļ��Ǻ�ͬ־"
};

wchar_t* welcomMessage[26] = {
	L"___________              __            __      __               ",
	L"\\__    ___/____    ____ |  | __       /  \\    /  \\_____ _______ ",
	L"  |    |  \\__  \\  /    \\|  |/ /       \\   \\/\\/   /\\__  \\\\_  __ \\",
	L"  |    |   / __ \\|   |  \\    <         \\        /  / __ \\|  | \\/",
	L"  |____|  (____  /___|  /__|_ \\         \\__/\\  /  (____  /__|   ",
	L"               \\/     \\/     \\/              \\/        \\/       ",
	L" ",
	L"�� 1 ��ʼ������Ϸ",
	L" ",
	L"�� 2 ��ʼ˫����Ϸ",
	L" ",
	L"�� 3 ѡ����Ϸ��ͼ",
	L" ",
	L"�� 4 ���봢����Ϸ",
	L" ",
	L"�� 5 �鿴��óɾ�",
	L" ",
	L"�� 6 �����ͼ�༭",
	L" ",
	L"�� 7 �鿴ͳ����Ϣ",
	L" ",
	L"�� 8 ����ģʽ���",
	L" ",
	L"�� 9 ̽��ģʽ���",
	L" ",
	L"��ESC�˳�̹�˴�ս"
};

wchar_t* gamePlayinfo[30] = {
	L"��� 1 ����˵��",
	L"��� 2 ����˵��",
	L" ",
	L" ",
	L"�� �� �����ƶ�",
	L"�� W �����ƶ�",
	L" ",
	L" ",
	L"�� �� �����ƶ�",
	L"�� A �����ƶ�",
	L" ",
	L" ",
	L"�� �� �����ƶ�",
	L"�� S �����ƶ�",
	L" ",
	L" ",
	L"�� �� �����ƶ�",
	L"�� D �����ƶ�",
	L" ",
	L" ",
	L"��SPACE�����ڵ�",
	L"��ENTER�����ڵ�",
	L" ",
	L" ",
	L" ",
	L" ",
	L"�� TAB �鿴��Ϣ",
	L"�� ESC �˳���Ϸ",
	L" ",
	L" "
};

wchar_t* selectMap[19] = {
	L"�� 1 ѡ���ȴ�����",
	L" ",
	L" ",
	L"�� 2 ѡ���������",
	L" ",
	L" ",
	L"�� 3 ѡ�񲽲�����",
	L" ",
	L" ",
	L"�� 4 ѡ�����Ǳ߼�",
	L" ",
	L" ",
	L"�� 5 ѡ�������//����Ĺ�û��",
	L" ",
	L" ",
	L"�� 6 ѡ��ɵ���",
	L" ",
	L" ",
	L"�� 7 ��������ͼ"
};

wchar_t* inGameInfo[18] = {
	L" ",
	L" ",
	L" ",
	L" ",
	L" ",
	L" ",
	L" ",
	L" ",
	L"����̫��������ûд...",
	L" ",
	L" ",
	L" ",
	L" ",
	L" ",
	L" ",
	L" ",
	L" ",
	L" "
};
tuiPOPUP::tuiPOPUP(wchar_t* pszMessage[], size_t lengthOfMessage)
{
	hPOP = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hPOP, csbSizePUP);
	CONSOLE_CURSOR_INFO cciPUP;
	cciPUP.bVisible = false;
	cciPUP.dwSize = 1;
	SetConsoleCursorInfo(hPOP, &cciPUP);
	m_ptMessage = pszMessage;
	m_messageLen = lengthOfMessage;
	randomBack();
}


tuiPOPUP::~tuiPOPUP()
{
	CloseHandle(hPOP);
}
