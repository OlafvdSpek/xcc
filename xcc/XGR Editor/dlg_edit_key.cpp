// dlg_edit_key.cpp : implementation file
//

#include "stdafx.h"
#include "XGR Editor.h"
#include "dlg_edit_key.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cdlg_edit_key dialog


Cdlg_edit_key::Cdlg_edit_key(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cdlg_edit_key::IDD, pParent, "dlg_edit_key")
{
	//{{AFX_DATA_INIT(Cdlg_edit_key)
	m_name = _T("");
	m_value = _T("");
	//}}AFX_DATA_INIT
}


void Cdlg_edit_key::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlg_edit_key)
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_CBString(pDX, IDC_VALUE, m_value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cdlg_edit_key, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Cdlg_edit_key)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdlg_edit_key message handlers

BOOL Cdlg_edit_key::OnInitDialog() 
{
	ETSLayoutDialog::OnInitDialog();
	CreateRoot(VERTICAL)
		<< item(IDC_NAME, ABSOLUTE_VERT)
		<< item(IDC_VALUE, ABSOLUTE_VERT)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	UpdateLayout();
	return true;
}

string Cdlg_edit_key::get_name()
{
	return m_name;
}

string Cdlg_edit_key::get_value()
{
	return m_value;
}

void Cdlg_edit_key::set_name(const string& v)
{
	m_name = v.c_str();
}

void Cdlg_edit_key::set_value(const string& v)
{
	m_value = v.c_str();
}
