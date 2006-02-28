// shp_properties_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "shp_properties_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cshp_properties_dlg dialog


Cshp_properties_dlg::Cshp_properties_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cshp_properties_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cshp_properties_dlg)
	m_cy = 0;
	m_cx = 0;
	m_c_frames = 0;
	//}}AFX_DATA_INIT
}


void Cshp_properties_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cshp_properties_dlg)
	DDX_Text(pDX, IDC_CY, m_cy);
	DDV_MinMaxInt(pDX, m_cy, 0, 16384);
	DDX_Text(pDX, IDC_CX, m_cx);
	DDV_MinMaxInt(pDX, m_cx, 0, 16384);
	DDX_Text(pDX, IDC_C_FRAMES, m_c_frames);
	DDV_MinMaxInt(pDX, m_c_frames, 0, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cshp_properties_dlg, CDialog)
	//{{AFX_MSG_MAP(Cshp_properties_dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cshp_properties_dlg message handlers

void Cshp_properties_dlg::set_size(int cx, int cy, int c_frames)
{
	m_cx = cx;
	m_cy = cy;
	m_c_frames = c_frames;
}
