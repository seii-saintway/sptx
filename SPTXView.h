// SPTXView.h : interface of the CSPTXView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPTXVIEW_H__E096B8B2_F612_4BA8_98F5_88298EADFDDF__INCLUDED_)
#define AFX_SPTXVIEW_H__E096B8B2_F612_4BA8_98F5_88298EADFDDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSPTXView : public CView
{
protected: // create from serialization only
	CSPTXView();
	DECLARE_DYNCREATE(CSPTXView)

// Attributes
public:
	CSPTXDoc* GetDocument();

protected:
	PBITMAPINFO m_pbmi;
	CDC m_dcMemory;
	CBitmap m_bm;

	INT m_nWidth, m_nHeight;
	BOOL m_bDrawing;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSPTXView)
protected:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSPTXView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSPTXView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in SPTXView.cpp
inline CSPTXDoc* CSPTXView::GetDocument()
   { return (CSPTXDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPTXVIEW_H__E096B8B2_F612_4BA8_98F5_88298EADFDDF__INCLUDED_)
