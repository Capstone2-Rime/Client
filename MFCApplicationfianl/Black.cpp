// Black.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplicationfianl.h"
#include "Black.h"


// CBlack

IMPLEMENT_DYNCREATE(CBlack, CFormView)

CBlack::CBlack()
	: CFormView(IDD_FORMVIEW_BLACK)
{

}

CBlack::~CBlack()
{
}

void CBlack::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBlack, CFormView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CBlack 진단

#ifdef _DEBUG
void CBlack::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBlack::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBlack 메시지 처리기


BOOL CBlack::OnEraseBkgnd(CDC* pDC)
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


int CBlack::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	this->MoveWindow(0, 0, 10, 10);
	return 0;
}
