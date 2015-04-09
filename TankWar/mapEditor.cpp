// MapEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TankWar.h"


int wolfX[9] = { -2, 0, 2, -2, 0, 2, -2, 0, 2 };
int wolfY[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
//定义老家周围砖块坐标变化

int rawMap[35][60] = { 0 };
//用来保存地图的数组

bool isWolf = false;
//检查是否已经画了老家

COORD wolfPOS;
//老家坐标

void mapEditor(COORD *saveCo)
{
	int nCurrentBrick = 0;
	//标记砖块种类

	wchar_t cTitle[] = L"Map editor";
	SetConsoleTitle(cTitle);
	//设置标题

	
	//tankwar.cpp里定义过的两个句柄和一个结构体

// 	COORD coIndi;	//输出提示文字的坐标
// 	COORD coSave;	//用来保存光标原本坐标，复位时用
// 	SMALL_RECT srRawMap = { 0, 0, 139, 39 };
 	GetConsoleScreenBufferInfo(hStdOut, &csbiInitiatWindow);
// 	csbiRawMap.dwSize.X = 140;
// 	csbiRawMap.dwSize.Y = 40;
// 	SetConsoleScreenBufferSize(hStdOut, csbiRawMap.dwSize);
// 	SetConsoleWindowInfo(hStdOut, true, &srRawMap);
	//设置输出缓冲区大小，设置窗口大小
	void printMessage(char(*pmt)[20], int numOfEle);

	INPUT_RECORD irBuf[128];
	DWORD cNumRead;
	//定义接收输入事件的数组和实际接收到的量

	for (int x = 0; x < 35; x++)
	{
		rawMap[x][0] = OBS;
		rawMap[x][59] = OBS;
		for (int y = 0; y < 60; y++)
		{
			rawMap[0][y] = OBS;
			rawMap[34][y] = OBS;
		}
	}

	for (int i = 0; i < 35; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			if (rawMap[i][j] == OBS)
			{
				printf("■");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	//画边框
	printMessage(g_mapEditorM, sizeof(g_mapEditorM) / sizeof(g_mapEditorM[0]));

	SetConsoleMode(hStdIn, ENABLE_MOUSE_INPUT);
	//设置允许鼠标输入

	while (true)
	{
		//死循环来获取鼠标和键盘事件
		if (!ReadConsoleInput(hStdIn, irBuf, 128, &cNumRead))
		{
			continue;
		}
		//没有新的输入事件就继续死循环

		unsigned int k = 0;
		for (; k < cNumRead; k++)
		{
			//遍历事件

			switch (irBuf[k].EventType)
			{
				//从事件种类选择处理方式

			case KEY_EVENT:
			{
							  if (irBuf[k].Event.KeyEvent.wVirtualKeyCode == 0x51)
							  {
								  //判断退出
								  selectBrickType(irBuf[k].Event.KeyEvent, &nCurrentBrick);
								  SetConsoleCursorPosition(hStdOut, *saveCo);
								  return;
							  }

							  selectBrickType(irBuf[k].Event.KeyEvent, &nCurrentBrick);
							  //键盘输入事件处理
							  break;
			}
			case MOUSE_EVENT:
			{
								if (irBuf[k].Event.MouseEvent.dwButtonState == 1)
								{
									//只考虑鼠左键按下的情况
									drawBricks(hStdOut, irBuf[k].Event.MouseEvent, rawMap, &nCurrentBrick);
									break;
								}
								break;
			}
			default:
				break;
			}
		}
	}

	return;
}

void selectBrickType(KEY_EVENT_RECORD ker, int *currentBrick){

	//键盘事件处理
	switch (ker.wVirtualKeyCode)
	{
	case 0x31:case VK_NUMPAD1:
	{
				  //数字键1，土墙
				  *currentBrick = BRICK;
				  return;
	}
	case 0x32:case VK_NUMPAD2:
	{
				  //数字键2，边框
				  *currentBrick = OBS;
				  return;
	}
	case 0x33:case VK_NUMPAD3:
	{
				  //数字键3，铁墙
				  *currentBrick = IRON;
				  return;
	}
	case 0x34:case VK_NUMPAD4:
	{
				  //数字键4，老窝
				  *currentBrick = WOLFPACK;
				  return;
	}
	case 0x30:case VK_NUMPAD0:
	{
				  //数字键0，擦除
				  *currentBrick = EMPTY;
				  return;
	}
	case 0x51:
	{
				 //q键退出地图编辑模式
				 //输出地图到文件，可以直接读文件画地图
				 FILE *fpMap;
				 errno_t errTemp = fopen_s(&fpMap, "customMap", "w");
				 //定义文件指针，打开文件

				 for (int p = 0; p < 35; p++)
				 {
					 for (int q = 0; q < 60; q++)
					 {
						 fprintf_s(fpMap, "%d,", rawMap[p][q]);
					 }
				 }
				 //写入文件
				 fprintf_s(fpMap, "{%d,%d}", wolfPOS.X, wolfPOS.Y);
				 fclose(fpMap);
				 //关闭文件指针

				 return;
	}
	default:
		return;
	}

	return;
}

void drawBricks(HANDLE hstdout, MOUSE_EVENT_RECORD mer, int(*pMap)[60], int* currentBrick){
	if (mer.dwMousePosition.X > 117 || mer.dwMousePosition.Y > 33 || mer.dwMousePosition.X < 2 || mer.dwMousePosition.Y < 1)
	{
		return;
	}
	//边界判断
	if (mer.dwMousePosition.X % 2 != 0)
	{
		mer.dwMousePosition.X -= 1;
	}
	//奇数处理
	SetConsoleCursorPosition(hstdout, mer.dwMousePosition);

	switch (*currentBrick)
	{
	case BRICK:
	{
				  if (pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] == 0)
				  {
					  printf("▓");
					  pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = (*currentBrick);
				  }
				  return;
	}
	case IRON:
	{
				 if (pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] == 0)
				 {
					 printf("〓");
					 pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = (*currentBrick);
				 }
				 return;
	}
	case OBS:
	{
				if (pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] == 0)
				{
					printf("■");
					pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = (*currentBrick);
				}
				return;
	}
	case WOLFPACK:
	{
					 if (isWolf)
					 {
						 return;
					 }
					 if (mer.dwMousePosition.X > 115 || mer.dwMousePosition.X <= 3 || mer.dwMousePosition.Y > 32 || mer.dwMousePosition.Y <= 1)
					 {
						 return;
					 }
					 for (int z = 0; z < 9; z++)
					 {
						 if (pMap[mer.dwMousePosition.Y + wolfY[z]][mer.dwMousePosition.X / 2 + wolfX[z]] != 0)
						 {
							 return;
						 }
					 }
					 for (int t = 0; t < 9; t++)
					 {
						 COORD coTemp;
						 coTemp.X = mer.dwMousePosition.X + wolfX[t];
						 coTemp.Y = mer.dwMousePosition.Y + wolfY[t];
						 SetConsoleCursorPosition(hstdout, coTemp);
						 printf("Ж");
						 pMap[coTemp.Y][coTemp.X / 2] = WOLFPACK;
					 }
					 wolfPOS.X = mer.dwMousePosition.X;
					 wolfPOS.Y = mer.dwMousePosition.Y;
					 isWolf = true;
					 return;
	}
	case EMPTY:
	{
				  if (pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] == WOLFPACK)
				  {
					  for (int t = 0; t < 9; t++)
					  {
						  COORD coTemp;
						  coTemp.X = wolfPOS.X + wolfX[t];
						  coTemp.Y = wolfPOS.Y + wolfY[t];
						  SetConsoleCursorPosition(hstdout, coTemp);
						  pMap[coTemp.Y][coTemp.X / 2] = 0;
						  printf("  ");
					  }
					  isWolf = false;
					  return;
				  }
				  printf("  ");
				  pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = 0;
				  return;
	}
	default:
		return;

	}

	return;
}