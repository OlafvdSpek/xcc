// directories_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "directories_dlg.h"

#include "string_conversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cdirectories_dlg dialog


Cdirectories_dlg::Cdirectories_dlg(const Cucr_library& library, CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cdirectories_dlg::IDD, pParent, "directories_dlg"), m_library(library)
{
	//{{AFX_DATA_INIT(Cdirectories_dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cdirectories_dlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdirectories_dlg)
	DDX_Control(pDX, IDC_DELETE, m_delete_button);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cdirectories_dlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Cdirectories_dlg)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdirectories_dlg message handlers

static int c_colums = 1;

BOOL Cdirectories_dlg::OnInitDialog() 
{
	ETSLayoutDialog::OnInitDialog();
	
	const char* column_label[] = {"Name"};

	m_list.SetRedraw(false);
	for (int i = 0; i < c_colums; i++)
		m_list.InsertColumn(i, column_label[i], LVCFMT_LEFT, -1, i);
	{
		const Cucr_library::t_directories& list = m_library.directories();
		for (Cucr_library::t_directories::const_iterator i = list.begin(); i != list.end(); i++)
			m_list.InsertItem(m_list.GetItemCount(), i->c_str());
	}
	m_list.auto_size();
	m_list.SetRedraw(true);

	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, GREEDY)
			<< item(IDC_LIST, GREEDY)
			)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDC_DELETE, NORESIZE)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	UpdateLayout();

	return true;
}

void Cdirectories_dlg::OnDelete() 
{
	int i = -1;
	while ((i = m_list.GetNextItem(-1, LVNI_SELECTED)) != -1)
	{
		m_library.erase_directory(string(m_list.GetItemText(i, 0)));
		m_list.DeleteItem(i);
	}
}

void Cdirectories_dlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_delete_button.EnableWindow(m_list.GetSelectedCount());	
	*pResult = 0;
}

void Cdirectories_dlg::OnDropFiles(HDROP hDropInfo) 
{
	int c_files = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char fname[MAX_PATH];
	for (int i = 0; i < c_files; i++)
	{
		DragQueryFile(hDropInfo, i, fname, MAX_PATH);
		strcpy(fname, (to_lower(fname) + "\\").c_str());
		if (m_library.directories().find(fname) == m_library.directories().end())
		{
			m_library.insert_directory(fname);
			m_list.InsertItem(m_list.GetItemCount(), fname);
		}
	}
	DragFinish(hDropInfo);
}
