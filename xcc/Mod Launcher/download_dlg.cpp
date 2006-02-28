#include "stdafx.h"
#include "download_dlg.h"

#include "string_conversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Cdownload_dlg::Cdownload_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cdownload_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cdownload_dlg)
	m_destination = _T("");
	m_source = _T("");
	m_size = _T("");
	//}}AFX_DATA_INIT
}


void Cdownload_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdownload_dlg)
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Text(pDX, IDC_DESTINATION, m_destination);
	DDX_Text(pDX, IDC_SOURCE, m_source);
	DDX_Text(pDX, IDC_FSIZE, m_size);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cdownload_dlg, CDialog)
	//{{AFX_MSG_MAP(Cdownload_dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdownload_dlg message handlers

void Cdownload_dlg::set(string source, string destination, int total_size)
{
	m_source = source.c_str();
	m_destination = destination.c_str();
	m_total_size = total_size;
}

void Cdownload_dlg::set_size(int size)
{
	m_size = (nwp(0, size) + " of " + nwp(0, m_total_size) + " bytes").c_str();
	m_progress.SetRange32(0, m_total_size);
	m_progress.SetPos(size);
	UpdateData(false);
}