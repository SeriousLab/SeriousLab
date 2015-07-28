// ImportTable.cpp : implementation file
//

#include "stdafx.h"
#include "info_PE.h"
#include "ImportTable.h"
#include "afxdialogex.h"


// CImportTable dialog

IMPLEMENT_DYNAMIC(CImportTable, CDialogEx)

CImportTable::CImportTable(CWnd* pParent /*=NULL*/)
: CDialogEx(CImportTable::IDD, pParent)
{

}

CImportTable::~CImportTable()
{
}

void CImportTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST5, m_importDLL);
	DDX_Control(pDX, IDC_LIST6, m_importFunctions);
}


BEGIN_MESSAGE_MAP(CImportTable, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST5, &CImportTable::OnNMClickList5)
	//	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST5, &CImportTable::OnLvnKeydownList5)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST5, &CImportTable::OnLvnKeydownList5)
END_MESSAGE_MAP()


// CImportTable message handlers
void CImportTable::printImportDLL(PVOID lpBuf, DWORD dwSize)
{
	int DLLCounter = 0;

	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)lpBuf;
	PIMAGE_NT_HEADERS pNT = (PIMAGE_NT_HEADERS)((DWORD)lpBuf + pDos->e_lfanew);

	PIMAGE_DATA_DIRECTORY pDir = pNT->OptionalHeader.DataDirectory;
	PIMAGE_DATA_DIRECTORY pImportDir = &pDir[IMAGE_DIRECTORY_ENTRY_IMPORT];

	if (pDir[IMAGE_DIRECTORY_ENTRY_IMPORT].Size == 0 || pDir[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress == 0)
	{
		MessageBox(L"无导入表!");
		return;
	}

	size_t stImportOffset = RVA2Offset(pImportDir->VirtualAddress, lpBuf, dwSize);
	PIMAGE_IMPORT_DESCRIPTOR pImport = (PIMAGE_IMPORT_DESCRIPTOR)(stImportOffset + (size_t)lpBuf);

	while (pImport->Name)
	{
		size_t stNameOffset = RVA2Offset(pImport->Name, lpBuf, dwSize);
		PCHAR pstrName = (PCHAR)(stNameOffset + (size_t)lpBuf);
		size_t stIATOffset = RVA2Offset(pImport->FirstThunk, lpBuf, dwSize);
		size_t stINTOffset = RVA2Offset(pImport->OriginalFirstThunk, lpBuf, dwSize);

		wchar_t szName[MAX_PATH] = { 0 };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pstrName, -1, szName, MAX_PATH);
		wchar_t szIAT[MAX_PATH] = { 0 };
		wchar_t szINT[MAX_PATH] = { 0 };
		wsprintf(szIAT, L"%#08X", stIATOffset);
		wsprintf(szINT, L"%#08X", stINTOffset);
		m_importDLL.Additem(DLLCounter, 3, szName, szIAT, szINT);
		pImport++;
		DLLCounter++;
	}
}

size_t CImportTable::RVA2Offset(DWORD rVA, PVOID lpImage, DWORD dwSize)
{
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)lpImage;
	PIMAGE_NT_HEADERS32 pNT32 = (PIMAGE_NT_HEADERS32)((LONG)lpImage + pDos->e_lfanew);

	PIMAGE_FILE_HEADER pFileHeader = &(pNT32->FileHeader);

	for (WORD i = 0; i < pFileHeader->NumberOfSections; i++)
	{
		PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNT32);
		DWORD rVAbegin = pSection[i].VirtualAddress;
		DWORD rVAend = pSection[i].Misc.VirtualSize + pSection[i].VirtualAddress;
		if (rVA >= rVAbegin && rVA < rVAend)
		{
			return rVA - pSection[i].VirtualAddress + pSection[i].PointerToRawData;
		}

	}
	return -1;
}

BOOL CImportTable::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_importDLL.AddColumn(3, L"模块名称", 340, L"IAT文件偏移", 130, L"INT文件偏移", 130);
	m_importFunctions.AddColumn(4, L"索引", 100, L"函数名", 200, L"rVA", 150, L"偏移", 150);

	printImportDLL(lpFileImage, dwSize);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CImportTable::OnNMClickList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	POSITION pos = m_importDLL.GetFirstSelectedItemPosition();

	int nIndex = -1;
	nIndex = m_importDLL.GetNextSelectedItem(pos);

	wchar_t szIAT[MAX_PATH] = { 0 };
	wchar_t szINT[MAX_PATH] = { 0 };
	wchar_t *endPtr;

	m_importDLL.GetItemText(nIndex, 1, szIAT, MAX_PATH);
	m_importDLL.GetItemText(nIndex, 2, szINT, MAX_PATH);

	size_t stIAT, stINT;
	stIAT = wcstol(szIAT, &endPtr, 16);
	stINT = wcstol(szINT, &endPtr, 16);

	if (stIAT == 0 || stINT == 0)
	{
		m_importFunctions.DeleteAllItems();
		return;
	}
	if (stIAT == 0x7fffffff && stINT == 0x7fffffff)
	{
		MessageBox(L"IAT与INT地址无效!");
		return;
	}
	if (stINT == 0x7fffffff)
	{
		printImportFunctions(stIAT, stINT, TRUE);
	}
	else
	{
		printImportFunctions(stIAT, stINT, FALSE);
	}
	*pResult = 0;
}


