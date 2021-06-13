// MinuteScroll.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplicationfianl.h"
#include "MinuteScroll.h"
#include "socket.h"

//queue
client_socket::S<3> dest_min;
//textout
int same_name_min = -1;
int font_size_min = 15;
double space_size_min = 1.7;
//int caption_height = 300;
int minute_width_min = 600;

//int max_cap_width;




//static: 값 유지
//static wchar_t* name_cap;
static CString name_min_cstr;
//static wchar_t* talk_cap;
static CString talk_min_cstr;
//출력 위치
static int count_x_min;
static int count_y_min;
//출력 유무
static boolean left_min;
//이름 출력
//static boolean name_text_out_min;
//lines
//static boolean line_invalidate;

//(255, 204, 0)
int yellow = -1;


// CMinuteScroll

IMPLEMENT_DYNCREATE(CMinuteScroll, CFormView)

CMinuteScroll::CMinuteScroll()
	: CFormView(IDD_FORMVIEW_MS)
{

}

CMinuteScroll::~CMinuteScroll()
{
}

void CMinuteScroll::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMinuteScroll, CFormView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMinuteScroll 진단

#ifdef _DEBUG
void CMinuteScroll::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMinuteScroll::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMinuteScroll 메시지 처리기


BOOL CMinuteScroll::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CFormView::OnEraseBkgnd(pDC);
	CBrush backBrush(RGB(0, 17, 51));               // 파랑색. 원하는 컬러를 너주면 된다...

	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect; pDC->GetClipBox(&rect);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	return TRUE;
}


int CMinuteScroll::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	this->MoveWindow(0, 0, 0, ::GetSystemMetrics(SM_CYSCREEN) * 3); // 이부분을 추가하여 폼의 사이즈를 정한다.

	//max_cap_width = (::GetSystemMetrics(SM_CXSCREEN) - 50) - minute_width - 20;

	//name_cap = _T("name");
	name_min_cstr.Format(_T("%s"), _T("name"));
	//talk_cap = _T("talk");
	talk_min_cstr.Format(_T("%s"), _T("talk"));
	//출력 위치
	count_x_min = 10;//-space_x + 10;
	count_y_min = 10;

	//출력 유무
	left_min = false;
	//이름 출력
	//name_text_out_min = false;
	//change line
	//line_invalidate = false;




	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	//SetTimer(1, 1000, NULL);

	SetTimer(1, 1000, NULL);

	return 0;
}


void CMinuteScroll::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CFormView::OnTimer(nIDEvent);



	left_min = false;
	left_min = client_socket::caption_min.try_pop(dest_min);
	if (left_min == false) {
		//OutputDebugString(_T("\n/////////////////TIMER : left_cap == false\n"));
	}
	else {

		talk_min_cstr.Format(_T("%s"), dest_min.a[2]);
		//발화자가 다른 경우 strcmp != 0
		CString t_dest_min_a1;
		t_dest_min_a1.Format(_T("%s"), dest_min.a[1]);
		same_name_min = wcscmp(name_min_cstr, t_dest_min_a1);

		if (same_name_min != 0) {
			//색바꿈
			yellow *= (-1);
			//줄바꿈
			CString start;
			start.Format(_T("name"));
			if (wcscmp(name_min_cstr, start) != 0) {
				count_x_min = 10;
				count_y_min += (font_size_min * 6);
			}

			//이름출력
			name_min_cstr.Format(_T("%s"), dest_min.a[1]);
			CClientDC dc(this);
			CFont font, * pOldFont;
			font.CreatePointFont(font_size_min * 10, _T("Lucida Grande Bold"));
			pOldFont = (CFont*)dc.SelectObject(&font);
			if (yellow == -1) {
				dc.SetTextColor(RGB(255, 204, 0));
			}
			else {
				dc.SetTextColor(RGB(102, 255, 153));
			}
			dc.SetBkMode(TRANSPARENT);

			dc.TextOut(
				//출력좌표 x, y,
				count_x_min, count_y_min,
				//텍스트 문자열
				name_min_cstr,
				//텍스트 문자열 길이
				name_min_cstr.GetLength()
			);
			count_x_min += name_min_cstr.GetLength() * font_size_min * space_size_min;

			dc.TextOut(count_x_min, count_y_min, _T(":"), 1);
			count_x_min += font_size_min * space_size_min;
		}
		//else {


		talk_min_cstr.Format(_T("%s"), dest_min.a[2]);
		//출력결과가 size_caption_x 넘어가면 줄 바꿈
		if ((count_x_min + talk_min_cstr.GetLength() * font_size_min * space_size_min) >= (minute_width_min - 50 - 20)) {
			count_x_min = 10;
			count_y_min += (font_size_min * 3);
		}

		CClientDC dc(this);
		CFont font, * pOldFont;
		font.CreatePointFont(font_size_min * 10, _T("Lucida Grande Bold"));
		pOldFont = (CFont*)dc.SelectObject(&font);
		if (yellow == -1) {
			dc.SetTextColor(RGB(255, 204, 0));
		}
		else {
			dc.SetTextColor(RGB(102, 255, 153));
		}
		dc.SetBkMode(TRANSPARENT);

		//new push - space
		//새로 push할 때 띄어쓰기
		//int space =

		dc.TextOut(
			//출력좌표 x, y,
			count_x_min, count_y_min,
			//텍스트 문자열
			talk_min_cstr,
			//텍스트 문자열 길이
			talk_min_cstr.GetLength()
		);
		count_x_min += talk_min_cstr.GetLength() * font_size_min * space_size_min;
		//띄어쓰기
		//if (talk_min_cstr.GetLength() > 0) {
		count_x_min += font_size_min * 0.7;
		//}



	//}
	}
}
