// AutoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "sptx.h"
#include "AutoDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoDialog

IMPLEMENT_DYNCREATE(CAutoDialog, CDialog)

CAutoDialog::CAutoDialog()
	: CDialog(CAutoDialog::IDD)
{
	//{{AFX_DATA_INIT(CAutoDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAutoDialog::~CAutoDialog()
{
}

void CAutoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAutoDialog, CDialog)
	//{{AFX_MSG_MAP(CAutoDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoDialog diagnostics

#ifdef _DEBUG
void CAutoDialog::AssertValid() const
{
	CDialog::AssertValid();
}

void CAutoDialog::Dump(CDumpContext& dc) const
{
	CDialog::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoDialog message handlers
