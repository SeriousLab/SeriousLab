#include "stdafx.h"
#include "tuiPOPUP.h"

const COORD tuiPOPUP::csbSizePUP = { 160, 40 };
const COORD tuiPOPUP::topLeftPOP = { 20, 5 };
WORD const popUPBack[4] = { BACKGROUND_GREEN | BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_INTENSITY,0 };

wchar_t* editorMessage[20] = {
	L" ",
	L"按 1 选择砖墙 ▓ , 一炮干死的渣渣",
	L" ",
	L"按 2 选择铁墙 〓 , 姑且算是个墙了",
	L" ",
	L"按 3 选择陷阱 ※ , 进去就别想出来",
	L" ",
	L"按 4 选择河流 ≈ , 发动机会进水的",
	L" ",
	L"按 5 选择草丛 ≡ , 跟敌人躲猫猫吧",
	L" ",
	L"按 6 选择地雷 × , 看不见但是致命",
	L" ",
	L"按 7 选择冰块 □ , 造个溜冰场玩玩",
	L" ",
	L"按 8 选择地道 Ω , 知道瞬间移动么",
	L" ",
	L"按 9 选择基岩 ■ , 核弹也炸不掉的",
	L" ",
	L"按 0 开始擦除   , 知错就改还是好同志"
};

wchar_t* welcomMessage[22] = {
	L"___________              __            __      __               ",
	L"\\__    ___/____    ____ |  | __       /  \\    /  \\_____ _______ ",
	L"  |    |  \\__  \\  /    \\|  |/ /       \\   \\/\\/   /\\__  \\\\_  __ \\",
	L"  |    |   / __ \\|   |  \\    <         \\        /  / __ \\|  | \\/",
	L"  |____|  (____  /___|  /__|_ \\         \\__/\\  /  (____  /__|   ",
	L"               \\/     \\/     \\/              \\/        \\/       ",
	L" ",
	L"按 1 开始单人游戏",
	L" ",
	L"按 2 开始双人游戏",
	L" ",
	L"按 3 选择游戏地图",
	L" ",
	L"按 4 载入储存游戏",
	L" ",
	L"按 5 查看获得成就",
	L" ",
	L"按 6 进入地图编辑",
	L" ",
	L"按 7 查看统计信息",
	L" ",
	L"按ESC退出坦克大战"
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
