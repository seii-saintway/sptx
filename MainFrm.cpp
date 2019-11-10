// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SPTX.h"
#include "SPTXDoc.h"
#include "ResultDialog.h"
#include "ConfigDialog.h"
#include "AdminDialog.h"
#include "ManuDialog.h"
#include "AutoDialog.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BYTE * pImage = NULL;

class Counter
{
public:
	Counter();
	~Counter();

private:
	LONGLONG m_llFrequency, m_llCountBegin, m_llCountEnd;
};

Counter::Counter()
{
	QueryPerformanceFrequency( (PLARGE_INTEGER) &m_llFrequency );
	QueryPerformanceCounter( (PLARGE_INTEGER) &m_llCountBegin );
}

Counter::~Counter()
{
	QueryPerformanceCounter( (PLARGE_INTEGER) &m_llCountEnd );
	pDoc->m_nResponseTime = int( (m_llCountEnd - m_llCountBegin) * 1000 / m_llFrequency );
	((CMainFrame *) AfxGetMainWnd())->m_wndResultDialog.UpdateResponseTime();
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_WINDOWPOSCHANGED()
	ON_COMMAND(ID_APERTURE, &CMainFrame::OnAperture)
	ON_COMMAND(ID_CONFIGURATION, &CMainFrame::OnConfiguration)
	ON_COMMAND(ID_MANU, &CMainFrame::OnManu)
	ON_COMMAND(ID_AUTO, &CMainFrame::OnAuto)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
	: camera( CTlFactory::GetInstance().CreateFirstDevice( ) )
{
	// TODO: add member initialization code here
	camera.StartGrabbing( );
	pImage = (BYTE *) calloc(HEIGHT * WIDTH * sizeof(BYTE), sizeof(BYTE));
}

CMainFrame::~CMainFrame()
{
	if ( pImage != NULL ) free( pImage );
}

void CMainFrame::Snap()
{
	CGrabResultPtr ptrGrabResult;
	camera.RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException );

	for (int i=0; i<HEIGHT; ++i)
		for (int j=0; j<WIDTH; ++j)
			pImage [ WIDTH * (HEIGHT - 1 - i) + j ] = ((BYTE *) ptrGrabResult->GetBuffer()) [ 1626 * i + j ];
}

