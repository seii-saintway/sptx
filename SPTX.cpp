// SPTX.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SPTX.h"

#include "MainFrm.h"
#include "SPTXDoc.h"
#include "SPTXView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSPTXApp

BEGIN_MESSAGE_MAP(CSPTXApp, CWinApp)
	//{{AFX_MSG_MAP(CSPTXApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSPTXApp construction

CSPTXApp::CSPTXApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSPTXApp object

CSPTXApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSPTXApp initialization

BOOL CSPTXApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate * pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSPTXDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CSPTXView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
//	ParseCommandLine(cmdInfo);

	CFileException fe;

	if (!CFile().Open(STR_CFG_FILE_NAME,
			CFile::modeRead|CFile::shareDenyWrite, &fe)
	&&	fe.m_cause == CFileException::fileNotFound) {
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNew;
	} else {
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileOpen;
		cmdInfo.m_strFileName = STR_CFG_FILE_NAME;
	}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->SetTimer(1, pDoc->m_nInterval, NULL);

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSPTXApp message handlers
