// formats_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "formats_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cformats_dlg dialog


Cformats_dlg::Cformats_dlg(const Cucr_formats& formats, CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cformats_dlg::IDD, pParent, "formats_dlg"), m_formats(formats)
{
	//{{AFX_DATA_INIT(Cformats_dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cformats_dlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cformats_dlg)
	DDX_Control(pDX, IDOK, m_ok_button);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cformats_dlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Cformats_dlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cformats_dlg message handlers

static int c_colums = 2;

BOOL Cformats_dlg::OnInitDialog() 
{
	ETSLayoutDialog::OnInitDialog();
	
	const char* column_label[] = {"Name", "Extensions"};

	m_list.SetRedraw(false);
	for (int i = 0; i < c_colums; i++)
		m_list.InsertColumn(i, column_label[i], LVCFMT_LEFT, -1, i);
	{
		const Cucr_formats::t_list& list = m_formats.list();
		for (Cucr_formats::t_list::const_iterator i = list.begin(); i != list.end(); i++)
		{
			int index = m_list.InsertItem(m_list.GetItemCount(), i->name().c_str());
			m_list.SetItemText(index, 1, i->extensions_string(" ").c_str());
			if (!m_extension.empty() && i->extensions().find(m_extension) != i->extensions().end())
				m_list.SetItemState(index, LVNI_FOCUSED | LVNI_SELECTED, LVNI_FOCUSED | LVNI_SELECTED);
		}
	}
	m_list.auto_size();
	m_list.SetRedraw(true);
	
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, GREEDY)
			<< item(IDC_LIST, GREEDY)
			)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	UpdateLayout();

	return true;
}

void Cformats_dlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_ok_button.EnableWindow(m_list.GetNextItem(-1, LVNI_SELECTED) != -1);	
	*pResult = 0;
}

void Cformats_dlg::OnOK() 
{
	m_format = m_list.GetNextItem(-1, LVNI_SELECTED);
	ETSLayoutDialog::OnOK();
}

void Cformats_dlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if ((m_format = m_list.GetNextItem(-1, LVNI_SELECTED)) != -1)
		EndDialog(IDOK);	
	*pResult = 0;
}
