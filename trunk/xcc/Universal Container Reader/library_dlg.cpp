// library_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "library_dlg.h"

#include "directories_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Clibrary_dlg dialog


Clibrary_dlg::Clibrary_dlg(const Cucr_formats& formats, Cucr_library& library, CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Clibrary_dlg::IDD, pParent, "library_dlg"), m_formats(formats), m_library(library)
{
	//{{AFX_DATA_INIT(Clibrary_dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Clibrary_dlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Clibrary_dlg)
	DDX_Control(pDX, IDOK, m_ok_button);
	DDX_Control(pDX, IDC_TREE, m_tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Clibrary_dlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Clibrary_dlg)
	ON_BN_CLICKED(IDC_DIRECTORIES, OnDirectories)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, OnDblclkTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Clibrary_dlg message handlers

BOOL Clibrary_dlg::OnInitDialog() 
{
	ETSLayoutDialog::OnInitDialog();
	
	update_containers();
	
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, GREEDY)
			<< item(IDC_TREE, GREEDY)
			)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDC_DIRECTORIES, NORESIZE)
			<< item(IDC_REFRESH, NORESIZE)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	UpdateLayout();
	
	return true;
}

void Clibrary_dlg::insert_format(const Cucr_library::t_containers& containers)
{
	CTreeCtrl& tc = m_tree;
	for (Cucr_library::t_containers::const_iterator i = containers.begin(); i != containers.end(); i++)
	{
		string name = i->c_str();
		HTREEITEM p = TVI_ROOT;
		int a = 0;
		int b;
		while ((b = name.find('\\', a)) != string::npos)
		{
			t_map::const_iterator i = m_map.find(name.substr(0, b));
			p = i == m_map.end() ? m_map[name.substr(0, b)] = tc.InsertItem(name.substr(a, b - a).c_str(), p) : i->second;
			a = b + 1;
		}
		m_reverse_map[m_map[name] = tc.InsertItem(name.substr(a).c_str(), p)] = name;
	}
}

void Clibrary_dlg::OnDirectories() 
{
	Cdirectories_dlg dlg(m_library);
	if (IDOK != dlg.DoModal())
		return;
	m_library = dlg.library();
	m_library.scan(m_formats);
	update_containers();
}

void Clibrary_dlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	m_ok_button.EnableWindow(m_reverse_map.find(m_tree.GetSelectedItem()) != m_reverse_map.end());
	*pResult = 0;
}

void Clibrary_dlg::OnOK() 
{
	m_container = m_reverse_map.find(m_tree.GetSelectedItem())->second;
	ETSLayoutDialog::OnOK();
}

void Clibrary_dlg::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	t_reverse_map::const_iterator i = m_reverse_map.find(m_tree.GetSelectedItem());
	if (i != m_reverse_map.end())
	{
		m_container = i->second;
		EndDialog(IDOK);	
	}
	*pResult = 0;
}

void Clibrary_dlg::update_containers()
{
	m_tree.DeleteAllItems();
	m_map.clear();
	m_reverse_map.clear();
	const Cucr_library::t_containers& containers = m_library.containers();
	for (Cucr_library::t_containers::const_iterator i = containers.begin(); i != containers.end(); i++)
	{
		string name = i->c_str();
		HTREEITEM p = TVI_ROOT;
		int a = 0;
		int b;
		while ((b = name.find('\\', a)) != string::npos)
		{
			t_map::const_iterator i = m_map.find(name.substr(0, b));
			p = i == m_map.end() ? m_map[name.substr(0, b)] = m_tree.InsertItem(name.substr(a, b - a).c_str(), p) : i->second;
			a = b + 1;
		}
		m_reverse_map[m_map[name] = m_tree.InsertItem(name.substr(a).c_str(), p)] = name;
	}
}

void Clibrary_dlg::OnRefresh() 
{
	m_library.scan(m_formats);
	update_containers();
}
