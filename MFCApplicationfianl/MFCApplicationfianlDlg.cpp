
// MFCApplication_fianlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationfianl.h"
#include "MFCApplicationfianlDlg.h"
#include "afxdialogex.h"

#include "FormView2.h"
#include "MinuteScroll.h"
#include "Black.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButton1();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCApplicationfianlDlg 대화 상자



CMFCApplicationfianlDlg::CMFCApplicationfianlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATIONFIANL_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationfianlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplicationfianlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMFCApplicationfianlDlg 메시지 처리기

BOOL CMFCApplicationfianlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	SetMenu(NULL);
	/*
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}*/


/*
	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	int nTransRatio = 10.0; // 50% 투명화

	int nAlpha = nTransRatio * 255 / 100;
	//SetLayeredWindowAttributes(RGB(0, 255, 0), nAlpha, LWA_ALPHA); // 투명 적용할 색상(RGB(255,0,255)) 설정
	SetLayeredWindowAttributes(RGB(0, 255, 0), nAlpha, LWA_COLORKEY);
*/
	

	screen_temp = 20;
	yuv_width = 640;
	yuv_height = 360;
	cxScreen = ::GetSystemMetrics(SM_CXSCREEN);  //화면너비
	cyScreen = ::GetSystemMetrics(SM_CYSCREEN);  //화면높이
	caption_height = 300;
	caption_width = yuv_width * 2 - screen_temp;
	//minute_width = cxScreen - caption_width;
	
	

	/*caption view*/
	CRect rc_cap;
	GetWindowRect(rc_cap);
	ScreenToClient(rc_cap);
	rc_cap.left = 0;
	rc_cap.top = yuv_height * 2 + screen_temp;
	rc_cap.bottom = cyScreen;
	rc_cap.right = caption_width - screen_temp;
	
	/*CString cap_size_cstr;
	cap_size_cstr.Format(_T("\n\n\n%d %d %d %d %d\n\n\n"), cxScreen, cyScreen, rc_cap.top, rc_cap.bottom, rc_cap.bottom - rc_cap.top);
	OutputDebugString(cap_size_cstr);*/

	CView* pView_cap = (CView*)RUNTIME_CLASS(CFormView2)->CreateObject();
	pView_cap->Create(nullptr, nullptr, WS_CHILD, rc_cap, this, IDD_FORMVIEW, 0);
	m_pFormView2 = pView_cap;
	m_pFormView2->ShowWindow(SW_SHOW);


	//minute view
	CRect rc_min;
	GetWindowRect(rc_min);
	ScreenToClient(rc_min);
	//minute view
	rc_min.top = 0;
	rc_min.right = cxScreen - screen_temp * 4;
	rc_min.bottom = rc_cap.bottom;
	rc_min.left = rc_cap.right;
	CView* pView_min = (CView*)RUNTIME_CLASS(CMinuteScroll)->CreateObject();
	pView_min->Create(nullptr, nullptr, WS_CHILD, rc_min, this, IDD_FORMVIEW_MS, 0);
	m_pFormViewMS = pView_min;
	m_pFormViewMS->ShowWindow(SW_SHOW);
	minute_width = rc_min.right - rc_min.left;

	//black_top
	CRect rc_black_top;
	GetWindowRect(rc_black_top);
	ScreenToClient(rc_black_top);
	rc_black_top.bottom = yuv_height / 2 + screen_temp * 2;
	rc_black_top.top = rc_min.top;
	rc_black_top.left = rc_cap.left;
	rc_black_top.right = rc_cap.right;

	CView* pView_black_TOP = (CView*)RUNTIME_CLASS(CBlack)->CreateObject();
	pView_black_TOP->Create(nullptr, nullptr, WS_CHILD, rc_black_top, this, IDD_FORMVIEW_BLACK, 0);
	m_pFormViewBlack_TOP = pView_black_TOP;
	m_pFormViewBlack_TOP->ShowWindow(SW_SHOW);

	//black_bottom
	CRect rc_black_bottom;
	GetWindowRect(rc_black_bottom);
	ScreenToClient(rc_black_bottom);
	rc_black_bottom.bottom = rc_cap.top;
	//bottom -> top
	rc_black_bottom.top = rc_black_bottom.bottom - (yuv_height/ 2+screen_temp);
	rc_black_bottom.left = rc_cap.left;
	rc_black_bottom.right = rc_cap.right;

	CView* pView_black_BOTTOM = (CView*)RUNTIME_CLASS(CBlack)->CreateObject();
	pView_black_BOTTOM->Create(nullptr, nullptr, WS_CHILD, rc_black_bottom, this, IDD_FORMVIEW_BLACK, 0);
	m_pFormViewBlack_BOTTOM = pView_black_BOTTOM;
	m_pFormViewBlack_BOTTOM->ShowWindow(SW_SHOW);

	//blac_left
	CRect rc_black_left;
	GetWindowRect(rc_black_left);
	ScreenToClient(rc_black_left);
	rc_black_left.top = rc_min.top;
	rc_black_left.bottom = rc_cap.top;
	rc_black_left.left = rc_cap.left;
	rc_black_left.right = yuv_width / 2 + screen_temp;

	CView* pView_black_LEFT = (CView*)RUNTIME_CLASS(CBlack)->CreateObject();
	pView_black_LEFT->Create(nullptr, nullptr, WS_CHILD, rc_black_left, this, IDD_FORMVIEW_BLACK, 0);
	m_pFormViewBlack_LEFT = pView_black_LEFT;
	m_pFormViewBlack_LEFT->ShowWindow(SW_SHOW);

	//blac_right
	CRect rc_black_right;
	GetWindowRect(rc_black_right);
	ScreenToClient(rc_black_right);
	rc_black_right.top = rc_min.top;
	rc_black_right.bottom = rc_cap.top;
	rc_black_right.left = rc_cap.right - (yuv_width/2+screen_temp);
	rc_black_right.right = rc_cap.right;

	CView* pView_black_RIGHT = (CView*)RUNTIME_CLASS(CBlack)->CreateObject();
	pView_black_RIGHT->Create(nullptr, nullptr, WS_CHILD, rc_black_right, this, IDD_FORMVIEW_BLACK, 0);
	m_pFormViewBlack_RIGHT = pView_black_RIGHT;
	m_pFormViewBlack_RIGHT->ShowWindow(SW_SHOW);


	//whole screen
	SetWindowPos(NULL, screen_temp*2, 0, cxScreen - screen_temp * 3, cyScreen , 0);


	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplicationfianlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplicationfianlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplicationfianlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CMFCApplicationfianlDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CDialogEx::OnEraseBkgnd(pDC);

	
	CBrush backBrush(RGB(0,255,0));               // 파랑색. 원하는 컬러를 너주면 된다...

	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect; pDC->GetClipBox(&rect);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
	

	


	
}

/*
HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	//return hbr;

	CBrush B;
	B.CreateStockObject(NULL_BRUSH);
	pDC->SetBkMode(TRANSPARENT); // 투명 설정 

	return B;


}*/


int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	this->MoveWindow(0, 0, 640*2, 360/2);


	return 0;
}


void CAboutDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
