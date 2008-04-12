#include "stdafx.h"
#include "XCC Universal Container Reader.h"

#include "format_edit_dlg.h"
#include "formats_dlg.h"
#include "library_dlg.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_FORMAT, OnEditFormat)
	ON_COMMAND(ID_FILE_LIBRARY, OnFileLibrary)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

void CMainFrame::OnEditFormat()
{
	Cformats_dlg dlg(app()->formats());
	if (IDOK == dlg.DoModal())
	{
		Cucr_format format = dlg.format();
		Cformat_edit_dlg dlg;
		dlg.set(format);
		if (IDOK == dlg.DoModal())
		{
			dlg.get();
		}
	}
}

void CMainFrame::OnFileLibrary()
{
	Clibrary_dlg dlg(app()->formats(), app()->library());
	if (IDOK == dlg.DoModal())
		app()->OpenDocumentFile(dlg.container().c_str());
}
