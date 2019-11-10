// SPTXView.cpp : implementation of the CSPTXView class
//

#include "stdafx.h"
#include "SPTX.h"

#include "SPTXDoc.h"
#include "SPTXView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSPTXView

IMPLEMENT_DYNCREATE(CSPTXView, CView)

BEGIN_MESSAGE_MAP(CSPTXView, CView)
	//{{AFX_MSG_MAP(CSPTXView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSPTXView construction/destruction

CSPTXView::CSPTXView()
{
	// TODO: add construction code here
	m_pbmi = (PBITMAPINFO) calloc(sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD), 4);
	m_pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pbmi->bmiHeader.biWidth = WIDTH;
	m_pbmi->bmiHeader.biHeight = HEIGHT;
	m_pbmi->bmiHeader.biPlanes = 1;
	m_pbmi->bmiHeader.biBitCount = 8;
	m_pbmi->bmiHeader.biCompression = BI_RGB;
	for (int i=0; i<256; ++i) {
		LPRGBQUAD pRGB = m_pbmi->bmiColors + i;
		pRGB->rgbRed = pRGB->rgbGreen = pRGB->rgbBlue = i;
	}

	m_bDrawing = FALSE;
}

CSPTXView::~CSPTXView()
{
	if ( m_pbmi != NULL ) free( m_pbmi );
}

BOOL CSPTXView::PreCreateWindow(CREATESTRUCT& cs)
{
	if ( !CView::PreCreateWindow(cs) ) return FALSE;

	// TODO:  在此添加专用代码和/或调用基类
	WNDCLASS wndcls;
	::GetClassInfo(AfxGetInstanceHandle(), cs.lpszClass, &wndcls);
	wndcls.style |= CS_OWNDC;
	wndcls.lpszClassName = _T("sptx");
	AfxRegisterClass( &wndcls );

	cs.lpszClass = _T("sptx");
	cs.cx = m_nWidth = WIDTH;
	cs.cy = m_nHeight = HEIGHT;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSPTXView drawing

void CSPTXView::OnDraw(CDC* pDC)
{
	CSPTXDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	CRect rt(0, 0, WIDTH, HEIGHT);
	CRect rtFill(rt);

	rtFill.right *= 3;
	rtFill.bottom *= 3;
	m_dcMemory.FillRect(rtFill, &CBrush(RGB(255, 255, 255)));
	SetDIBitsToDevice(m_dcMemory.m_hDC, WIDTH, HEIGHT, WIDTH, HEIGHT, 0, 0, 0, HEIGHT,
		pImage, m_pbmi, DIB_RGB_COLORS);

//	if ( pDoc->m_bBoxing )
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen * pOldPen = m_dcMemory.SelectObject( &pen );
		CBrush * pOldBrush = (CBrush *) m_dcMemory.SelectStockObject(NULL_BRUSH);

		m_dcMemory.Rectangle( &( CPoint(WIDTH, HEIGHT) + pDoc->m_rtAperture ) );

		m_dcMemory.SelectObject(pOldPen);
		m_dcMemory.SelectObject(pOldBrush);
	}

	if ( pDoc->m_bLining )
	{
		INT m_nDrawMode = m_dcMemory.SetROP2(R2_XORPEN);
		CPen pen(PS_SOLID, 1, RGB(255,0,0));
		CPen * pOldPen = m_dcMemory.SelectObject( &pen );
		CBrush * pOldBrush = (CBrush *) m_dcMemory.SelectStockObject(NULL_BRUSH);

		m_dcMemory.MoveTo( CPoint(WIDTH, HEIGHT) + ((CMainFrame *) AfxGetMainWnd())->m_wndConfigDialog.m_ptStart );
		m_dcMemory.LineTo( CPoint(WIDTH, HEIGHT) + ((CMainFrame *) AfxGetMainWnd())->m_wndConfigDialog.m_ptEnd );

		m_dcMemory.SelectObject(pOldPen);
		m_dcMemory.SelectObject(pOldBrush);
		m_dcMemory.SetROP2(m_nDrawMode);
	}

	pDC->BitBlt(-WIDTH, -HEIGHT, rtFill.Width(), rtFill.Height(), &m_dcMemory, 0, 0, SRCCOPY);
/*
	if ( pDoc->m_bBoxing ) {
		INT m_nDrawMode = pDC->SetROP2(R2_XORPEN);
		CPen pen(PS_SOLID, 1, RGB(255,0,0));
		CPen* pOldPen = pDC->SelectObject(&pen);
		CBrush* pOldBrush = (CBrush*) pDC->SelectStockObject(NULL_BRUSH);

		pDC->Rectangle( pDoc->m_rtAperture );

		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
		pDC->SetROP2(m_nDrawMode);
	}

	if ( pDoc->m_bLining ) {
		INT m_nDrawMode = pDC->SetROP2(R2_XORPEN);
		CPen pen(PS_SOLID, 1, RGB(255,0,0));
		CPen * pOldPen = pDC->SelectObject(&pen);
		CBrush * pOldBrush = (CBrush *) pDC->SelectStockObject(NULL_BRUSH);

		pDC->MoveTo(((CMainFrame *) AfxGetMainWnd())->m_wndConfigDialog.m_ptStart);
		pDC->LineTo(((CMainFrame *) AfxGetMainWnd())->m_wndConfigDialog.m_ptEnd);

		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
		pDC->SetROP2(m_nDrawMode);
	}*/
}

