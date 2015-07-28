#pragma once


// CCalc dialog

class CCalc : public CDialogEx
{
	DECLARE_DYNAMIC(CCalc)

public:
	CCalc(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCalc();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	void clearMessage();
	//afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit2();
	size_t RVA2Offset(DWORD rVA, PVOID lpImage, DWORD dwSize);
	size_t Offset2rVA(size_t offset, PVOID lpImage, DWORD dwSize);
	size_t rVA2VA(size_t rVA, PVOID lpImage, DWORD dwSize);
	size_t VA2rVA(size_t VA, PVOID lpImage, DWORD dwSize);
	DWORD dwSize = 0;
	PVOID lpFileImage = nullptr;
	
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit3();
	virtual BOOL OnInitDialog();
};
