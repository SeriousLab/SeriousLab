// MapEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TankWar.h"


int wolfX[9] = { -2, 0, 2, -2, 0, 2, -2, 0, 2 };
int wolfY[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
//�����ϼ���Χש������仯

int rawMap[35][60] = { 0 };
//���������ͼ������

bool isWolf = false;
//����Ƿ��Ѿ������ϼ�

COORD wolfPOS;
//�ϼ�����

void mapEditor(COORD *saveCo)
{
	int nCurrentBrick = 0;
	//���ש������

	wchar_t cTitle[] = L"Map editor";
	SetConsoleTitle(cTitle);
	//���ñ���

	
	//tankwar.cpp�ﶨ��������������һ���ṹ��

// 	COORD coIndi;	//�����ʾ���ֵ�����
// 	COORD coSave;	//����������ԭ�����꣬��λʱ��
// 	SMALL_RECT srRawMap = { 0, 0, 139, 39 };
 	GetConsoleScreenBufferInfo(hStdOut, &csbiInitiatWindow);
// 	csbiRawMap.dwSize.X = 140;
// 	csbiRawMap.dwSize.Y = 40;
// 	SetConsoleScreenBufferSize(hStdOut, csbiRawMap.dwSize);
// 	SetConsoleWindowInfo(hStdOut, true, &srRawMap);
	//���������������С�����ô��ڴ�С
	void printMessage(char(*pmt)[20], int numOfEle);

	INPUT_RECORD irBuf[128];
	DWORD cNumRead;
	//������������¼��������ʵ�ʽ��յ�����

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
				printf("��");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	//���߿�
	printMessage(g_mapEditorM, sizeof(g_mapEditorM) / sizeof(g_mapEditorM[0]));

	SetConsoleMode(hStdIn, ENABLE_MOUSE_INPUT);
	//���������������

	while (true)
	{
		//��ѭ������ȡ���ͼ����¼�
		if (!ReadConsoleInput(hStdIn, irBuf, 128, &cNumRead))
		{
			continue;
		}
		//û���µ������¼��ͼ�����ѭ��

		unsigned int k = 0;
		for (; k < cNumRead; k++)
		{
			//�����¼�

			switch (irBuf[k].EventType)
			{
				//���¼�����ѡ����ʽ

			case KEY_EVENT:
			{
							  if (irBuf[k].Event.KeyEvent.wVirtualKeyCode == 0x51)
							  {
								  //�ж��˳�
								  selectBrickType(irBuf[k].Event.KeyEvent, &nCurrentBrick);
								  SetConsoleCursorPosition(hStdOut, *saveCo);
								  return;
							  }

							  selectBrickType(irBuf[k].Event.KeyEvent, &nCurrentBrick);
							  //���������¼�����
							  break;
			}
			case MOUSE_EVENT:
			{
								if (irBuf[k].Event.MouseEvent.dwButtonState == 1)
								{
									//ֻ������������µ����
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

	//�����¼�����
	switch (ker.wVirtualKeyCode)
	{
	case 0x31:case VK_NUMPAD1:
	{
				  //���ּ�1����ǽ
				  *currentBrick = BRICK;
				  return;
	}
	case 0x32:case VK_NUMPAD2:
	{
				  //���ּ�2���߿�
				  *currentBrick = OBS;
				  return;
	}
	case 0x33:case VK_NUMPAD3:
	{
				  //���ּ�3����ǽ
				  *currentBrick = IRON;
				  return;
	}
	case 0x34:case VK_NUMPAD4:
	{
				  //���ּ�4������
				  *currentBrick = WOLFPACK;
				  return;
	}
	case 0x30:case VK_NUMPAD0:
	{
				  //���ּ�0������
				  *currentBrick = EMPTY;
				  return;
	}
	case 0x51:
	{
				 //q���˳���ͼ�༭ģʽ
				 //�����ͼ���ļ�������ֱ�Ӷ��ļ�����ͼ
				 FILE *fpMap;
				 errno_t errTemp = fopen_s(&fpMap, "customMap", "w");
				 //�����ļ�ָ�룬���ļ�

				 for (int p = 0; p < 35; p++)
				 {
					 for (int q = 0; q < 60; q++)
					 {
						 fprintf_s(fpMap, "%d,", rawMap[p][q]);
					 }
				 }
				 //д���ļ�
				 fprintf_s(fpMap, "{%d,%d}", wolfPOS.X, wolfPOS.Y);
				 fclose(fpMap);
				 //�ر��ļ�ָ��

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
	//�߽��ж�
	if (mer.dwMousePosition.X % 2 != 0)
	{
		mer.dwMousePosition.X -= 1;
	}
	//��������
	SetConsoleCursorPosition(hstdout, mer.dwMousePosition);

	switch (*currentBrick)
	{
	case BRICK:
	{
				  if (pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] == 0)
				  {
					  printf("��");
					  pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = (*currentBrick);
				  }
				  return;
	}
	case IRON:
	{
				 if (pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] == 0)
				 {
					 printf("��");
					 pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = (*currentBrick);
				 }
				 return;
	}
	case OBS:
	{
				if (pMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] == 0)
				{
					printf("��");
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
						 printf("��");
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