// ConfigDialog.cpp : implementation file
//

#include "stdafx.h"
#include "sptx.h"
#include "ConfigDialog.h"
#include "AdminDialog.h"

#include <math.h>
#include "SPTXDoc.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDialog

IMPLEMENT_DYNCREATE(CConfigDialog, CDialog)

CConfigDialog::CConfigDialog()
	: CDialog(CConfigDialog::IDD)
{
	//{{AFX_DATA_INIT(CConfigDialog)
	m_brush.CreateSolidBrush(RGB(255, 255, 255));
	//}}AFX_DATA_INIT
}

CConfigDialog::~CConfigDialog()
{
}

void CConfigDialog::Revise() {
	CDataExchange dx(this, TRUE);

	UINT uMM;
	DDX_Text(&dx, IDC_UNIT_MM_EDIT, uMM);

	dx.m_bSaveAndValidate = FALSE;

	CSize sz = m_ptStart - m_ptEnd;
	FLOAT fPixel = sqrt((float)sz.cx * sz.cx + sz.cy * sz.cy);
	DDX_Text(&dx, IDC_UNIT_PIXEL_EDIT, fPixel);

	m_fUnit = uMM / fPixel;

	CString strUnit;
	strUnit.Format( _T("1 象素 = %.3f 毫米"), m_fUnit );
	DDX_Text(&dx, IDC_UNIT_EDIT, strUnit);

	OnEnKillfocusMmEdit();
}

FLOAT CConfigDialog::ShowTextBox()
{
	FLOAT rst = 0;
	for(int i=0; i<3; ++i) {
		if (((CButton *)GetDlgItem(IDC_RADIO_0 + i))->GetCheck() == 1) {
			GetDlgItem(IDC_MM_EDIT0 + i)->ShowWindow(SW_SHOW);
			CDataExchange dx(this, TRUE);
			DDX_Text(&dx, IDC_MM_EDIT0 + i, rst);
		}
		else
			GetDlgItem(IDC_MM_EDIT0 + i)->ShowWindow(SW_HIDE);
	}
	return rst;
}

void CConfigDialog::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	pDoc->m_bLining = FALSE;

	CDialog::OnCancel();
}

void CConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	CString strUnit;
	FLOAT fPixel;

	if (!pDX->m_bSaveAndValidate) {
		m_fUnit = pDoc->m_fUnit;
		m_ptStart = pDoc->m_ptStart;
		m_ptEnd = pDoc->m_ptEnd;

		strUnit.Format( _T("1 象素 = %.3f 毫米"), m_fUnit );
		fPixel = pDoc->m_arrMM[pDoc->m_nLevel] / m_fUnit;
	}

	//{{AFX_DATA_MAP(CConfigDialog)
	DDX_Text(pDX, IDC_UNIT_MM_EDIT, pDoc->m_uMM);
	DDX_Text(pDX, IDC_UNIT_PIXEL_EDIT, pDoc->m_fPixel);
	DDX_Text(pDX, IDC_UNIT_EDIT, strUnit);
	DDX_Text(pDX, IDC_MM_EDIT0, pDoc->m_arrMM[0]);
	DDX_Text(pDX, IDC_MM_EDIT1, pDoc->m_arrMM[1]);
	DDX_Text(pDX, IDC_MM_EDIT2, pDoc->m_arrMM[2]);
	DDX_Text(pDX, IDC_PIXEL_EDIT, fPixel);
	DDX_Radio(pDX, IDC_RADIO_0, pDoc->m_nLevel);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, pDoc->m_nInterval);
	DDX_Text(pDX, IDC_PSITV_EDIT, pDoc->m_nPassItv);
	DDX_Text(pDX, IDC_UPITV_EDIT, pDoc->m_nUnpsItv);
	DDX_Text(pDX, IDC_MOTOR_RATE, pDoc->m_fMotorRate);
	DDX_Text(pDX, IDC_ANGLE_RATE, pDoc->m_fAngleRate);
	DDX_Radio(pDX, IDC_RADIO_WISE1, pDoc->m_nWise);
	DDX_Text(pDX, IDC_ADD_RATE, pDoc->m_fAddRate);
	DDX_Text(pDX, IDC_ADD_STEP, pDoc->m_nAddStep);
	DDX_Text(pDX, IDC_EDIT_IP, pDoc->m_strIP);
	//}}AFX_DATA_MAP

	if (pDX->m_bSaveAndValidate) {
		pDoc->m_ptStart = m_ptStart;
		pDoc->m_ptEnd = m_ptEnd;
		pDoc->m_fUnit = m_fUnit;
	}
}


