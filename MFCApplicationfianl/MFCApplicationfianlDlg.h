
// MFCApplicationfianlDlg.h: 헤더 파일
//

#pragma once


// CMFCApplicationfianlDlg 대화 상자
class CMFCApplicationfianlDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplicationfianlDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONFIANL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	
	
	DECLARE_MESSAGE_MAP()

public:
	BOOL OnEraseBkgnd(CDC* pDC);
	CView* m_pFormView2;
	CView* m_pFormViewMS;
	CView* m_pFormViewBlack_TOP;
	CView* m_pFormViewBlack_BOTTOM;
	CView* m_pFormViewBlack_LEFT;
	CView* m_pFormViewBlack_RIGHT;

	int screen_temp;
	int cxScreen;
	int cyScreen;
	int caption_height;
	int caption_width;
	int minute_width;
	int yuv_width;
	int yuv_height;
};
