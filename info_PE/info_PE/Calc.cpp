// Calc.cpp : implementation file
//

#include "stdafx.h"
#include "info_PE.h"
#include "Calc.h"
#include "afxdialogex.h"


// CCalc dialog

IMPLEMENT_DYNAMIC(CCalc, CDialogEx)

CCalc::CCalc(CWnd* pParent /*=NULL*/)
: CDialogEx(CCalc::IDD, pParent)
{

}

CCalc::~CCalc()
{
}

void CCalc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCalc, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CCalc::OnBnClickedButton2)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CCalc::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CCalc::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT2, &CCalc::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &CCalc::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, &CCalc::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CCalc message handlers


void CCalc::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	clearMessage();
	CEdit* edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT1);
	edit_value->EnableWindow(FALSE);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT3);
	edit_value->EnableWindow(FALSE);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT2);
	edit_value->EnableWindow(TRUE);
}


void CCalc::clearMessage()
{
	this->SetDlgItemTextW(IDC_EDIT1, L"");
	this->SetDlgItemTextW(IDC_EDIT2, L"");
	this->SetDlgItemTextW(IDC_EDIT3, L"");
}

// void CCalc::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
// {
// 	// TODO: Add your message handler code here and/or call default
// 
// 	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
// }

void CCalc::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	clearMessage();
	CEdit* edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT2);
	edit_value->EnableWindow(FALSE);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT3);
	edit_value->EnableWindow(FALSE);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT1);
	edit_value->EnableWindow(TRUE);
}




void CCalc::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	clearMessage();
	CEdit* edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT1);
	edit_value->EnableWindow(FALSE);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT2);
	edit_value->EnableWindow(FALSE);
	edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT3);
	edit_value->EnableWindow(TRUE);
}


void CCalc::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	

	CString szRVA;
	wchar_t *endPoint;
	CEdit* edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT2);

	if (!edit_value->IsWindowEnabled())
	{
		return;
	}

	edit_value->GetWindowTextW(szRVA);
	DWORD dwRVA = wcstol(szRVA, &endPoint, 16);
	if (dwRVA == 0)
	{
		return;
	}
	size_t stOffset = RVA2Offset(dwRVA, lpFileImage, dwSize);
	size_t stVA = rVA2VA(dwRVA, lpFileImage, dwSize);
	wchar_t szOffset[MAX_PATH] = { 0 };
	wchar_t szVA[MAX_PATH] = { 0 };
	_itow_s(stOffset, szOffset, 16);
	_itow_s(stVA, szVA, 16);
	this->SetDlgItemTextW(IDC_EDIT1, szVA);
	this->SetDlgItemTextW(IDC_EDIT3, szOffset);
	// TODO:  Add your control notification handler code here
}


size_t CCalc::RVA2Offset(DWORD rVA, PVOID lpImage, DWORD dwSize)
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

size_t CCalc::Offset2rVA(size_t offset, PVOID lpImage, DWORD dwSize)
{
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)lpImage;
	PIMAGE_NT_HEADERS32 pNT32 = (PIMAGE_NT_HEADERS32)((LONG)lpImage + pDos->e_lfanew);

	PIMAGE_FILE_HEADER pFileHeader = &(pNT32->FileHeader);

	for (WORD i = 0; i < pFileHeader->NumberOfSections; i++)
	{
		PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNT32);
		DWORD dwSecBegin = pSection[i].PointerToRawData;
		DWORD dwSecEnd = pSection[i].PointerToRawData + pSection[i].SizeOfRawData;
		if (offset >= dwSecBegin && offset < dwSecEnd)
		{
			return offset - pSection[i].PointerToRawData + pSection[i].VirtualAddress;
		}
	}
	return -1;
}

size_t CCalc::rVA2VA(size_t rVA, PVOID lpImage, DWORD dwSize)
{
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)lpImage;
	PIMAGE_NT_HEADERS32 pNT32 = (PIMAGE_NT_HEADERS32)((LONG)lpImage + pDos->e_lfanew);

	PIMAGE_OPTIONAL_HEADER32 pOptional = &(pNT32->OptionalHeader);

	return pOptional->ImageBase + rVA;
}

size_t CCalc::VA2rVA(size_t VA, PVOID lpImage, DWORD dwSize)
{
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)lpImage;
	PIMAGE_NT_HEADERS32 pNT32 = (PIMAGE_NT_HEADERS32)((LONG)lpImage + pDos->e_lfanew);

	PIMAGE_OPTIONAL_HEADER32 pOptional = &(pNT32->OptionalHeader);

	if (VA<pOptional->ImageBase)
	{
		return -1;
	}
	else
	{
		return VA - pOptional->ImageBase;
	}
}

void CCalc::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString szVA;
	wchar_t *endPoint;
	CEdit* edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT1);
	if (!edit_value->IsWindowEnabled())
	{
		return;
	}
	edit_value->GetWindowTextW(szVA);
	DWORD dwVA = wcstol(szVA, &endPoint, 16);
	if (dwVA == 0)
	{
		return;
	}
	size_t stRVA = VA2rVA(dwVA, lpFileImage, dwSize);
	size_t stOffset = RVA2Offset(stRVA, lpFileImage, dwSize);
	wchar_t szOffset[MAX_PATH] = { 0 };
	wchar_t szRVA[MAX_PATH] = { 0 };
	_itow_s(stOffset, szOffset, 16);
	_itow_s(stRVA, szRVA, 16);
	this->SetDlgItemTextW(IDC_EDIT2, szRVA);
	this->SetDlgItemTextW(IDC_EDIT3, szOffset);
	// TODO:  Add your control notification handler code here
}




void CCalc::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString szOffset;
	wchar_t *endPoint;
	CEdit* edit_value = (CEdit*)this->GetDlgItem(IDC_EDIT3);
	if (!edit_value->IsWindowEnabled())
	{
		return;
	}
	edit_value->GetWindowTextW(szOffset);
	DWORD dwOffset = wcstol(szOffset, &endPoint, 16);
	if (dwOffset == 0)
	{
		return;
	}
	size_t stRVA = Offset2rVA(dwOffset, lpFileImage, dwSize);
	size_t stVA = rVA2VA(stRVA, lpFileImage, dwSize);
	wchar_t szRVA[MAX_PATH] = { 0 };
	wchar_t szVA[MAX_PATH] = { 0 };
	_itow_s(stRVA, szRVA, 16);
	_itow_s(stVA, szVA, 16);
	this->SetDlgItemTextW(IDC_EDIT1, szVA);
	this->SetDlgItemTextW(IDC_EDIT2, szRVA);
	// TODO:  Add your control notification handler code here
}


BOOL CCalc::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	OnBnClickedButton2();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
