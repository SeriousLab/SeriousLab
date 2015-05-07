#pragma once
#include <windows.h>
#include <conio.h>

extern wchar_t* editorMessage[20];
extern wchar_t* welcomMessage[26];
extern WORD const popUPBack[4];
extern wchar_t* gamePlayinfo[30];
extern wchar_t* selectMap[19];
extern wchar_t* inGameInfo[18];

class tuiPOPUP
{
public:
	HANDLE hPOP;
	tuiPOPUP(wchar_t* pszMessage[], size_t lengthOfMessage);
	~tuiPOPUP();

	void popUP()
	{
		drawPOPUP();
		SetConsoleActiveScreenBuffer(hPOP);
	}

	void drawPOPUP()
	{
		COORD tempCO = topLeftPOP;
		for (int i = 0; i < 30; i++)
		{
			FillConsoleOutputAttribute(hPOP, popUPShadow, 120, tempCO, &m_numWritten);
			tempCO.Y++;
		}
		tempCO.X = topLeftPOP.X + 2;
		tempCO.Y = topLeftPOP.Y + 1;
		for (int i = 0; i < 28; i++)
		{
			FillConsoleOutputAttribute(hPOP, popUPColor, 116, tempCO, &m_numWritten);
			tempCO.Y++;
		}
		drawInfo();
	}
	void drawInfo()
	{
		COORD tempCO = topLeftPOP;
		tempCO.Y++;
		if (m_messageLen < 27)
		{
			for (int i = 0; i < m_messageLen; i++)
			{
				tempCO.Y ++;
				tempCO.X = (116 - wcslen(m_ptMessage[i])) / 2 + 18;
				WriteConsoleOutputCharacter(hPOP, m_ptMessage[i], wcslen(m_ptMessage[i]), tempCO, &m_numWritten);
			}
		}
		if (m_messageLen>26 && m_messageLen < 50)
		{
			for (int i = 0; i < m_messageLen; i++)
			{
				tempCO.X = (116 - wcslen(m_ptMessage[i])) / 2 + 18 + 29;
				if (i % 2 == 0)
				{
					tempCO.Y ++;
					tempCO.X = (58 - wcslen(m_ptMessage[i])) / 2 + 18;
				}
				WriteConsoleOutputCharacter(hPOP, m_ptMessage[i], wcslen(m_ptMessage[i]), tempCO, &m_numWritten);
			}
		}
	}
	void randomBack()
	{
		for (int i = 0; i < 3000;i++)
		{
			COORD tempCO = { rand() % 80 * 2, rand() % 40 };
			FillConsoleOutputAttribute(hPOP, popUPBack[rand() % 4], 2, tempCO, &m_numWritten);
		}
	}
private:
	DWORD m_numWritten = 0;
	WORD const popUPColor = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
	WORD const popUPShadow = BACKGROUND_INTENSITY;
	static const COORD csbSizePUP;
	static const COORD  topLeftPOP;
	wchar_t** m_ptMessage;
	int m_messageLen;
};
