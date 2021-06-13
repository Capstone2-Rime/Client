#pragma once
#include <afxdialogex.h>
class CBitmapDlg :
    public CDialogEx
{

	DECLARE_DYNAMIC(CBitmapDlg)

public:
	CBitmapDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBitmapDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	//enum { IDD = IDD_DIALOG_GREET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


	DECLARE_MESSAGE_MAP()

public:
	BOOL OnInitDialog();

	CComboBox list;

	afx_msg void OnPaint();
	HBITMAP m_hBitmap; BITMAP m_bitmap;
};

class CBitmapDlg :
	public CDialogEx
{
};

