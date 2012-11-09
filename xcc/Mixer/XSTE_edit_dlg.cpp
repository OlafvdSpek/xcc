#include "stdafx.h"
#include "XSTE_edit_dlg.h"

CXSTE_edit_dlg::CXSTE_edit_dlg(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(CXSTE_edit_dlg::IDD, pParent, "XSTE_edit_dlg")
{
	//{{AFX_DATA_INIT(CXSTE_edit_dlg)
	m_extra_value = _T("");
	m_name = _T("");
	m_value = _T("");
	//}}AFX_DATA_INIT
}

void CXSTE_edit_dlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXSTE_edit_dlg)
	DDX_Text(pDX, IDC_EXTRA_VALUE, m_extra_value);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_VALUE, m_value);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXSTE_edit_dlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(CXSTE_edit_dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CXSTE_edit_dlg::set(const string& name, const string& value, const string& extra_value)
{
	m_name = name.c_str();
	m_value.Empty();
	for (size_t i = 0; i < value.length(); i++)
	{
		if (value[i] == '\n')
			m_value += '\r';
		m_value += value[i];
	}
	m_extra_value = extra_value.c_str();
}

string CXSTE_edit_dlg::get_name() const
{
	return string(m_name);
}

string CXSTE_edit_dlg::get_value() const
{
	string r;
	for (int i = 0; i < m_value.GetLength(); i++)
	{
		if (m_value[i] != '\r')
			r += m_value[i];
	}
	return r;
}

string CXSTE_edit_dlg::get_extra_value() const
{
	return string(m_extra_value);
}

BOOL CXSTE_edit_dlg::OnInitDialog() 
{
	CreateRoot(VERTICAL)
		<< item(IDC_NAME, ABSOLUTE_VERT)
		<< item(IDC_VALUE, GREEDY)
		<< item(IDC_EXTRA_VALUE, ABSOLUTE_VERT)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	ETSLayoutDialog::OnInitDialog();
	return true;
}
