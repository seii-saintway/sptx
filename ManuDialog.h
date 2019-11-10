#if !defined(AFX_ManuDialog_H__F92CCF71_3F41_4E0F_B47B_67CF6FA2DAE7__INCLUDED_)
#define AFX_ManuDialog_H__F92CCF71_3F41_4E0F_B47B_67CF6FA2DAE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManuDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManuDialog form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CManuDialog : public CDialog
{
public:
	CManuDialog();
	DECLARE_DYNCREATE(CManuDialog)

// Form Data
public:
	//{{AFX_DATA(CManuDialog)
	enum { IDD = IDD_MANU };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManuDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CManuDialog();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	//{{AFX_MSG(CManuDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ManuDialog_H__F92CCF71_3F41_4E0F_B47B_67CF6FA2DAE7__INCLUDED_)