void CImportTable::printImportFunctions(size_t iAT, size_t iNT, BOOL isIAT)
{
	m_importFunctions.DeleteAllItems();

	int nIndex = 0;

	PIMAGE_THUNK_DATA pIAT = (PIMAGE_THUNK_DATA)(iAT + (size_t)lpFileImage);
	PIMAGE_THUNK_DATA pINT = (PIMAGE_THUNK_DATA)(iNT + (size_t)lpFileImage);

	PIMAGE_THUNK_DATA pFunctions = nullptr;
	if (isIAT)
	{
		pFunctions = pIAT;
	}
	else
	{
		pFunctions = pINT;
	}

	while (pFunctions->u1.AddressOfData)
	{
		if (IMAGE_SNAP_BY_ORDINAL32(pFunctions->u1.AddressOfData))
		{
			wchar_t szRVA[MAX_PATH] = { 0 };
			wchar_t szOffset[MAX_PATH] = { 0 };
			wchar_t szOrdinal[MAX_PATH] = { 0 };
			wsprintf(szRVA, L"%#08X", pFunctions->u1.AddressOfData);
			size_t stOffset = RVA2Offset(pFunctions->u1.AddressOfData, lpFileImage, dwSize);
			wsprintf(szOffset, L"%#08X", stOffset);
			wsprintf(szOrdinal, L"%#04X", pFunctions->u1.Ordinal & 0x0000ffff);
			m_importFunctions.Additem(nIndex, 4, szOrdinal, L"-", szRVA, szOffset);
		}
		else
		{
			wchar_t szRVA[MAX_PATH] = { 0 };
			wchar_t szOffset[MAX_PATH] = { 0 };
			wchar_t szOrdinal[MAX_PATH] = { 0 };
			wchar_t szName[MAX_PATH] = { 0 };
			size_t stByNameOffset = RVA2Offset(pFunctions->u1.AddressOfData, lpFileImage, dwSize);
			PIMAGE_IMPORT_BY_NAME pByName = (PIMAGE_IMPORT_BY_NAME)(stByNameOffset + (size_t)lpFileImage);
			wsprintf(szRVA, L"%#08X", pFunctions->u1.AddressOfData);
			size_t stOffset = RVA2Offset(pFunctions->u1.AddressOfData, lpFileImage, dwSize);
			wsprintf(szOffset, L"%#08X", stOffset);
			wsprintf(szOrdinal, L"%#04X", pByName->Hint);
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pByName->Name, -1, szName, MAX_PATH);
			m_importFunctions.Additem(nIndex, 4, szOrdinal, szName, szRVA, szOffset);
		}
		pFunctions++;
		nIndex++;
	}
}



void CImportTable::OnLvnKeydownList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	POSITION pos = m_importDLL.GetFirstSelectedItemPosition();

	int nIndex = -1;
	nIndex = m_importDLL.GetNextSelectedItem(pos);

	switch (pLVKeyDow->wVKey)
	{
	case VK_UP:
	{
				  if (nIndex != 0)
				  {
					  nIndex -= 1;
				  }
				  else
				  {
					  return;
				  }
				  break;
	}
	case VK_DOWN:
	{
					if (nIndex < m_importDLL.GetItemCount() - 1)
					{
						nIndex += 1;
					}
					else
					{
						return;
					}
					break;
	}
	default:
		return;
	}

	wchar_t szIAT[MAX_PATH] = { 0 };
	wchar_t szINT[MAX_PATH] = { 0 };
	wchar_t *endPtr;

	m_importDLL.GetItemText(nIndex, 1, szIAT, MAX_PATH);
	m_importDLL.GetItemText(nIndex, 2, szINT, MAX_PATH);

	size_t stIAT, stINT;
	stIAT = wcstol(szIAT, &endPtr, 16);
	stINT = wcstol(szINT, &endPtr, 16);

	if (stIAT == 0 || stINT == 0)
	{
		m_importFunctions.DeleteAllItems();
		return;
	}
	if (stIAT == 0x7fffffff && stINT == 0x7fffffff)
	{
		MessageBox(L"IAT与INT地址无效!");
		return;
	}
	if (stINT == 0x7fffffff)
	{
		printImportFunctions(stIAT, stINT, TRUE);
	}
	else
	{
		printImportFunctions(stIAT, stINT, FALSE);
	}
	*pResult = 0;
}
