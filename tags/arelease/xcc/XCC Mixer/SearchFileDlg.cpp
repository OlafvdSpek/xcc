// SearchFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "xcc mixer.h"
#include "SearchFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchFileDlg dialog


CSearchFileDlg::CSearchFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchFileDlg)
	m_filename = _T("");
	//}}AFX_DATA_INIT
}


void CSearchFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchFileDlg)
	DDX_Text(pDX, IDC_FILENAME, m_filename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchFileDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchFileDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchFileDlg message handlers
