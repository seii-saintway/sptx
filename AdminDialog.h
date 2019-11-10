#if !defined(AFX_AdminDialog_H__E79E8455_E67E_4C78_9432_9C9DA1806E03__INCLUDED_)
#define AFX_AdminDialog_H__E79E8455_E67E_4C78_9432_9C9DA1806E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdminDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdminDialog form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CAdminDialog : public CDialog
{
public:
	CAdminDialog();
	DECLARE_DYNCREATE(CAdminDialog)

// Form Data
public:
	//{{AFX_DATA(CAdminDialog)
	enum { IDD = IDD_ADMINISTRATOR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

protected:
	CString	m_strPassword;

// Operations
public:

// Overrides
protected:
	virtual void OnOK();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdminDialog)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAdminDialog();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	//{{AFX_MSG(CAdminDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AdminDialog_H__E79E8455_E67E_4C78_9432_9C9DA1806E03__INCLUDED_)
