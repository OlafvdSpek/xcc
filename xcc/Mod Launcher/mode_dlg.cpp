// mode_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "mode_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cmode_dlg dialog


Cmode_dlg::Cmode_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cmode_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cmode_dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cmode_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cmode_dlg)
	DDX_Control(pDX, IDC_MODE, m_modes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cmode_dlg, CDialog)
	//{{AFX_MSG_MAP(Cmode_dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cmode_dlg message handlers

BOOL Cmode_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	{
		typedef Cxcc_mod::t_mode_map t_map;
		const t_map& map = mod().mode_map();
		for (t_map::const_iterator i = map.begin(); i != map.end(); i++)
		{
			if (i->first != -1)
				m_modes.AddString(i->second.c_str());
		}
		m_modes.SetCurSel(0);
	}
	return true;
}

void Cmode_dlg::OnOK() 
{
	if (!UpdateData())
		return;
	CString mode, module;
	m_modes.GetWindowText(mode);
	m_mode = mode;
	CDialog::OnOK();
}

void Cmode_dlg::mod(const Cxcc_mod& mod)
{
	m_mod = &mod;
}
