// XCCObjectExtractorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "xcc mixer.h"
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
	: CDialog(CXCCObjectExtractorDlg::IDD, pParent)
{
	m_game = game;
	//{{AFX_DATA_INIT(CXCCObjectExtractorDlg)
	m_link = _T("http://");
	m_link_title = _T("");
	m_mail = _T("");
	m_name = _T("");
	//}}AFX_DATA_INIT
}


void CXCCObjectExtractorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXCCObjectExtractorDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_LINK, m_link);
	DDX_Text(pDX, IDC_LINK_TITLE, m_link_title);
	DDX_Text(pDX, IDC_MAIL, m_mail);
	DDX_Text(pDX, IDC_NAME, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXCCObjectExtractorDlg, CDialog)
	//{{AFX_MSG_MAP(CXCCObjectExtractorDlg)
	ON_BN_CLICKED(IDC_EXTRACT, OnExtract)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCObjectExtractorDlg message handlers

BOOL CXCCObjectExtractorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_extract_object.open_default(m_game);
	m_extract_object.load();
	Cextract_object::t_object_type_list::const_iterator i;
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
	int index = m_list.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	if (index < 0)
		return;
	UpdateData(true);
	string name = m_list.GetItemText(index, 0);
	CFileDialog dlg(false, "xif", to_lower(name).c_str(), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, "XIF files (*.xif)|*.xif|", this);
	if (IDOK == dlg.DoModal())
	{
		Cxif_key k = m_extract_object.extract(name);
		Cextract_object::set_credits(k, static_cast<string>(m_name), static_cast<string>(m_mail), static_cast<string>(m_link_title), static_cast<string>(m_link));
		if (!k.save_start())
		{
			if (file32_write(static_cast<string>(dlg.GetPathName()), k.key_data(), k.key_size()))
				MessageBox("Error writing file.", NULL, MB_ICONERROR);
			k.save_finish();
		}		
	}
}
