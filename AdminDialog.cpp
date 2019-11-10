// AdminDialog.cpp : implementation file
//

#include "stdafx.h"
#include "sptx.h"
#include "AdminDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdminDialog

IMPLEMENT_DYNCREATE(CAdminDialog, CDialog)

CAdminDialog::CAdminDialog()
	: CDialog( CAdminDialog::IDD )
{
	//{{AFX_DATA_INIT(CAdminDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAdminDialog::~CAdminDialog()
{
}

void CAdminDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData( TRUE );
	if ( m_strPassword == "123456" )
		CDialog::OnOK();
	else
		MessageBox( _T("√‹¬Î¥ÌŒÛ£¨«Î÷ÿ–¬ ‰»Î£°") );
}

void CAdminDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdminDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdminDialog, CDialog)
	//{{AFX_MSG_MAP(CAdminDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdminDialog diagnostics

#ifdef _DEBUG
void CAdminDialog::AssertValid() const
{
	CDialog::AssertValid();
}

void CAdminDialog::Dump(CDumpContext& dc) const
{
	CDialog::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAdminDialog message handlers
