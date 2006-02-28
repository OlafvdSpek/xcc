// edit_waypoints_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "edit_waypoints_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cedit_waypoints_dlg dialog


Cedit_waypoints_dlg::Cedit_waypoints_dlg(Cxcc_level& level, bool selection_wanted):
	ETSLayoutDialog(Cedit_waypoints_dlg::IDD, 0, "edit_waypoints_dlg"),
	m_waypoint_data(level.waypoint_data),	
	m_selection_wanted(selection_wanted)
{
	//{{AFX_DATA_INIT(Cedit_waypoints_dlg)
	//}}AFX_DATA_INIT
	m_selected_i = -1;
}


void Cedit_waypoints_dlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cedit_waypoints_dlg)
	DDX_Control(pDX, IDC_DELETE, m_delete_button);
	DDX_Control(pDX, IDOK, m_ok_button);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cedit_waypoints_dlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Cedit_waypoints_dlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cedit_waypoints_dlg message handlers

BOOL Cedit_waypoints_dlg::OnInitDialog() 
{
	CreateRoot(HORIZONTAL)
		<< item(IDC_LIST1, GREEDY)
		<< (pane(VERTICAL, ABSOLUTE_HORZ)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			<< item(IDC_DELETE, NORESIZE)
			);
	ETSLayoutDialog::OnInitDialog();

	m_list.add_column("Index", 1, LVCFMT_RIGHT);
	m_list.add_column("Cell", 1);	

	for (long i = 0; i < 100; i++)
	{
		m_list.add_item(n(i), i);
		long v = m_waypoint_data[i];
		if (v == -1)
			continue;
		Cxcc_cell cell;
		cell.set_cc(v);
		m_list.set_item(nwzl(3, cell.get_x() >> 8) + ',' + nwzl(3, cell.get_y() >> 8), i, 1);
	};

	m_list.autosize_columns();
	
	return true;
}

long Cedit_waypoints_dlg::get_selected_i() const
{
	return m_selected_i;
}

void Cedit_waypoints_dlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_selected_i = m_list.get_focused_item();	
	if (m_selection_wanted)
		m_ok_button.EnableWindow(m_selected_i != -1 && m_selection_wanted);
	m_delete_button.EnableWindow(m_selected_i != -1 && m_waypoint_data[m_selected_i] != -1);
	*pResult = 0;
}

void Cedit_waypoints_dlg::OnDelete() 
{
	m_waypoint_data[m_selected_i] = -1;
	m_list.set_item("", m_selected_i, 1);
}

void Cedit_waypoints_dlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_selection_wanted)
		OnOK();
	*pResult = 0;
}
