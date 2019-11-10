#if !defined(AFX_ResultDialog_H__637E6A2D_4660_4E46_898D_439A8575A238__INCLUDED_)
#define AFX_ResultDialog_H__637E6A2D_4660_4E46_898D_439A8575A238__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultDialog form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CResultDialog : public CDialog
{
public:
	CResultDialog();
	DECLARE_DYNCREATE(CResultDialog)

// Form Data
public:
	//{{AFX_DATA(CResultDialog)
	enum { IDD = IDD_RESULT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

protected:
	CProgressCtrl m_prgsLeft, m_prgsRight;

// Operations
public:
	void UpdateResponseTime();
	void UpdateResult();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultDialog)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResultDialog();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	//{{AFX_MSG(CResultDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedRadio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CBrush m_brush, m_brushOriginal, m_brushBackground;
	CFont m_font, m_fontLG, m_fontNM, m_fontBold;
	void DrawRoundRect(CPaintDC * pDC, CWnd * pWnd, COLORREF crBackground);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ResultDialog_H__637E6A2D_4660_4E46_898D_439A8575A238__INCLUDED_)
