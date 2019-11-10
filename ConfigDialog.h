#if !defined(AFX_ConfigDialog_H__F5C77EAB_FE51_4EA0_8ABA_41EDA7574606__INCLUDED_)
#define AFX_ConfigDialog_H__F5C77EAB_FE51_4EA0_8ABA_41EDA7574606__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDialog form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CConfigDialog : public CDialog
{
public:
	CConfigDialog();
	DECLARE_DYNCREATE(CConfigDialog)

// Form Data
public:
	//{{AFX_DATA(CConfigDialog)
	enum { IDD = IDD_CONFIGURATION };
	FLOAT m_fUnit;
	CPoint m_ptStart, m_ptEnd;
	//}}AFX_DATA

// Attributes
public:

protected:
	CBrush m_brush;

// Operations
public:
	void Revise();

protected:
	FLOAT ShowTextBox();

// Overrides
protected:
	virtual void OnCancel();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDialog)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConfigDialog();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	//{{AFX_MSG(CConfigDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedRadio();
	afx_msg void OnEnKillfocusMmEdit();
	afx_msg void OnEnKillfocusUnitMmEdit();
	afx_msg void OnBnClickedSetButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ConfigDialog_H__F5C77EAB_FE51_4EA0_8ABA_41EDA7574606__INCLUDED_)
