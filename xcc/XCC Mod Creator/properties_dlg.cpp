// properties_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "XCC Mod Creator.h"
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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cproperties_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cproperties_dlg)
	DDX_Control(pDX, IDC_MODULE, m_module);
	DDX_Control(pDX, IDC_MODE, m_mode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cproperties_dlg, CDialog)
	//{{AFX_MSG_MAP(Cproperties_dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cproperties_dlg message handlers

BOOL Cproperties_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	{
		typedef Cxcc_mod::t_mode_map t_map;
		const t_map& map = mod().mode_map();
		for (t_map::const_iterator i = map.begin(); i != map.end(); i++)
		{
			int index = m_mode.AddString(i->second.c_str());
			if (i->first == m_properties.mode)
				m_mode.SetCurSel(index);
		}
	}
	{
		typedef Cxcc_mod::t_module_map t_map;
		const t_map& map = mod().module_map();
		for (t_map::const_iterator i = map.begin(); i != map.end(); i++)
		{
			int index = m_module.AddString(i->second.c_str());
			if (i->first == m_properties.module)
				m_module.SetCurSel(index);
		}
	}
	return true;
}

void Cproperties_dlg::OnOK() 
{
	if (!UpdateData())
		return;
	CString mode, module;
	m_mode.GetWindowText(mode);
	m_module.GetWindowText(module);
	m_mode_value = mode;
	m_module_value = module;
	CDialog::OnOK();
}

void Cproperties_dlg::mod(const Cxcc_mod& mod)
{
	m_mod = &mod;
}

void Cproperties_dlg::properties(Cxcc_mod::t_file_properties properties)
{
	m_properties = properties;
}