/////////////////////////////////////////////////////////////////////////////
// CSPTXView diagnostics

#ifdef _DEBUG
void CSPTXView::AssertValid() const
{
	CView::AssertValid();
}

void CSPTXView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSPTXDoc* CSPTXView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSPTXDoc)));
	return (CSPTXDoc *) m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSPTXView message handlers

int CSPTXView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CDC* pDC = GetDC();

	m_dcMemory.CreateCompatibleDC( pDC ); // 创建与显示DC相兼容的内存DC
	m_bm.CreateCompatibleBitmap( pDC, WIDTH * 3, HEIGHT * 3 );
	m_dcMemory.SelectObject( &m_bm );

	ReleaseDC(pDC);

	return 0;
}

void CSPTXView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CDC* pDC = GetDC();

	pDC->SetMapMode( MM_ISOTROPIC );
	pDC->SetWindowExt( WUNIT * pDoc->m_nRate, HUNIT * pDoc->m_nRate );
	pDC->SetViewportExt( m_nWidth, m_nHeight );
	pDC->SetWindowOrg( pDoc->m_ptOrg );
	pDC->SetViewportOrg( m_nWidth / 2, m_nHeight * 3 / 4 );

	ReleaseDC(pDC);
}

void CSPTXView::OnDestroy()
{
	// TODO: 在此处添加消息处理程序代码
	CDC* pDC = GetDC();
	pDoc->m_ptOrg = CPoint(m_nWidth / 2, m_nHeight * 3 / 4);
	pDC->DPtoLP( &(pDoc->m_ptOrg) );
	ReleaseDC( pDC );

	GetDocument()->DoSave(STR_CFG_FILE_NAME);

	CView::OnDestroy();
}

void CSPTXView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	CDC* pDC = GetDC();
	
	CPoint pt(m_nWidth / 2, m_nHeight * 3 / 4);
	pDC->DPtoLP(&pt);

	pDC->SetViewportExt(cx, cy);
	pDC->SetWindowOrg(pt);
	pDC->SetViewportOrg(cx / 2, cy * 3 / 4);

	ReleaseDC(pDC);

	m_nWidth = cx;
	m_nHeight = cy;
}


