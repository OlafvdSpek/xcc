#include "stdafx.h"
#include "XIF Editor.h"
#include "dlg_edit_bin32.h"
#include "string_conversion.h"
#include "xif_tools.h"

Cdlg_edit_bin32::Cdlg_edit_bin32(CWnd* pParent /*=NULL*/)
	: CDialog(Cdlg_edit_bin32::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cdlg_edit_bin32)
	m_key = _T("");
	m_value = _T("");
	//}}AFX_DATA_INIT
}

void Cdlg_edit_bin32::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlg_edit_bin32)
	DDX_Text(pDX, IDC_KEY, m_key);
	DDX_Text(pDX, IDC_VALUE, m_value);
	DDV_MaxChars(pDX, m_value, 8);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cdlg_edit_bin32, CDialog)
	//{{AFX_MSG_MAP(Cdlg_edit_bin32)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void Cdlg_edit_bin32::set(const string& key, int value)
{
	m_key = key.c_str();
	m_value = nh(8, value).c_str();
}

int Cdlg_edit_bin32::get()
{
	return str2hex(m_value);
}

BOOL Cdlg_edit_bin32::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GotoDlgCtrl(GetDlgItem(IDC_VALUE));
	return false;
}
