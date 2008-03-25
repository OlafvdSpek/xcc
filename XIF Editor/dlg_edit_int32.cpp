#include "stdafx.h"
#include "xif editor.h"
#include "dlg_edit_int32.h"

Cdlg_edit_int32::Cdlg_edit_int32(CWnd* pParent /*=NULL*/)
	: CDialog(Cdlg_edit_int32::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cdlg_edit_int32)
	m_key = _T("");
	m_value = 0;
	//}}AFX_DATA_INIT
}

void Cdlg_edit_int32::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlg_edit_int32)
	DDX_Text(pDX, IDC_KEY, m_key);
	DDX_Text(pDX, IDC_VALUE, m_value);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cdlg_edit_int32, CDialog)
	//{{AFX_MSG_MAP(Cdlg_edit_int32)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void Cdlg_edit_int32::set(const string& key, int value)
{
	m_key = key.c_str();
	m_value = value;
}

int Cdlg_edit_int32::get()
{
	return m_value;
}

BOOL Cdlg_edit_int32::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GotoDlgCtrl(GetDlgItem(IDC_VALUE));
	return false;
}
