#if !defined(AFX_AutoDialog_H__45EC40C7_9FB4_478A_9B36_E0E578AE354E__INCLUDED_)
#define AFX_AutoDialog_H__45EC40C7_9FB4_478A_9B36_E0E578AE354E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAutoDialog form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CAutoDialog : public CDialog
{
public:
	CAutoDialog();
	DECLARE_DYNCREATE(CAutoDialog)

// Form Data
public:
	//{{AFX_DATA(CAutoDialog)
	enum { IDD = IDD_AUTO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoDialog();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	//{{AFX_MSG(CAutoDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AutoDialog_H__45EC40C7_9FB4_478A_9B36_E0E578AE354E__INCLUDED_)
