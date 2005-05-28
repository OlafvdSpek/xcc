// XCCObjectExtractorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XCCObjectExtractorDlg.h"
#include "string_conversion.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCObjectExtractorDlg dialog


CXCCObjectExtractorDlg::CXCCObjectExtractorDlg(t_game game, CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(CXCCObjectExtractorDlg::IDD, pParent, "XOE_dlg")
{
	m_game = game;
	m_reg_key = "XOE_dlg";
	//{{AFX_DATA_INIT(CXCCObjectExtractorDlg)
	m_extract_to_edit = _T("");
	//}}AFX_DATA_INIT
}


void CXCCObjectExtractorDlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCObjectExtractorDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_LINK, m_link);
	DDX_Text(pDX, IDC_LINK_TITLE, m_link_title);
	DDX_Text(pDX, IDC_MAIL, m_mail);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_EXTRACT_TO_EDIT, m_extract_to_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXCCObjectExtractorDlg, ETSLayoutDialog)
	//{{AFX_MSG_MAP(CXCCObjectExtractorDlg)
	ON_BN_CLICKED(IDC_EXTRACT, OnExtract)
	ON_BN_CLICKED(IDC_EXTRACT_TO_BUTTON, OnExtractToButton)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCObjectExtractorDlg message handlers

BOOL CXCCObjectExtractorDlg::OnInitDialog()
{
	m_name = AfxGetApp()->GetProfileString(m_reg_key, "credits_name");
	m_mail = AfxGetApp()->GetProfileString(m_reg_key, "credits_mail");
	m_link_title = AfxGetApp()->GetProfileString(m_reg_key, "credits_link_title", "http://");
	m_link = AfxGetApp()->GetProfileString(m_reg_key, "credits_link");
	set_extract_to_dir(static_cast<string>(AfxGetApp()->GetProfileString(m_reg_key, "extract_to_dir", xcc_dirs::get_dir(m_game).c_str())));
	CreateRoot(VERTICAL)
		<< item(IDC_LIST, GREEDY)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
			<< (pane(VERTICAL, ABSOLUTE_HORZ)
				<< item(IDC_NAME_STATIC, NORESIZE)
				<< item(IDC_MAIL_STATIC, NORESIZE)
				<< item(IDC_LINK_TITLE_STATIC, NORESIZE)
				<< item(IDC_LINK_STATIC, NORESIZE)
				<< item(IDC_EXTRACT_TO_STATIC, NORESIZE)
				)
			<< (pane(VERTICAL, GREEDY)
				<< item(IDC_NAME, GREEDY)
				<< item(IDC_MAIL, GREEDY)
				<< item(IDC_LINK_TITLE, GREEDY)
				<< item(IDC_LINK, GREEDY)
				<< (pane(HORIZONTAL, ABSOLUTE_VERT)
					<< item(IDC_EXTRACT_TO_EDIT, GREEDY)
					<< item(IDC_EXTRACT_TO_BUTTON, NORESIZE)
					)
				)
			<< (pane(VERTICAL, ABSOLUTE_HORZ)
				<< itemGrowing(VERTICAL)
				<< item(IDC_EXTRACT, NORESIZE)
				<< item(IDOK, NORESIZE)
				)
			);
	ETSLayoutDialog::OnInitDialog();
	CWaitCursor wait;
	m_extract_object.open_default(m_game);
	m_extract_object.load();
	Crules_ts_ini_reader::t_object_type_list::const_iterator i;
	int j = 0;
	for (i = m_extract_object.get_rir().get_aircraft_type_list().begin(); i != m_extract_object.get_rir().get_aircraft_type_list().end(); i++)
		add(j++, i->first);
	for (i = m_extract_object.get_rir().get_building_type_list().begin(); i != m_extract_object.get_rir().get_building_type_list().end(); i++)
		add(j++, i->first);
	for (i = m_extract_object.get_rir().get_infantry_type_list().begin(); i != m_extract_object.get_rir().get_infantry_type_list().end(); i++)
		add(j++, i->first);
	for (i = m_extract_object.get_rir().get_vehicle_type_list().begin(); i != m_extract_object.get_rir().get_vehicle_type_list().end(); i++)
		add(j++, i->first);
	return true;
}

void CXCCObjectExtractorDlg::add(int j, string _name)
{
	char name[256];
	strcpy(name, _name.c_str());
	m_list.InsertItem(j, name);
}

void CXCCObjectExtractorDlg::OnExtract()
{
	if (UpdateData(true))
	{
		CWaitCursor wait;
		set_extract_to_dir(static_cast<string>(m_extract_to_edit));
		string path = m_extract_to_edit;
		AfxGetApp()->WriteProfileString(m_reg_key, "credits_name", m_name);
		AfxGetApp()->WriteProfileString(m_reg_key, "credits_mail", m_mail);
		AfxGetApp()->WriteProfileString(m_reg_key, "credits_link_title", m_link_title);
		AfxGetApp()->WriteProfileString(m_reg_key, "credits_link", m_link);
		AfxGetApp()->WriteProfileString(m_reg_key, "extract_to_dir", m_extract_to_edit);
		int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		while (index != -1)
		{
			string name = m_list.GetItemText(index, 0);
			Cxif_key k = m_extract_object.extract(name);
			Cextract_object::t_credits credits;
			credits.name = m_name;
			credits.mail = m_mail;
			credits.link_title = m_link_title;
			credits.link = m_link;
			Cextract_object::set_credits(k, credits);
			if (k.vdata().save(path + name + ".xif"))
				MessageBox("Error writing file.", NULL, MB_ICONERROR);
			index = m_list.GetNextItem(index, LVNI_ALL | LVNI_SELECTED);
		}
	}
}

void CXCCObjectExtractorDlg::set_extract_to_dir(const string& v)
{
	Cfname fname = v;
	fname.make_path();
	m_extract_to_edit = fname.get_path().c_str();
	UpdateData(false);
}


void CXCCObjectExtractorDlg::OnExtractToButton() 
{
    BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = GetSafeHwnd();
	bi.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
	ITEMIDLIST* idl = SHBrowseForFolder(&bi);
	if (idl)
	{
		char b[MAX_PATH];
		SHGetPathFromIDList(idl, b);
		set_extract_to_dir(b);
		LPMALLOC lpm;
		if (SHGetMalloc(&lpm) == NOERROR)
			lpm->Free(idl);
	}
}