BOOL CSPTXView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDC* pDC = GetDC();

	CPoint point(pt);
	pDC->DPtoLP(&point);

	pDC->SetViewportOrg(pt);
	pDC->SetWindowOrg(point);

	pDoc->m_nRate -= zDelta / WHEEL_DELTA;
	if (pDoc->m_nRate <= 1) pDoc->m_nRate = 2;

	pDC->SetWindowExt(WUNIT * pDoc->m_nRate, HUNIT * pDoc->m_nRate);

	Invalidate(FALSE);
	ReleaseDC(pDC);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CSPTXView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ( pDoc->m_bBoxing ) {
		if ( !m_bDrawing ) {
			m_bDrawing = TRUE;

			CDC* pDC = GetDC();
			pDC->DPtoLP( &point );
			ReleaseDC(pDC);

			pDoc->m_rtAperture = CRect(point, point);
			Invalidate(FALSE);
		}
		return;
	}
	if ( pDoc->m_bLining ) {
		if ( !m_bDrawing ) {
			m_bDrawing = TRUE;

			CDC* pDC = GetDC();
			pDC->DPtoLP( &point );
			ReleaseDC(pDC);

			((CMainFrame *) AfxGetMainWnd())->m_wndConfigDialog.m_ptStart = point;
			((CMainFrame *) AfxGetMainWnd())->m_wndConfigDialog.m_ptEnd = point;
			((CMainFrame *) AfxGetMainWnd())->m_wndConfigDialog.Revise();
			Invalidate(FALSE);
		}
		return;
	}
	SetCapture();
	if ( !m_bDrawing ) {
		m_bDrawing = TRUE;

		CDC* pDC = GetDC();

		CPoint pt(point);
		pDC->DPtoLP(&pt);
		pDC->SetViewportOrg(point);
		pDC->SetWindowOrg(pt);

		Invalidate(FALSE);
		ReleaseDC(pDC);
	}

//	CView::OnLButtonDown(nFlags, point);
}

void CSPTXView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ( pDoc->m_bBoxing ) {
		pDoc->m_bBoxing = FALSE;
		if ( m_bDrawing ) {
			m_bDrawing = FALSE;

			CDC* pDC = GetDC();
			pDC->DPtoLP( &point );
			ReleaseDC(pDC);

			pDoc->m_rtAperture.BottomRight() = point;
			Invalidate(FALSE);
		}
		return;
	}
	if ( pDoc->m_bLining ) {
		if ( m_bDrawing ) {
			m_bDrawing = FALSE;

			CDC* pDC = GetDC();
			pDC->DPtoLP( &point );
			ReleaseDC(pDC);

			((CMainFrame *) AfxGetMainWnd())->m_wndConfigDialog.m_ptEnd = point;
			((CMainFrame *) AfxGetMainWnd())->m_wndConfigDialog.Revise();
			Invalidate(FALSE);
		}
		return;
	}
	if ( m_bDrawing ) {
		m_bDrawing = FALSE;

		CDC* pDC = GetDC();
		pDC->SetViewportOrg(point);
		Invalidate(FALSE);
		ReleaseDC(pDC);
	}
	ReleaseCapture();

//	CView::OnLButtonUp(nFlags, point);
}

void CSPTXView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ( pDoc->m_bBoxing ) {
		if ( m_bDrawing ) {
			CDC* pDC = GetDC();
			pDC->DPtoLP( &point );
			ReleaseDC(pDC);

			pDoc->m_rtAperture.BottomRight() = point;
			Invalidate(FALSE);
		}
		return;
	}
	if ( pDoc->m_bLining ) {
		if ( m_bDrawing ) {
			CDC* pDC = GetDC();
			pDC->DPtoLP( &point );
			ReleaseDC(pDC);

			((CMainFrame *) AfxGetMainWnd())->m_wndConfigDialog.m_ptEnd = point;
			((CMainFrame *) AfxGetMainWnd())->m_wndConfigDialog.Revise();
			Invalidate(FALSE);
		}
		return;
	}
	if ( m_bDrawing ) {
		CDC* pDC = GetDC();
		pDC->SetViewportOrg(point);
		Invalidate(FALSE);
		ReleaseDC(pDC);
	}

//	CView::OnMouseMove(nFlags, point);
}
