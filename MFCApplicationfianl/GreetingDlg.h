#pragma once


//byh header
#include <string>

// CGreetingDlg 대화 상자

class CGreetingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGreetingDlg)

public:
	CGreetingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGreetingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GREETING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	//byh member
public:
	BOOL OnInitDialog();
	
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnPaint();

	//background
	int greet_width;
	int greet_height;
	HBITMAP m_hBitmap; BITMAP m_bitmap;
	//btn
	CBitmapButton STARTBtn;
	CBitmapButton CANCELBtn;
	CBitmapButton BROWSEBtn;
	afx_msg void OnBnClickedButtonBrowsebtn();
	CString strPathName;
	CEdit BROWSEEdit;
	CEdit NICKNAMEEdit;
	CEdit SESSIONEdit;
	CButton CHECK1;
	CButton CHECK2;
	CButton CHECK3;
	CButton CHECK4;
	CButton CHECK5;
	CButton CHECK6;
	CButton CHECK7;
	CButton CHECK8;
	CButton CHECK9;
	CButton CHECK10;
	CComboBox COMBO1;
	CComboBox COMBO2;
	CComboBox COMBO3;
	CComboBox COMBO4;
	CComboBox COMBO5;
	CComboBox COMBO6;
	CComboBox COMBO7;
	CComboBox COMBO8;
	CComboBox COMBO9;
	CComboBox COMBO10;
};
