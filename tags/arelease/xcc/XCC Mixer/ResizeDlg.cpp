// ResizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "xcc mixer.h"
#include "ResizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizeDlg dialog


CResizeDlg::CResizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResizeDlg)
	m_cx = 0;
	m_cy = 0;
	//}}AFX_DATA_INIT
}


void CResizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResizeDlg)
	DDX_Text(pDX, IDC_CX, m_cx);
	DDV_MinMaxInt(pDX, m_cx, 0, 4095);
	DDX_Text(pDX, IDC_CY, m_cy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResizeDlg, CDialog)
	//{{AFX_MSG_MAP(CResizeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizeDlg message handlers

void CResizeDlg::set_size(int cx, int cy)
{
	m_cx = cx;
	m_cy = cy;
	m_aspect_ratio = static_cast<float>(m_cx) / m_cy;
}
