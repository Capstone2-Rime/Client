#pragma once



// CFormView2 폼 보기

class CFormView2 : public CFormView
{
	DECLARE_DYNCREATE(CFormView2)

protected:
	CFormView2();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CFormView2();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
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
	void OnDraw(CDC* pDC);
};


