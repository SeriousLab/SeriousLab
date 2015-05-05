#include "stdafx.h"
#include <windows.h>
#include "mapEditor.h"
#include "Wall.h"
#include "tuiPOPUP.h"
#include "CPPTankWar.h"

int brickType = EMPTY;
bool tabONCE = false;
void mapEditor(HANDLE hIN, HANDLE hOUT)
{
	tuiPOPUP editorM(editorMessage, _countof(editorMessage));
	DWORD numReadorWrite = 0;
	drawMap(rawMap, hOUT);
	SetConsoleActiveScreenBuffer(hOUT);
	wchar_t titleMap[] = L"Map Editor";
	SetConsoleTitleW(titleMap);
	SetConsoleMode(hIN, ENABLE_MOUSE_INPUT);
	brickType = EMPTY;
	while (isEditor)
	{
		INPUT_RECORD irBuf[128];
		DWORD dwNumRead = 0;
		if (!ReadConsoleInput(hIN, irBuf, 128, &dwNumRead))
		{
			continue;
		}
		for (unsigned int i = 0; i < dwNumRead; i++)
		{
			switch (irBuf[i].EventType)
			{
			case KEY_EVENT:
			{

							  changeBrick(irBuf[i].Event.KeyEvent, hOUT, rawMap,editorM);
							  break;
			}
			case MOUSE_EVENT:
			{
								if (irBuf[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
								{
									drawONrawMap(irBuf[i].Event.MouseEvent, rawMap, hOUT, brickType);
								}
								break;
			}
			default:
				break;
			}
		}
	}
}

void changeBrick(KEY_EVENT_RECORD ker, HANDLE hOLD, int(*pRawMap)[80],tuiPOPUP& editorPOP)
{
	if (ker.bKeyDown)
	{
		switch (ker.wVirtualKeyCode)
		{
		case 0x31:case VK_NUMPAD1:
		{
					  brickType = BRICKWALL;
					  break;
		}
		case 0x32:case VK_NUMPAD2:
		{
					  brickType = IRONWALL;
					  break;
		}
		case 0x33:case VK_NUMPAD3:
		{
					  brickType = TRAP;
					  break;
		}
		case 0x34:case VK_NUMPAD4:
		{
					  brickType = RIVER;
					  break;
		}
		case 0x35:case VK_NUMPAD5:
		{
					  brickType = BUSH;
					  break;
		}
		case 0x36:case VK_NUMPAD6:
		{
					  brickType = MINE;
					  break;
		}
		case 0x37:case VK_NUMPAD7:
		{
					  brickType = ICE;
					  break;
		}
		case 0x38:case VK_NUMPAD8:
		{
					  brickType = PORTAL;
					  break;
		}
		case 0x39:case VK_NUMPAD9:
		{
					  brickType = BEDROCK;
					  break;
		}
		case 0x30:case VK_NUMPAD0:
		{
					  brickType = EMPTY;
					  break;
		}
		case VK_TAB:
		{
					   if (!tabONCE)
					   {
						   editorPOP.popUP();
						   tabONCE = true;
						   return;
					   }
					   return;
		}
		case VK_ESCAPE:
		{
						  FILE *fpMapOut;
						  fopen_s(&fpMapOut, "mapOut", "w");
						  for (int x = 0; x < 40; x++)
						  {
							  fprintf_s(fpMapOut, "{");
							  for (int y = 0; y < 80; y++)
							  {
								  fprintf_s(fpMapOut, "%d,", pRawMap[x][y]);
							  }
							  fprintf_s(fpMapOut, "a},\n");
						  }
						  fclose(fpMapOut);
						  isEditor = false;
						  return;
		}
		default:
			break;
		}
	}
	else
	{
		if (ker.wVirtualKeyCode == VK_TAB)
		{
			SetConsoleActiveScreenBuffer(hOLD);
			tabONCE = false;
			return;
		}
	}
}

void drawONrawMap(MOUSE_EVENT_RECORD mer, int(*pRawMap)[80], HANDLE hOUT, int& brickT)
{
	if (mer.dwMousePosition.X > 157 || mer.dwMousePosition.Y > 38 || mer.dwMousePosition.X < 2 || mer.dwMousePosition.Y < 1)
	{
		return;
	}
	if (mer.dwMousePosition.X % 2 != 0)
	{
		mer.dwMousePosition.X -= 1;
	}
	if (pRawMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] != 0 && brickT != 0)
	{
		return;
	}
	else
	{
		DWORD nWritten = 0;
		pRawMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = brickT;
		WriteConsoleOutputCharacter(hOUT, wallType[brickT / 11111 % 10], 1, mer.dwMousePosition, &nWritten);
		WriteConsoleOutputAttribute(hOUT, &wallColor[brickT / 11111 % 10], 1, mer.dwMousePosition, &nWritten);
		mer.dwMousePosition.X++;
		WriteConsoleOutputAttribute(hOUT, &wallColor[brickT / 11111 % 10], 1, mer.dwMousePosition, &nWritten);
	}
}