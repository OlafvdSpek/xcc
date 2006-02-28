// ResizeDlg.cpp : implementation file
//

#include "stdafx.h"
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
	m_maintain_aspect_ratio = true;
	m_relative_cx = 100;
	m_relative_cy = 100;
	m_fix_shadows = FALSE;
	//}}AFX_DATA_INIT
}


void CResizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResizeDlg)
	DDX_Text(pDX, IDC_CX, m_cx);
	DDV_MinMaxInt(pDX, m_cx, 0, 16384);
	DDX_Text(pDX, IDC_CY, m_cy);
	DDV_MinMaxInt(pDX, m_cy, 0, 16384);
	DDX_Check(pDX, IDC_MAINTAIN_ASPECT_RATIO, m_maintain_aspect_ratio);
	DDX_Text(pDX, IDC_RELATIVE_CX, m_relative_cx);
	DDX_Text(pDX, IDC_RELATIVE_CY, m_relative_cy);
	DDX_Check(pDX, IDC_FIX_SHADOWS, m_fix_shadows);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResizeDlg, CDialog)
	//{{AFX_MSG_MAP(CResizeDlg)
	ON_EN_UPDATE(IDC_CX, OnUpdateCX)
	ON_EN_UPDATE(IDC_CY, OnUpdateCY)
	ON_EN_UPDATE(IDC_RELATIVE_CX, OnUpdateRelativeCx)
	ON_EN_UPDATE(IDC_RELATIVE_CY, OnUpdateRelativeCy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizeDlg message handlers

void CResizeDlg::set_size(int cx, int cy)
{
	m_cx = m_original_cx = cx;
	m_cy = m_original_cy = cy;
	m_relative_cx = 100;
	m_relative_cy = 100;
	m_aspect_ratio = static_cast<float>(m_cx) / m_cy;
	update_relative();
}

void CResizeDlg::OnUpdateCX() 
{
	if (UpdateData(true) && m_maintain_aspect_ratio)
	{
		m_cy = m_cx / m_aspect_ratio + .5;
		update_relative();
		UpdateData(false);
	}
}

void CResizeDlg::OnUpdateCY() 
{
	if (UpdateData(true) && m_maintain_aspect_ratio)
	{
		m_cx = m_cy * m_aspect_ratio + .5;
		update_relative();
		UpdateData(false);
	}
}

void CResizeDlg::OnUpdateRelativeCx() 
{
	if (UpdateData(true))
	{
		if (m_maintain_aspect_ratio)
			m_relative_cy = m_relative_cx;
		update_absolut();
		UpdateData(false);
	}
}

void CResizeDlg::OnUpdateRelativeCy() 
{
	if (UpdateData(true))
	{
		if (m_maintain_aspect_ratio)
			m_relative_cx = m_relative_cy;
		update_absolut();
		UpdateData(false);
	}
}

void CResizeDlg::update_absolut()
{
	m_cx = m_original_cx * m_relative_cx / 100;
	m_cy = m_original_cy * m_relative_cy / 100;
}

void CResizeDlg::update_relative()
{
	m_relative_cx = m_cx * 100 / m_original_cx;
	m_relative_cy = m_cy * 100 / m_original_cy;
}
