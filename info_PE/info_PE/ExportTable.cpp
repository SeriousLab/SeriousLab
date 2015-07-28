// ExportTable.cpp : implementation file
//

#include "stdafx.h"
#include "info_PE.h"
#include "ExportTable.h"
#include "afxdialogex.h"


// CExportTable dialog

IMPLEMENT_DYNAMIC(CExportTable, CDialogEx)

CExportTable::CExportTable(CWnd* pParent /*=NULL*/)
: CDialogEx(CExportTable::IDD, pParent)
{

}

CExportTable::~CExportTable()
{
}

void CExportTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST4, m_ExportTable);
}


BEGIN_MESSAGE_MAP(CExportTable, CDialogEx)
END_MESSAGE_MAP()


// CExportTable message handlers

void CExportTable::PrintExport(PVOID lpImage, DWORD dwSize)
{
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)lpImage;
	PIMAGE_NT_HEADERS pNT = (PIMAGE_NT_HEADERS)((DWORD)lpImage + pDos->e_lfanew);

	PIMAGE_DATA_DIRECTORY pDir = pNT->OptionalHeader.DataDirectory;
	PIMAGE_DATA_DIRECTORY pExportDir = &pDir[IMAGE_DIRECTORY_ENTRY_EXPORT];

	if (pDir[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == 0 || pDir[IMAGE_DIRECTORY_ENTRY_EXPORT].Size == 0)
	{
		MessageBox(L"无导出表!");
		pDos = nullptr;
		pNT = nullptr;
		pDir = nullptr;
		pExportDir = nullptr;
		return;
	}

	size_t stExportOffset = RVA2Offset(pExportDir->VirtualAddress, lpImage, dwSize);
	PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)(stExportOffset + (size_t)lpImage);
	if (pExport->Characteristics != 0)
	{
		MessageBox(L"导出表格式错误,无法解析!");
		pDos = nullptr;
		pNT = nullptr;
		pDir = nullptr;
		pExportDir = nullptr;
		pExport = nullptr;
		return;
	}
	size_t stNameOffset = RVA2Offset(pExport->Name, lpImage, dwSize);
	PCHAR pstrName = (PCHAR)(stNameOffset + (size_t)lpImage);
	size_t stEATOffset = RVA2Offset(pExport->AddressOfFunctions, lpImage, dwSize);
	size_t stENTOffset = RVA2Offset(pExport->AddressOfNames, lpImage, dwSize);
	size_t stEOTOffset = RVA2Offset(pExport->AddressOfNameOrdinals, lpImage, dwSize);
	PDWORD pEAT = (PDWORD)(stEATOffset + (size_t)lpImage);
	PDWORD pENT = (PDWORD)(stENTOffset + (size_t)lpImage);
	PWORD pEOT = (PWORD)(stEOTOffset + (size_t)lpImage);
	DWORD dwFunctionAddressCount = pExport->NumberOfFunctions;
	DWORD dwNameCount = pExport->NumberOfNames;

	wchar_t szName[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pstrName, -1, szName, MAX_PATH);
	CEdit* edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT1);
	edit_value->SetWindowTextW(szName);

	DWORD dwBase = pExport->Base;
	wchar_t szBase[MAX_PATH] = { 0 };
	wsprintf(szBase, L"%#08X", dwBase);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT2);
	edit_value->SetWindowTextW(szBase);

	wchar_t szFunctionCount[MAX_PATH] = { 0 };
	wsprintf(szFunctionCount, L"%#08X", dwFunctionAddressCount);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT3);
	edit_value->SetWindowTextW(szFunctionCount);

	wchar_t szNameCount[MAX_PATH] = { 0 };
	wsprintf(szNameCount, L"%#08X", dwNameCount);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT4);
	edit_value->SetWindowTextW(szNameCount);

	wchar_t szFunctionTable[MAX_PATH] = { 0 };
	wsprintf(szFunctionTable, L"%#08X", stEATOffset);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT5);
	edit_value->SetWindowTextW(szFunctionTable);

	wchar_t szNameTable[MAX_PATH] = { 0 };
	wsprintf(szNameTable, L"%#08X", stENTOffset);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT6);
	edit_value->SetWindowTextW(szNameTable);

	wchar_t szOrdinalTable[MAX_PATH] = { 0 };
	wsprintf(szOrdinalTable, L"%#08X", stEOTOffset);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT7);
	edit_value->SetWindowTextW(szOrdinalTable);

	for (DWORD Ordinal = 0; Ordinal < dwFunctionAddressCount; Ordinal++)
	{
		for (DWORD Index = 0; Index < dwNameCount; Index++)
		{
			if (pEOT[Index] == Ordinal)
			{
				size_t stName = RVA2Offset(pENT[Index], lpImage, dwSize);
				DWORD dwAddr = pEAT[Ordinal];
				DWORD dwOrdinal = Ordinal + pExport->Base;
				PCHAR pstrFunctionName = (PCHAR)(stName + (size_t)lpImage);
				wchar_t szAddr[MAX_PATH] = { 0 };
				wchar_t szOrdinal[MAX_PATH] = { 0 };
				wchar_t szFunctionName[MAX_PATH] = { 0 };
				wsprintf(szAddr, L"%#08X", dwAddr);
				wsprintf(szOrdinal, L"%#04X", dwOrdinal);
				MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pstrFunctionName, -1, szFunctionName, MAX_PATH);

				m_ExportTable.Additem(Ordinal, 3, szOrdinal, szAddr, szFunctionName);
				break;
			}
			if (Index == dwNameCount - 1)
			{
				DWORD dwAddr = pEAT[Ordinal];
				DWORD dwOrdinal = Ordinal + pExport->Base;
				wchar_t szAddr[MAX_PATH] = { 0 };
				wchar_t szOrdinal[MAX_PATH] = { 0 };
				wsprintf(szAddr, L"%#08X", dwAddr);
				wsprintf(szOrdinal, L"%#04X", dwOrdinal);

				m_ExportTable.Additem(Ordinal, 3, szOrdinal, szAddr, L"-");
			}
		}
	}
}

size_t CExportTable::RVA2Offset(DWORD rVA, PVOID lpImage, DWORD dwSize)
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


BOOL CExportTable::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	m_ExportTable.AddColumn(3, L"索引", 80, L"地址", 100, L"函数名", 180);

	PrintExport(lpImage, dwSize);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
