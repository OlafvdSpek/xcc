#include "stdafx.h"
#include "xif editor.h"
#include "dlg_edit_string.h"

Cdlg_edit_string::Cdlg_edit_string(CWnd* pParent /*=NULL*/)
	: CDialog(Cdlg_edit_string::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cdlg_edit_string)
	m_key = _T("");
	m_value = _T("");
	//}}AFX_DATA_INIT
}

void Cdlg_edit_string::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlg_edit_string)
	DDX_Text(pDX, IDC_KEY, m_key);
	DDX_Text(pDX, IDC_VALUE, m_value);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cdlg_edit_string, CDialog)
	//{{AFX_MSG_MAP(Cdlg_edit_string)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void Cdlg_edit_string::set(const string& key, const string& value)
{
	m_key = key.c_str();
	m_value = value.c_str();
}

string Cdlg_edit_string::get()
{
	return string(m_value);
}

BOOL Cdlg_edit_string::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GotoDlgCtrl(GetDlgItem(IDC_VALUE));
	return false;
}
