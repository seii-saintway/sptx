// SPTXDoc.cpp : implementation of the CSPTXDoc class
//

#include "stdafx.h"
#include "SPTX.h"

#include "SPTXDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSPTXDoc * pDoc = NULL;

/////////////////////////////////////////////////////////////////////////////
// CSPTXDoc

IMPLEMENT_DYNCREATE(CSPTXDoc, CDocument)

BEGIN_MESSAGE_MAP(CSPTXDoc, CDocument)
	//{{AFX_MSG_MAP(CSPTXDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSPTXDoc construction/destruction

CSPTXDoc::CSPTXDoc()
{
	// TODO: add one-time construction code here
	pDoc = this;

	m_bLining = m_bBoxing = FALSE;
	m_bSuccess = FALSE;
	m_fDeviation = 0;
	m_nResponseTime = 0;

	m_fUnit = 10 / 200.0f;
	m_uMM = 10;
	m_fPixel = 200.0f;
	m_ptStart = CPoint(50, 150);
	m_ptEnd = CPoint(250, 150);

	m_arrMM.Add(0.1f); m_arrMM.Add(0.25f); m_arrMM.Add(0.4f);
	m_nLevel = 0;
	m_nInterval = 200;
	m_nPassItv = 15;
	m_nUnpsItv = 15;

	m_rtAperture = CRect(WIDTH / 2, HEIGHT * 7 / 13, WIDTH / 2, HEIGHT * 7 / 13);
	m_rtAperture.InflateRect(WIDTH / 4, HEIGHT / 10);

	m_nRate = RATE;
	m_ptOrg = CPoint(WIDTH / 2, HEIGHT * 3 / 4);

	m_fMotorRate = 5;
	m_fAngleRate = 10000;
	m_fAddRate = 1;
	m_nAddStep = 0;
	m_nWise = 0;

	m_strIP = "127.0.0.1";
}

CSPTXDoc::~CSPTXDoc()
{
}

BOOL CSPTXDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_fUnit = 10 / 200.0f;
	m_uMM = 10;
	m_fPixel = 200.0f;
	m_ptStart = CPoint(50, 150);
	m_ptEnd = CPoint(250, 150);

	m_arrMM.Add(0.1f); m_arrMM.Add(0.25f); m_arrMM.Add(0.4f);
	m_nLevel = 0;
	m_nInterval = 200;
	m_nPassItv = 15;
	m_nUnpsItv = 15;

	m_rtAperture = CRect(WIDTH / 2, HEIGHT * 7 / 13, WIDTH / 2, HEIGHT * 7 / 13);
	m_rtAperture.InflateRect(WIDTH / 4, HEIGHT / 10);

	m_nRate = RATE;
	m_ptOrg = CPoint(WIDTH / 2, HEIGHT * 3 / 4);

	m_fMotorRate = 5;
	m_fAngleRate = 10000;
	m_fAddRate = 1;
	m_nAddStep = 0;
	m_nWise = 0;

	m_strIP = "127.0.0.1";

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSPTXDoc serialization

void CSPTXDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_fUnit;
		ar << m_uMM;
		ar << m_fPixel;
		ar << m_ptStart;
		ar << m_ptEnd;
		m_arrMM.Serialize(ar);
		ar << m_nLevel;
		ar << m_nInterval;
		ar << m_nPassItv;
		ar << m_nUnpsItv;
		ar << m_rtAperture;
		ar << m_nRate;
		ar << m_ptOrg;
		ar << m_fMotorRate;
		ar << m_fAngleRate;
		ar << m_fAddRate;
		ar << m_nAddStep;
		ar << m_nWise;
		ar << m_strIP;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_fUnit;
		ar >> m_uMM;
		ar >> m_fPixel;
		ar >> m_ptStart;
		ar >> m_ptEnd;
		m_arrMM.Serialize(ar);
		ar >> m_nLevel;
		ar >> m_nInterval;
		ar >> m_nPassItv;
		ar >> m_nUnpsItv;
		ar >> m_rtAperture;
		ar >> m_nRate;
		ar >> m_ptOrg;
		ar >> m_fMotorRate;
		ar >> m_fAngleRate;
		ar >> m_fAddRate;
		ar >> m_nAddStep;
		ar >> m_nWise;
		ar >> m_strIP;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSPTXDoc diagnostics

#ifdef _DEBUG
void CSPTXDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSPTXDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSPTXDoc commands
