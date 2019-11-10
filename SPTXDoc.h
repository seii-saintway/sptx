// SPTXDoc.h : interface of the CSPTXDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPTXDOC_H__B7CB9531_F821_4A70_9A10_5B8ED5D17964__INCLUDED_)
#define AFX_SPTXDOC_H__B7CB9531_F821_4A70_9A10_5B8ED5D17964__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSPTXDoc : public CDocument
{
protected: // create from serialization only
	CSPTXDoc();
	DECLARE_DYNCREATE(CSPTXDoc)

// Attributes
public:
	FLOAT m_fUnit;
	UINT m_uMM;
	FLOAT m_fPixel;
	CPoint m_ptStart, m_ptEnd;

	CArray<FLOAT, FLOAT> m_arrMM; //float m_auPexil[3];
	INT m_nLevel;
	INT m_nInterval;
	INT m_nPassItv;
	INT m_nUnpsItv;

	CRect m_rtAperture; //CRect m_rtDIBRegion;

	INT m_nRate;
	CPoint m_ptOrg;

	// AutoDlg
	FLOAT m_fMotorRate;
	FLOAT m_fAngleRate;
	FLOAT m_fAddRate;
	INT m_nAddStep;
	INT m_nWise;

	CString m_strIP;

	BOOL m_bLining, m_bBoxing;
	BOOL m_bSuccess;
	FLOAT m_fDeviation;
	INT m_nResponseTime;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSPTXDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSPTXDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSPTXDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

extern BYTE * pImage;
extern CSPTXDoc * pDoc;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPTXDOC_H__B7CB9531_F821_4A70_9A10_5B8ED5D17964__INCLUDED_)
