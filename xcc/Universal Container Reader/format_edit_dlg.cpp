// format_edit_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "format_edit_dlg.h"

#include "string_conversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cformat_edit_dlg dialog


Cformat_edit_dlg::Cformat_edit_dlg(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cformat_edit_dlg::IDD, pParent, "format_edit_dlg")
{
	//{{AFX_DATA_INIT(Cformat_edit_dlg)
	m_extensions = _T("");
	m_name = _T("");
	m_registry_keys = _T("");
	//}}AFX_DATA_INIT
	m_buffer_w = 0;
}


void Cformat_edit_dlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cformat_edit_dlg)
	DDX_Control(pDX, IDC_VARS, m_vars);
	DDX_Control(pDX, IDC_BLOCKS, m_blocks);
	DDX_Text(pDX, IDC_EXTENSIONS, m_extensions);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_REGISTRY_KEYS, m_registry_keys);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cformat_edit_dlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(Cformat_edit_dlg)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_BLOCKS, OnGetdispinfoBlocks)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_VARS, OnGetdispinfoVars)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_BLOCKS, OnItemchangedBlocks)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cformat_edit_dlg message handlers

static int c_colums_blocks = 6;
static int c_colums_vars = 10;

BOOL Cformat_edit_dlg::OnInitDialog() 
{
	ETSLayoutDialog::OnInitDialog();
	
	{
		const char* column_label[] = {"I", "Add object", "Update object", "Count", "Offset", "Size"};

		m_blocks.SetRedraw(false);
		for (int i = 0; i < c_colums_blocks; i++)
			m_blocks.InsertColumn(i, column_label[i], LVCFMT_LEFT, -1, i);
		{
			int j = 0;
			for (Cucr_format::t_blocks::const_iterator i = m_format.blocks().begin(); i != m_format.blocks().end(); i++)
				m_blocks.SetItemData(m_blocks.InsertItem(m_blocks.GetItemCount(), LPSTR_TEXTCALLBACK), j++);
		}
		m_blocks.auto_size();
		m_blocks.SetRedraw(true);
	}
	{
		const char* column_label[] = {"I", "Big endian", "Block", "Var", "ID", "Name", "Offset", "Size", "Type", "Value"}; 

		m_vars.SetRedraw(false);
		m_vars.auto_size();
		m_vars.SetRedraw(true);
	}

	CreateRoot(VERTICAL)
		<< item(IDC_NAME, ABSOLUTE_VERT)
		<< item(IDC_EXTENSIONS, ABSOLUTE_VERT)
		<< item(IDC_REGISTRY_KEYS, ABSOLUTE_VERT)
		<< (pane(HORIZONTAL, GREEDY)
			<< item(IDC_BLOCKS, GREEDY)
			<< item(IDC_VARS, GREEDY)
			)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< itemGrowing(HORIZONTAL)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE)
			);
	UpdateLayout();

	m_blocks.SetItemState(0, LVNI_FOCUSED | LVNI_SELECTED, LVNI_FOCUSED | LVNI_SELECTED);
	
	return true;
}

const Cucr_format& Cformat_edit_dlg::get() const
{
	return m_format;
}

void Cformat_edit_dlg::set(const Cucr_format& v)
{
	m_format = v;
	m_name = v.name().c_str();
	m_extensions = v.extensions_string(";").c_str();
	m_registry_keys = v.registry_keys_string(";").c_str();
}

void Cformat_edit_dlg::OnGetdispinfoBlocks(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	const Cucr_format::t_block& e = m_format.blocks()[pDispInfo->item.lParam];
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		m_buffer[m_buffer_w] = n(pDispInfo->item.lParam);
		break;
	case 1:
		m_buffer[m_buffer_w] = e.add_object ? "Y" : "N";
		break;
	case 2:
		m_buffer[m_buffer_w] = e.update_object ? "Y" : "N";
		break;
	case 3:
		m_buffer[m_buffer_w] = n(e.count);
		break;
	case 4:
		m_buffer[m_buffer_w] = n(e.offset);
		break;
	case 5:
		m_buffer[m_buffer_w] = n(e.size);
		break;
	default:
		m_buffer[m_buffer_w].erase();
	}
	pDispInfo->item.pszText = const_cast<char*>(m_buffer[m_buffer_w].c_str());
	m_buffer_w--;
	if (m_buffer_w < 0)
		m_buffer_w += 4;
	*pResult = 0;
}

void Cformat_edit_dlg::OnGetdispinfoVars(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	m_buffer[m_buffer_w].erase();
	const Cucr_format::t_var& e = m_block->vars[pDispInfo->item.lParam];
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		m_buffer[m_buffer_w] = n(pDispInfo->item.lParam);
		break;
	case 1:
		m_buffer[m_buffer_w] = e.big_endian ? "Y" : "N";
		break;
	case 2:
		switch (e.id)
		{
		case Cucr_format::vi_block_offset:
		case Cucr_format::vi_object_offset:
			m_buffer[m_buffer_w] = n(e.block);
		}
		break;
	case 3:
		if (e.id == Cucr_format::vi_var_size)
			m_buffer[m_buffer_w] = n(e.var);
		break;
	case 4:
		m_buffer[m_buffer_w] = Cucr_format::get_vi_name(e.id);
		break;
	case 5:
		m_buffer[m_buffer_w] = e.name.c_str();
		break;
	case 6:
		if (e.offset)
			m_buffer[m_buffer_w] = n(e.offset);
		break;
	case 7:
		m_buffer[m_buffer_w] = n(e.size);
		break;
	case 8:
		m_buffer[m_buffer_w] = Cucr_format::get_vt_name(e.type);
		break;
	case 9:
		if (e.id == Cucr_format::vi_literal)
			m_buffer[m_buffer_w] = e.type == Cucr_format::vt_string ? e.string_value : n(e.int_value);
		break;
	default:
		m_buffer[m_buffer_w].erase();
	}
	pDispInfo->item.pszText = const_cast<char*>(m_buffer[m_buffer_w].c_str());
	m_buffer_w--;
	if (m_buffer_w < 0)
		m_buffer_w += 4;
	*pResult = 0;
}

void Cformat_edit_dlg::update_vars()
{
	m_vars.DeleteAllItems();
	if (!m_block)
		return;
	int j = 0;
	for (Cucr_format::t_vars::const_iterator i = m_block->vars.begin(); i != m_block->vars.end(); i++)
		m_vars.SetItemData(m_vars.InsertItem(m_vars.GetItemCount(), LPSTR_TEXTCALLBACK), j++);
	m_vars.auto_size();
}

void Cformat_edit_dlg::OnItemchangedBlocks(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uChanged & LVIF_STATE)
	{
		m_block = pNMListView->uNewState & LVIS_FOCUSED ? &m_format.blocks()[pNMListView->lParam] : NULL;
		update_vars();
	}	
	*pResult = 0;
}
