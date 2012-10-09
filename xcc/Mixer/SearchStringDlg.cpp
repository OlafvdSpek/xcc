#include "stdafx.h"
#include "SearchStringDlg.h"

#include "fname.h"

CString CSearchStringDlg::m_name;

CSearchStringDlg::CSearchStringDlg(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(CSearchStringDlg::IDD, pParent, "search_file_dlg")
{
	//{{AFX_DATA_INIT(CSearchStringDlg)
	//}}AFX_DATA_INIT
}

void CSearchStringDlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchStringDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_NAME, m_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSearchStringDlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(CSearchStringDlg)
	ON_BN_CLICKED(IDOK, OnSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSearchStringDlg::OnInitDialog() 
{
	CreateRoot(VERTICAL)
		<< item(IDC_NAME, ABSOLUTE_VERT)
		<< item(IDC_LIST, GREEDY)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	ETSLayoutDialog::OnInitDialog();
	m_list.InsertColumn(0, "Name");
	m_list.InsertColumn(1, "Value");
	m_list.auto_size();
	return true;
}

void CSearchStringDlg::OnSearch() 
{
	if (UpdateData(true))
	{
		CWaitCursor wait;
		m_list.DeleteAllItems();
		for (auto& i : m_csf->get_map())
		{
			if (fname_filter(i.first, static_cast<string>(m_name))
				|| fname_filter(Ccsf_file::convert2string(i.second.value), static_cast<string>(m_name)))
				m_list.SetItemText(m_list.InsertItem(m_list.GetItemCount(), i.first.c_str()), 1, Ccsf_file::convert2string(i.second.value).c_str());
		}
		m_list.auto_size();
	}
}

void CSearchStringDlg::set(const Ccsf_file *csf)
{
	m_csf = csf;
}

void CSearchStringDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i = m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	if (i != -1)
	{
		m_selected = m_list.GetItemText(i, 0);
		EndDialog(IDOK);
	}
	*pResult = 0;
}
