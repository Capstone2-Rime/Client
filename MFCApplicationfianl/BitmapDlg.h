#pragma once
#include <afxdialogex.h>
class CBitmapDlg :
    public CDialogEx
{

	DECLARE_DYNAMIC(CBitmapDlg)

public:
	CBitmapDlg(CWnd* pParent = nullptr);   // ǥ�� �������Դϴ�.
	virtual ~CBitmapDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	//enum { IDD = IDD_DIALOG_GREET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.


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

