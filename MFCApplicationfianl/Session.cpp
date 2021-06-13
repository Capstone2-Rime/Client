// Session.cpp: 구현 파일
//
/*
#include "pch.h"
#include "MFCApplicationfianl.h"
#include "Session.h"
#include "afxdialogex.h"


// CSession 대화 상자

IMPLEMENT_DYNAMIC(CSession, CDialogEx)


//CSession::CSession(CWnd* pParent /*=nullptr)
CSession::CSession(CWnd* pParent )
	: CDialogEx(IDD_DIALOG_SESSION, pParent)
{

}

CSession::~CSession()
{
}

void CSession::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSession, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSession 메시지 처리기
BOOL CSession::OnInitDialog() {
	CSession::OnInitDialog();
	greet_width = 768; greet_height = 354;

	//MAIN
	m_hBitmap = LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_SESSION_START)); GetObject(m_hBitmap, sizeof(BITMAP), &m_bitmap);

	return true;
}

void CSession::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
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
*/