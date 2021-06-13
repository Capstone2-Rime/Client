#pragma once



// CMinuteScroll 폼 보기

class CMinuteScroll : public CFormView
{
	DECLARE_DYNCREATE(CMinuteScroll)

protected:
	CMinuteScroll();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMinuteScroll();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_MS };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


