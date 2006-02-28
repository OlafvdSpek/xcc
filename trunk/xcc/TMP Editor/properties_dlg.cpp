// properties_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "properties_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cproperties_dlg dialog


Cproperties_dlg::Cproperties_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cproperties_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cproperties_dlg)
	m_height = 0;
	m_terrain_type = 0;
	m_x = 0;
	m_x_extra = 0;
	m_y = 0;
	m_y_extra = 0;
	m_ramp_type = 0;
	//}}AFX_DATA_INIT
}


void Cproperties_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cproperties_dlg)
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDV_MinMaxInt(pDX, m_height, 0, 127);
	DDX_Text(pDX, IDC_TERRAIN_TYPE, m_terrain_type);
	DDV_MinMaxInt(pDX, m_terrain_type, 0, 127);
	DDX_Text(pDX, IDC_X, m_x);
	DDX_Text(pDX, IDC_X_EXTRA, m_x_extra);
	DDX_Text(pDX, IDC_Y, m_y);
	DDX_Text(pDX, IDC_Y_EXTRA, m_y_extra);
	DDX_Text(pDX, IDC_RAMP_TYPE, m_ramp_type);
	DDV_MinMaxInt(pDX, m_ramp_type, 0, 127);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cproperties_dlg, CDialog)
	//{{AFX_MSG_MAP(Cproperties_dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cproperties_dlg message handlers

void Cproperties_dlg::set(const t_tmp_image_header& header)
{
	m_x = header.x;
	m_y = header.y;
	if (header.has_extra_data)
	{
		m_x_extra = header.x_extra;
		m_y_extra = header.y_extra;
	}
	else
	{
		m_x_extra = 0;
		m_y_extra = 0;
	}
	m_height = header.height;
	m_terrain_type = header.terrain_type;
	m_ramp_type = header.ramp_type;
}

void Cproperties_dlg::get(t_tmp_image_header& header)
{
	header.x = m_x;
	header.y = m_y;
	header.x_extra = m_x_extra;
	header.y_extra = m_y_extra;
	header.height = m_height;
	header.terrain_type = m_terrain_type;
	header.ramp_type = m_ramp_type;
}
