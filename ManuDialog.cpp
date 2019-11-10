// ManuDialog.cpp : implementation file
//

#include "stdafx.h"
#include "sptx.h"
#include "ManuDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManuDialog

IMPLEMENT_DYNCREATE(CManuDialog, CDialog)

CManuDialog::CManuDialog()
	: CDialog(CManuDialog::IDD)
{
	//{{AFX_DATA_INIT(CManuDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CManuDialog::~CManuDialog()
{
}

void CManuDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManuDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManuDialog, CDialog)
	//{{AFX_MSG_MAP(CManuDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManuDialog diagnostics

#ifdef _DEBUG
void CManuDialog::AssertValid() const
{
	CDialog::AssertValid();
}

void CManuDialog::Dump(CDumpContext& dc) const
{
	CDialog::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CManuDialog message handlers
