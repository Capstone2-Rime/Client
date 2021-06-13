// GreetingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplicationfianl.h"
#include "GreetingDlg.h"
#include "afxdialogex.h"


//byh header
#include "CExampleListener.h"
#include <string>
#include "socket.h"

IMPLEMENT_DYNAMIC(CGreetingDlg, CDialogEx)

CGreetingDlg::CGreetingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GREETING, pParent)
{

}

CGreetingDlg::~CGreetingDlg()
{
}

void CGreetingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, STARTBtn);
	DDX_Control(pDX, IDCANCEL, CANCELBtn);
	DDX_Control(pDX, IDC_BUTTON_BROWSEBtn, BROWSEBtn);
	DDX_Control(pDX, IDC_EDIT_BROWSEEdit, BROWSEEdit);
	DDX_Control(pDX, IDC_EDIT_NICKNAMEEdit, NICKNAMEEdit);
	DDX_Control(pDX, IDC_EDIT_SESSIONEdit, SESSIONEdit);
	DDX_Control(pDX, IDC_CHECK1, CHECK1);
	DDX_Control(pDX, IDC_CHECK2, CHECK2);
	DDX_Control(pDX, IDC_CHECK3, CHECK3);
	DDX_Control(pDX, IDC_CHECK4, CHECK4);
	DDX_Control(pDX, IDC_CHECK5, CHECK5);
	DDX_Control(pDX, IDC_CHECK6, CHECK6);
	DDX_Control(pDX, IDC_CHECK7, CHECK7);
	DDX_Control(pDX, IDC_CHECK8, CHECK8);
	DDX_Control(pDX, IDC_CHECK9, CHECK9);
	DDX_Control(pDX, IDC_CHECK10, CHECK10);
	DDX_Control(pDX, IDC_COMBO1, COMBO1);
	DDX_Control(pDX, IDC_COMBO2, COMBO2);
	DDX_Control(pDX, IDC_COMBO3, COMBO3);
	DDX_Control(pDX, IDC_COMBO4, COMBO4);
	DDX_Control(pDX, IDC_COMBO5, COMBO5);
	DDX_Control(pDX, IDC_COMBO6, COMBO6);
	DDX_Control(pDX, IDC_COMBO7, COMBO7);
	DDX_Control(pDX, IDC_COMBO8, COMBO8);
	DDX_Control(pDX, IDC_COMBO9, COMBO9);
	DDX_Control(pDX, IDC_COMBO10, COMBO10);
}


BEGIN_MESSAGE_MAP(CGreetingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_START, &CGreetingDlg::OnBnClickedButtonStart)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BROWSEBtn, &CGreetingDlg::OnBnClickedButtonBrowsebtn)
END_MESSAGE_MAP()



