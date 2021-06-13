// FormView2.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplicationfianl.h"
#include "FormView2.h"

#include "socket.h"
//queue
client_socket::S<3> dest_cap;
//textout
int same_name_cap = -1;
int font_size = 30;
double space_size = 1.7;
int caption_height = 300;
int minute_width = 600;

int max_cap_width;




//static: 값 유지
//static wchar_t* name_cap;
static CString name_cap_cstr;
//static wchar_t* talk_cap;
static CString talk_cap_cstr;
//출력 위치
static int count_x_cap;
static int count_y_cap;
//출력 유무
static boolean left_cap;
//이름 출력
static boolean name_text_out_cap;
//lines
static boolean line_invalidate;





// CFormView2

IMPLEMENT_DYNCREATE(CFormView2, CFormView)

CFormView2::CFormView2()
	: CFormView(IDD_FORMVIEW)
{

}

CFormView2::~CFormView2()
{
}

void CFormView2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormView2, CFormView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CFormView2 진단

#ifdef _DEBUG
void CFormView2::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormView2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG




BOOL CFormView2::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CFormView::OnEraseBkgnd(pDC);
	CBrush backBrush(RGB(0, 0, 0));               // 파랑색. 원하는 컬러를 너주면 된다...

	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect; pDC->GetClipBox(&rect);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);



	return TRUE;
}


int CFormView2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//max_cap_width = (::GetSystemMetrics(SM_CXSCREEN) - 50) - minute_width - 20;

	max_cap_width = (::GetSystemMetrics(SM_CXSCREEN) - 50) - minute_width - 20 - 40;

	//name_cap = _T("name");
	name_cap_cstr.Format(_T("%s"), _T("name"));
	//talk_cap = _T("talk");
	talk_cap_cstr.Format(_T("%s"), _T("talk"));
	//출력 위치
	count_x_cap = 10;//-space_x + 10;
	count_y_cap = 10;

	//출력 유무
	left_cap = false;
	//이름 출력
	name_text_out_cap = false;
	//change line
	line_invalidate = false;




	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(1, 1000, NULL);

	return 0;
}


void CFormView2::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CFormView::OnTimer(nIDEvent);

	left_cap = false;
	left_cap = client_socket::caption.try_pop(dest_cap);
	if (left_cap == false) {
		//OutputDebugString(_T("\n/////////////////TIMER : left_cap == false\n"));
	}
	else {
		//talk_cap = dest_cap.a[2];
		talk_cap_cstr.Format(_T("%s"), dest_cap.a[2]);
		//발화자가 다른 경우 strcmp != 0

		CString t_dest_cap_a1;
		t_dest_cap_a1.Format(_T("%s"), dest_cap.a[1]);
		same_name_cap = wcscmp(name_cap_cstr, t_dest_cap_a1);

		//같은 사람
		if (same_name_cap == 0) {

			talk_cap_cstr.Format(_T("%s"), dest_cap.a[2]);
			//출력결과가 size_caption_x 넘어가면 줄 바꿈
			if ((count_x_cap + talk_cap_cstr.GetLength() * font_size * space_size) >= max_cap_width) {
				count_x_cap = 10;
				count_y_cap += (font_size * 3);
			}


			// rc_cap.top, rc_cap.bottom, rc_cap.bottom - rc_cap.top
			//736 1080 344
			//300이면 끝이 잘린다. 일단은 250까지만 출력하기
			int temp = 50;
			if (count_y_cap + (font_size * 2) >= caption_height - temp) {

				//출력 위치 초기화
				//count_x_cap = 10;
				//count_y_cap = 10;

				line_invalidate = true;
				Invalidate();
			}

			CClientDC dc(this);
			CFont font, * pOldFont;
			font.CreatePointFont(font_size * 10, _T("Lucida Grande Bold"));
			pOldFont = (CFont*)dc.SelectObject(&font);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.SetBkMode(TRANSPARENT);

			dc.TextOut(
				//출력좌표 x, y,
				count_x_cap, count_y_cap,
				//텍스트 문자열
				talk_cap_cstr,
				//텍스트 문자열 길이
				talk_cap_cstr.GetLength()
			);
			count_x_cap += talk_cap_cstr.GetLength() * font_size * space_size;

		}
		//다르다
		else {
			//name_cap = dest_cap.a[1];
			name_cap_cstr.Format(_T("%s"), dest_cap.a[1]);
			talk_cap_cstr.Format(_T("%s"), dest_cap.a[2]);
			//이름 출력하기
			name_text_out_cap = true;
			//출력 위치 초기화
			//count_x_cap = 10;
			//count_y_cap = 10;

			//OutputDebugString(_T("Invalidate1\n"));
			Invalidate();
		}
	}


}


void CFormView2::OnDraw(CDC* pDC)
{
	//OutputDebugString(_T("Invalidate2\n"));
	if (left_cap == true) {
		CClientDC dc(this);
		CFont font, * pOldFont;
		font.CreatePointFont(font_size * 10, _T("Lucida Grande Bold"));
		pOldFont = (CFont*)dc.SelectObject(&font);
		dc.SetTextColor(RGB(255, 255, 255));
		dc.SetBkMode(TRANSPARENT);

		//name 출력
		if (name_text_out_cap == true) {
			count_x_cap = 10;
			count_y_cap = 10;
			dc.TextOut(count_x_cap, count_y_cap, name_cap_cstr, name_cap_cstr.GetLength());
			count_x_cap += name_cap_cstr.GetLength() * font_size * space_size;
			dc.TextOut(count_x_cap, count_y_cap, _T(":"), 1);
			count_x_cap += font_size * space_size;
			dc.TextOut(count_x_cap, count_y_cap, talk_cap_cstr, talk_cap_cstr.GetLength());
			count_x_cap += talk_cap_cstr.GetLength() * font_size * space_size;

			name_text_out_cap = false;
		}
		else if (line_invalidate == true) {
			count_x_cap = 10;
			count_y_cap = 10;
			dc.TextOut(count_x_cap, count_y_cap, talk_cap_cstr, talk_cap_cstr.GetLength());
			count_x_cap += talk_cap_cstr.GetLength() * font_size * space_size;
			line_invalidate == false;
		}
	}
	else {
		//OutputDebugString(_T("\n/////////////////PAINT : left_cap == false\n"));
	}
}