BOOL CMainFrame::Locate()
{
	bool bNarrow = true;

	float thY, thD;

	if ( bNarrow ) {
		thY = 0.75f; thD = 0.04f;
	} else {
		thY = 0.8f; thD = 0.025f;
	}

	struct {
		BYTE * m_pOrg;
		BYTE & operator [] (const CPoint & pt) {
			return m_pOrg [ pt.x + WIDTH_BYTES(WIDTH * 8) * pt.y ];
		}
	} i = { (pImage + (HEIGHT - pDoc->m_rtAperture.bottom) * WIDTH_BYTES(WIDTH * 8) + pDoc->m_rtAperture.left) };

	LONG iWidth = pDoc->m_rtAperture.Width();
	LONG iHeight = pDoc->m_rtAperture.Height();

	float I [ 1500 ], dI [ 1500 ];
	float dMin, dMax;

	CPoint p;

	dMin = 255 * 1500; dMax = 0;
	for(p.y = 0; p.y < iHeight; ++p.y) {
		I [ p.y ] = 0;
		for(p.x = 0; p.x < iWidth; ++p.x)
			I [ p.y ] += i [ p ];
		if(I [ p.y ] < dMin) dMin = I [ p.y ];
		if(I [ p.y ] > dMax) dMax = I [ p.y ];
	}
	if( dMax - dMin <= 0.1 )
		return pDoc->m_bSuccess = FALSE;
	for(p.y = 0; p.y < iHeight; ++p.y)
		I [ p.y ] = ( I [ p.y ] - dMin ) / ( dMax - dMin );

	dI [ 0 ] = 0;
	for(p.y = 1; p.y < iHeight - 1; ++p.y)
		dI [ p.y ] = I [ p.y + 1 ] - I [ p.y - 1 ];
	dI [ iHeight - 1 ] = 0;

	LONG iU1, iU2;

	if ( bNarrow ) {
		iU1 = 0;
		for(p.y = 0; p.y < iHeight / 2; ++p.y)
			if( dI [ p.y ] < dI [ iU1 ] ) iU1 = p.y;
	}

	if ( bNarrow ) {
		iU2 = 0;
		for(p.y = iHeight - 1; p.y > iHeight / 2; --p.y)
			if( dI [ p.y ] > dI [ iU2 ] ) iU2 = p.y;
	}

	dMin = 255 * 1500; dMax = 0;
	if ( bNarrow ) {
		for(p.x = 0; p.x < iWidth; ++p.x) {
			I [ p.x ] = 0;
			for(p.y = iU1; p.y <= iU2; ++p.y) // !
				I [ p.x ] += i [ p ];
			if(I [ p.x ] < dMin) dMin = I [ p.x ];
			if(I [ p.x ] > dMax) dMax = I [ p.x ];
		}
	} else {
		for(p.x = 0; p.x < iWidth; ++p.x) {
			I [ p.x ] = 0;
			for(p.y = 0; p.y < iHeight; ++p.y) // !
				I [ p.x ] += i [ p ];
			if(I [ p.x ] < dMin) dMin = I [ p.x ];
			if(I [ p.x ] > dMax) dMax = I [ p.x ];
		}
	}
	if( dMax - dMin <= 0.1 )
		return pDoc->m_bSuccess = FALSE;
	for(p.x = 0; p.x < iWidth; ++p.x)
		I [ p.x ] = ( I [ p.x ] - dMin ) / ( dMax - dMin );

	dI [ 0 ] = 0;
	for(p.x = 1; p.x < iWidth - 1; ++p.x)
		dI [ p.x ] = I [ p.x + 1 ] - I [ p.x - 1 ];
	dI [ iWidth - 1 ] = 0;

	LONG iR1, iR2, iP1, iP2;

	iR1 = 0;
	for(p.x = 0; p.x < iWidth/2; ++p.x)
		if( dI[ p.x ] < dI[ iR1 ] ) iR1 = p.x;

	iR2 = 0;
	for(p.x = iWidth - 1; p.x > iWidth/2; --p.x)
		if( dI[ p.x ] > dI[ iR2 ] ) iR2 = p.x;

	int cnt;

	iP1 = 0;
//	for(p.x = (iR1 + iR2)/2; p.x > iR1 && I [ p.x ] < thY; --p.x);
//	while( p.x > iR1 && dI [ p.x ] <= - thD ) --p.x;
//	iP1 = p.x + 1;
	cnt = 0;
	for(p.x = (iR1 + iR2)/2; p.x > iR1 && !( I [ p.x ] < thY && I [ p.x + 1 ] >= thY ); --p.x)
		if( I [ p.x ] >= thY && dI [ p.x ] <= - thD ) {
			if( ++cnt >= 3 ) iP1 = p.x;
		} else cnt = 0;

	iP2 = 0;
//	for(p.x = (iR1 + iR2)/2; p.x < iR2 && I [ p.x ] < thY; ++p.x);
//	while( p.x < iR2 && dI [ p.x ] >= + thD ) ++p.x;
//	iP2 = p.x - 1;
	cnt = 0;
	for(p.x = (iR1 + iR2)/2; p.x < iR2 && !( I [ p.x ] < thY && I [ p.x - 1 ] >= thY ); ++p.x)
		if( I [ p.x ] >= thY && dI [ p.x ] >= + thD ) {
			if( ++cnt >= 3 ) iP2 = p.x;
		} else cnt = 0;

	if( iP2 - iP1 > (iR2 - iR1)/2 && iP2 - iP1 < iR2 - iR1 ) {
		if ( bNarrow ) {
			p.y = iU1;
			for(p.x = 0; p.x < iWidth; ++p.x)
				i [ p ] = 0;
			p.y = iU2;
			for(p.x = 0; p.x < iWidth; ++p.x)
				i [ p ] = 0;
		}
		p.x = iR1;
		for(p.y = 0; p.y < iHeight; ++p.y)
			i [ p ] = 0;
		p.x = iR2;
		for(p.y = 0; p.y < iHeight; ++p.y)
			i [ p ] = 0;
		p.x = iP1;
		for(p.y = 0; p.y < iHeight; ++p.y)
			i [ p ] = 0;
		p.x = iP2;
		for(p.y = 0; p.y < iHeight; ++p.y)
			i [ p ] = 0;
		pDoc->m_fDeviation = ( ((iP1 + iP2) - (iR1 + iR2)) / 2 ) * pDoc->m_fUnit;
		return pDoc->m_bSuccess = TRUE;
	}

	return pDoc->m_bSuccess = FALSE;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (CFrameWnd::OnCreateClient(lpcs, pContext) == NULL) return FALSE;

	m_wndResultDialog.Create(CResultDialog::IDD, this);
	m_wndConfigDialog.Create(CConfigDialog::IDD, &m_wndResultDialog);
	m_wndManuDialog.Create(CManuDialog::IDD, &m_wndResultDialog);
	m_wndAutoDialog.Create(CAutoDialog::IDD, &m_wndResultDialog);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	m_wndResultDialog.UpdateData(FALSE);
	m_wndResultDialog.ShowWindow(SW_SHOW);
}

void CMainFrame::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CFrameWnd::OnWindowPosChanged(lpwndpos);

	// TODO: 在此处添加消息处理程序代码
	if (GetActiveView() == NULL) return;
	if (m_wndResultDialog.GetSafeHwnd() == NULL) return;

	CRect rtCapture, rtResult;
	GetActiveView()->GetClientRect(&rtCapture);
	GetActiveView()->ClientToScreen(&rtCapture);
	m_wndResultDialog.GetClientRect(&rtResult);

	// 移动屏幕
	m_wndResultDialog.MoveWindow(
		(rtCapture.left + rtCapture.right) / 2 - rtResult.Width() / 2,
		rtCapture.top, rtResult.Width(), rtResult.Height()
	);
}

void CMainFrame::OnAperture()
{
	// TODO: 在此添加命令处理程序代码
	pDoc->m_bBoxing = TRUE;
}

void CMainFrame::OnConfiguration()
{
	// TODO: 在此添加命令处理程序代码
	m_wndConfigDialog.UpdateData(FALSE);
	m_wndConfigDialog.ShowWindow(SW_SHOW);
	pDoc->m_bLining = TRUE;
}

void CMainFrame::OnManu()
{
	// TODO: 在此添加命令处理程序代码
	m_wndManuDialog.ShowWindow(SW_SHOW);
}

void CMainFrame::OnAuto()
{
	// TODO: 在此添加命令处理程序代码
	m_wndAutoDialog.ShowWindow(SW_SHOW);
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch ( nIDEvent ) {
	case 1:
		{
			Counter T;

			Snap();
			Locate();
			m_wndResultDialog.UpdateResult();
			GetActiveView()->Invalidate(FALSE);
			GetActiveView()->UpdateWindow();
		}
		break;
	default:
		;
	}

	CFrameWnd::OnTimer(nIDEvent);
}