BEGIN_MESSAGE_MAP(CConfigDialog, CDialog)
	//{{AFX_MSG_MAP(CConfigDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_WM_CTLCOLOR()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_0, &CConfigDialog::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_1, &CConfigDialog::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_2, &CConfigDialog::OnBnClickedRadio)
	ON_EN_KILLFOCUS(IDC_MM_EDIT0, &CConfigDialog::OnEnKillfocusMmEdit)
	ON_EN_KILLFOCUS(IDC_MM_EDIT1, &CConfigDialog::OnEnKillfocusMmEdit)
	ON_EN_KILLFOCUS(IDC_MM_EDIT2, &CConfigDialog::OnEnKillfocusMmEdit)
	ON_EN_KILLFOCUS(IDC_UNIT_MM_EDIT, &CConfigDialog::OnEnKillfocusUnitMmEdit)
	ON_BN_CLICKED(IDC_SET_BUTTON, &CConfigDialog::OnBnClickedSetButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDialog diagnostics

#ifdef _DEBUG
void CConfigDialog::AssertValid() const
{
	CDialog::AssertValid();
}

void CConfigDialog::Dump(CDumpContext& dc) const
{
	CDialog::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CConfigDialog message handlers

HBRUSH CConfigDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_UNIT_PIXEL_EDIT) {
		// TODO:  在此更改 DC 的任何属性
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(RGB(255, 255, 255));
		// TODO:  如果默认的不是所需画笔，则返回另一个画笔
		return m_brush;
	}

	return hbr;
}

void CConfigDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	ShowTextBox();
}

void CConfigDialog::OnBnClickedRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	FLOAT fMM = ShowTextBox();
	FLOAT fPixel = fMM / m_fUnit;
	CDataExchange dx(this, FALSE);
	DDX_Text(&dx, IDC_PIXEL_EDIT, fPixel);
}

void CConfigDialog::OnEnKillfocusMmEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	FLOAT fMM = ShowTextBox();
	FLOAT fPixel = fMM / m_fUnit;
	CDataExchange dx(this, FALSE);
	DDX_Text(&dx, IDC_PIXEL_EDIT, fPixel);
}

void CConfigDialog::OnEnKillfocusUnitMmEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDataExchange dx(this, TRUE);

	UINT uMM;
	DDX_Text(&dx, IDC_UNIT_MM_EDIT, uMM);

	FLOAT fPixel;
	DDX_Text(&dx, IDC_UNIT_PIXEL_EDIT, fPixel);

	m_fUnit = uMM / fPixel;

	dx.m_bSaveAndValidate = FALSE;

	CString strUnit;
	strUnit.Format( _T("1 象素 = %.3f 毫米"), m_fUnit );
	DDX_Text(&dx, IDC_UNIT_EDIT, strUnit);

	OnEnKillfocusMmEdit();
}

void CConfigDialog::OnBnClickedSetButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CAdminDialog wndAdminDialog;
	if ( wndAdminDialog.DoModal() == IDOK ) {
		UpdateData(TRUE);
		((CMainFrame *) AfxGetMainWnd())->m_wndResultDialog.UpdateData(FALSE);
	}
}
