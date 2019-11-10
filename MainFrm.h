// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__FCBBFD3A_E9C7_43D9_85AC_5336CBCE0C77__INCLUDED_)
#define AFX_MAINFRM_H__FCBBFD3A_E9C7_43D9_85AC_5336CBCE0C77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResultDialog.h"
#include "ConfigDialog.h"
#include "AdminDialog.h"
#include "ManuDialog.h"
#include "AutoDialog.h"

#include <pylon/PylonIncludes.h>
#include <pylon/PylonGUI.h>
using namespace Pylon;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

protected:
	CInstantCamera camera;

// Operations
public:

protected:
	void Snap();
	BOOL Locate();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar    m_wndToolBar;

public:
	CResultDialog  m_wndResultDialog;
	CConfigDialog  m_wndConfigDialog;
	CManuDialog    m_wndManuDialog;
	CAutoDialog    m_wndAutoDialog;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnAperture();
	afx_msg void OnConfiguration();
	afx_msg void OnManu();
	afx_msg void OnAuto();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__FCBBFD3A_E9C7_43D9_85AC_5336CBCE0C77__INCLUDED_)
