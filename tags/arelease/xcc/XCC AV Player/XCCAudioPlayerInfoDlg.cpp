// XCCAUDIOPLAYERINFODlg.cpp : implementation file
//

#include "stdafx.h"
#include "XCC Audio Player.h"
#include "XCCAudioPlayerInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCAudioPlayerInfoDlg dialog


CXCCAudioPlayerInfoDlg::CXCCAudioPlayerInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXCCAudioPlayerInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXCCAudioPlayerInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CXCCAudioPlayerInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCAudioPlayerInfoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXCCAudioPlayerInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CXCCAudioPlayerInfoDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCAudioPlayerInfoDlg message handlers
