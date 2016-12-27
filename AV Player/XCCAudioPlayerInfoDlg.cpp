#include "stdafx.h"
#include "XCCAudioPlayerInfoDlg.h"

CXCCAudioPlayerInfoDlg::CXCCAudioPlayerInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXCCAudioPlayerInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXCCAudioPlayerInfoDlg)
	//}}AFX_DATA_INIT
}

void CXCCAudioPlayerInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCAudioPlayerInfoDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXCCAudioPlayerInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CXCCAudioPlayerInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