// CGreetingDlg 메시지 처리기
BOOL CGreetingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	greet_width = 1280; greet_height = 720;

	//MAIN
	m_hBitmap = LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_MAINBG_TOPIC)); GetObject(m_hBitmap, sizeof(BITMAP), &m_bitmap);

	int okbtn_width = 177; int okbtn_height = 59;
	//btn ok, cancel
	STARTBtn.LoadBitmaps(IDB_BITMAP_STARTBtn, IDB_BITMAP_STARTBtn);
	STARTBtn.SizeToContent();
	STARTBtn.MoveWindow(greet_width - okbtn_width * 3, greet_height - okbtn_height * 2.5, okbtn_width, okbtn_height);
	CANCELBtn.LoadBitmaps(IDB_BITMAP_CLOSEBtn, IDB_BITMAP_CLOSEBtn);
	CANCELBtn.SizeToContent();
	CANCELBtn.MoveWindow(greet_width - okbtn_width * 1.5, greet_height - okbtn_height * 2.5, okbtn_width, okbtn_height);


	int edit_width = (greet_width - okbtn_width * 1.5 + okbtn_width) - (greet_width - okbtn_width * 3);
	int edit_height = 50;


	//nickname, session
	NICKNAMEEdit.MoveWindow(greet_width - okbtn_width * 3, edit_height * 1, edit_width, edit_height);
	SESSIONEdit.MoveWindow(greet_width - okbtn_width * 3, edit_height * 3, edit_width, edit_height);


	//btn browse
	BROWSEEdit.MoveWindow(greet_width - okbtn_width * 3, edit_height * 5, okbtn_width * 2, okbtn_height);
	BROWSEBtn.LoadBitmaps(IDB_BITMAP_BROWSEDOTBtn, IDB_BITMAP_BROWSEDOTBtn);
	BROWSEBtn.SizeToContent();
	BROWSEBtn.MoveWindow(greet_width - okbtn_width * 3 + okbtn_width * 2 + 10, edit_height * 5, okbtn_height, okbtn_height);


	//check & combo
	int check_size = 20;
	int x_check_L = greet_width - okbtn_width * 3 - check_size;
	int y_check = edit_height * 5 + check_size * 4 + 5;
	int x_combo_L = x_check_L + check_size * 7.5;
	int y_combo = y_check - 5;
	int check_y_gap = check_size * 2 + 6;
	CHECK1.MoveWindow(x_check_L, y_check, check_size, check_size);
	COMBO1.AddString(_T("DEFAULT"));
	COMBO1.MoveWindow(x_combo_L, y_combo, check_size * 5, check_size);

	CHECK2.MoveWindow(x_check_L, y_check + check_y_gap, check_size, check_size);
	COMBO2.AddString(_T("DEFAULT"));
	COMBO2.MoveWindow(x_combo_L, y_combo + check_y_gap, check_size * 5, check_size);

	CHECK3.MoveWindow(x_check_L, y_check + check_y_gap * 2, check_size, check_size);
	COMBO3.AddString(_T("DEFAULT"));
	COMBO3.MoveWindow(x_combo_L, y_combo + check_y_gap * 2, check_size * 5, check_size);

	CHECK4.MoveWindow(x_check_L, y_check + check_y_gap * 3, check_size, check_size);
	COMBO4.AddString(_T("DEFAULT"));
	COMBO4.MoveWindow(x_combo_L, y_combo + check_y_gap * 3, check_size * 5, check_size);

	CHECK5.MoveWindow(x_check_L, y_check + check_y_gap * 4, check_size, check_size);
	COMBO5.AddString(_T("DEFAULT"));
	COMBO5.MoveWindow(x_combo_L, y_combo + check_y_gap * 4, check_size * 5, check_size);

	int x_check_R = x_combo_L + check_size * 5 + 30;
	int x_combo_R = x_check_R + check_size * 7;
	CHECK6.MoveWindow(x_check_R, y_check, check_size, check_size);
	COMBO6.AddString(_T("DEFAULT"));
	COMBO6.MoveWindow(x_combo_R, y_combo, check_size * 5, check_size);

	//7.자연과학
	CHECK7.MoveWindow(x_check_R, y_check + check_y_gap, check_size, check_size);
	COMBO7.AddString(_T("DEFAULT"));
	COMBO7.AddString(_T("생명/영양/식품"));
	COMBO7.AddString(_T("화학"));
	COMBO7.AddString(_T("물리"));
	COMBO7.AddString(_T("수학"));
	COMBO7.AddString(_T("지구과학"));
	COMBO7.MoveWindow(x_combo_R, y_combo + check_y_gap, check_size * 5, check_size);

	//8.공학
	CHECK8.MoveWindow(x_check_R, y_check + check_y_gap * 2, check_size, check_size);
	COMBO8.AddString(_T("DEFAULT"));
	COMBO8.AddString(_T("우주/천문/항공"));
	COMBO8.AddString(_T("건축/건설/토목"));
	COMBO8.AddString(_T("전기/전자"));
	COMBO8.AddString(_T("기계/자동차/금속"));
	COMBO8.MoveWindow(x_combo_R, y_combo + check_y_gap * 2, check_size * 5, check_size);

	//9.예술
	CHECK9.MoveWindow(x_check_R, y_check + check_y_gap * 3, check_size, check_size);
	COMBO9.AddString(_T("DEFAULT"));
	COMBO9.AddString(_T("미술"));
	COMBO9.AddString(_T("음악"));
	COMBO9.AddString(_T("건축"));
	COMBO9.MoveWindow(x_combo_R, y_combo + check_y_gap * 3, check_size * 5, check_size);

	CHECK10.MoveWindow(x_check_R, y_check + check_y_gap * 4, check_size, check_size);
	COMBO10.AddString(_T("DEFAULT"));
	COMBO10.AddString(_T("문학"));
	COMBO10.AddString(_T("언어"));
	COMBO10.AddString(_T("종교"));
	COMBO10.AddString(_T("철학/윤리"));
	COMBO10.AddString(_T("심리"));
	COMBO10.AddString(_T("인류학"));
	COMBO10.MoveWindow(x_combo_R, y_combo + check_y_gap * 4, check_size * 5, check_size);
	return true;
}

void CGreetingDlg::OnBnClickedButtonStart()
{
	//OutputDebugString(_T("\n\nzoom session\n\n"));
	CString cstr_nick;
	NICKNAMEEdit.GetWindowText(cstr_nick);
	CString cstr_session;
	SESSIONEdit.GetWindowText(cstr_session);


	
	CExampleListener* example = new CExampleListener(strPathName);



	ZoomInstantSDKSessionContext* sessionContext = new ZoomInstantSDKSessionContext();
	sessionContext->sessionName = L"cap0";
	sessionContext->sessionPassword = L"sPwd";


	
	sessionContext->userName = cstr_nick;
	sessionContext->token = cstr_session;



	sessionContext->videoOption.localVideoOn = false;
	sessionContext->audioOption.connect = true;
	sessionContext->audioOption.mute = false;

	example->JoinSession(sessionContext);

	
}


void CGreetingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	//CPaintDC dc(this);
	// device context for painting 
	CRect rect; GetWindowRect(&rect);
	// 스크린과 호환되는 DC생성. 
	HDC hMemDC = CreateCompatibleDC(dc);
	SetStretchBltMode(hMemDC, HALFTONE);
	// 호환DC에 비트맵을 선정. 
	SelectObject(hMemDC, m_hBitmap);
	// 메모리 DC에서 스크린 DC로 이미지 복사 
	//StretchBlt( dc, 0, 0, rect.Width(), rect.Height(), hMemDC, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY ); 



	StretchBlt(dc, 0, 0, greet_width, greet_height, hMemDC, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);

	// 메모리 DC삭제 
	DeleteDC(hMemDC);
	SetWindowPos(NULL, 30, 100, greet_width, greet_height, 0);

}


void CGreetingDlg::OnBnClickedButtonBrowsebtn()
{

	CString str = _T("All files(*.*)|*.*|"); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText(IDC_EDIT_BROWSEEdit, strPathName);
	}
}
