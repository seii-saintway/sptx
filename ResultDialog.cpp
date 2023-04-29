// ResultDialog.cpp : implementation file
//

#include "stdafx.h"
#include "sptx.h"
#include "ResultDialog.h"

#include "SPTXDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultDialog

IMPLEMENT_DYNAMIC(CResultDialog, CDialog)

CResultDialog::CResultDialog()
	: CDialog(CResultDialog::IDD)
{
	//{{AFX_DATA_INIT(CResultDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_brush.CreateSolidBrush(RGB(127, 127, 127));
	m_brushOriginal.CreateSolidBrush(RGB(240, 240, 240));

	m_font.CreatePointFont(100, _T("宋体"));
	m_fontLG.CreatePointFont(400, _T("宋体"));
	m_fontNM.CreatePointFont(300, _T("宋体"));
	m_fontBold.CreatePointFont(100, _T("微软雅黑"));
}

CResultDialog::~CResultDialog()
{
}

void CResultDialog::UpdateResponseTime()
{
	CDataExchange dx( this, FALSE );
	DDX_Text( &dx, IDC_RUN_TIME, pDoc->m_nResponseTime );
}

void CResultDialog::UpdateResult() {
	if ( pDoc->m_bSuccess ) {
		GetDlgItem(IDC_STOP)->ShowWindow(SW_HIDE);
		if ( pDoc->m_fDeviation < - pDoc->m_arrMM[ pDoc->m_nLevel ] ) {
			GetDlgItem(IDC_PASSED)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_UNPASSED)->ShowWindow(SW_SHOW);
			m_prgsLeft.SetPos(int((1 + pDoc->m_arrMM[ pDoc->m_nLevel ] / pDoc->m_fDeviation) * 100));
			m_prgsRight.SetPos(0);
		} else if ( pDoc->m_fDeviation > + pDoc->m_arrMM[ pDoc->m_nLevel ] ) {
			GetDlgItem(IDC_PASSED)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_UNPASSED)->ShowWindow(SW_SHOW);
			m_prgsLeft.SetPos(0);
			m_prgsRight.SetPos(int((1 - pDoc->m_arrMM[ pDoc->m_nLevel ] / pDoc->m_fDeviation) * 100));
		} else {
			GetDlgItem(IDC_PASSED)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_UNPASSED)->ShowWindow(SW_HIDE);
			m_prgsLeft.SetPos(0);
			m_prgsRight.SetPos(0);
		}
	} else {
		GetDlgItem(IDC_STOP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PASSED)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_UNPASSED)->ShowWindow(SW_HIDE);
		m_prgsLeft.SetPos(0);
		m_prgsRight.SetPos(0);
	}
	CString strDeviation;
	if ( pDoc->m_fDeviation < 0 )
		strDeviation.Format( _T("%.2f mm"), - pDoc->m_fDeviation );
	else
		strDeviation.Format( _T("%.2f mm"), + pDoc->m_fDeviation );
	CDataExchange dx( this, FALSE );
	DDX_Text( &dx, IDC_DEVIATION_EDIT, strDeviation );
}

BOOL CResultDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetLayeredWindowAttributes(RGB(127, 127, 127), 0, 0x1);

	CDataExchange dx( this, FALSE );
	DDX_Control( &dx, IDC_PROGRESS1, m_prgsLeft );
	DDX_Control( &dx, IDC_PROGRESS2, m_prgsRight );

	m_prgsLeft.SendMessage(PBM_SETBARCOLOR, 0, RGB(255, 0, 0));
	m_prgsLeft.SetPos(0);

	m_prgsRight.SendMessage(PBM_SETBARCOLOR, 0, RGB(255, 0, 0));
	m_prgsRight.SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CResultDialog::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Radio(pDX, IDC_RADIO0, pDoc->m_nLevel);
	DDX_Text(pDX, IDC_MAX_MM, pDoc->m_arrMM[pDoc->m_nLevel]);
	DDX_Text(pDX, IDC_WAITING_TIME, pDoc->m_nInterval);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CResultDialog, CDialog)
	//{{AFX_MSG_MAP(CResultDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO0, &CResultDialog::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO1, &CResultDialog::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO2, &CResultDialog::OnBnClickedRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultDialog diagnostics

#ifdef _DEBUG
void CResultDialog::AssertValid() const
{
	CDialog::AssertValid();
}

void CResultDialog::Dump(CDumpContext& dc) const
{
	CDialog::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResultDialog message handlers

void CResultDialog::DrawRoundRect(CPaintDC * pDC, CWnd * pWnd, COLORREF crBackground)
{
	m_brushBackground.CreateSolidBrush(crBackground);
	CBrush * oldBrush = (CBrush *) 
		pDC->SelectObject(&m_brushBackground);

	CRect rect;
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.InflateRect(10, 10);
	pDC->RoundRect(&rect, CPoint(10, 10));

	pDC->SelectObject(oldBrush);
	m_brushBackground.DeleteObject();
}

void CResultDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	DrawRoundRect(&dc, GetDlgItem(IDC_GROUP_LEFT), RGB(240, 240, 240));
	DrawRoundRect(&dc, GetDlgItem(IDC_GROUP_RIGHT), RGB(240, 240, 240));
	// 不为绘图消息调用 CDialog::OnPaint()
}

HBRUSH CResultDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何特性
	pDC->SetBkMode(TRANSPARENT);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SelectObject(&m_font);
	}
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_GROUP_LEFT:
	case IDC_GROUP_RIGHT:
		pDC->SelectObject(&m_font);
		break;
	case IDC_MAX_MM:
	case IDC_DEVIATION_EDIT:
		pDC->SelectObject(&m_fontLG);
		break;
	case IDC_DEVIATION:
		pDC->SelectObject(&m_fontNM);
		break;
	case IDC_RUN_TIME:
	case IDC_WAITING_TIME:
	case IDC_TODAY_OK:
	case IDC_ALL_OK:
		pDC->SelectObject(&m_fontBold);
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	switch (pWnd->GetDlgCtrlID()) {
	case IDC_MAX_MM:
	case IDC_RUN_TIME:
	case IDC_WAITING_TIME:
	case IDC_TODAY_OK:
	case IDC_ALL_OK:
		pDC->SetBkColor(RGB(240, 240, 240));
	case IDC_GROUP_LEFT:
	case IDC_GROUP_RIGHT:
	case IDC_STATIC:
	case IDC_RADIO0:
	case IDC_RADIO1:
	case IDC_RADIO2:
	case IDC_LEVEL:
		return m_brushOriginal;
	case IDC_DEVIATION_EDIT:
		pDC->SetBkColor(RGB(127, 127, 127));
	}
	return m_brush;
}

void CResultDialog::OnBnClickedRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	CDataExchange dx( this, TRUE );
	DDX_Radio( &dx, IDC_RADIO0, pDoc->m_nLevel );

	dx.m_bSaveAndValidate = FALSE;
	DDX_Text( &dx, IDC_MAX_MM, pDoc->m_arrMM[pDoc->m_nLevel] );
}
