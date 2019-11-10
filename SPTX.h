// SPTX.h : main header file for the SPTX application
//

#if !defined(AFX_SPTX_H__5EC82EB3_1AD9_42DA_B0CF_08AF51863BC1__INCLUDED_)
#define AFX_SPTX_H__5EC82EB3_1AD9_42DA_B0CF_08AF51863BC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#define HUNIT                           30
#define WUNIT                           40
#define RATE                            40
#define HEIGHT                          ( HUNIT * RATE )
#define WIDTH                           ( WUNIT * RATE )
#define STR_CFG_FILE_NAME               "Config.sptx"

#define WIDTH_BYTES(bits)                (((bits) + 31) / 32 * 4)

/////////////////////////////////////////////////////////////////////////////
// CSPTXApp:
// See SPTX.cpp for the implementation of this class
//

class CSPTXApp : public CWinApp
{
public:
	CSPTXApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSPTXApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSPTXApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPTX_H__5EC82EB3_1AD9_42DA_B0CF_08AF51863BC1__INCLUDED_)
