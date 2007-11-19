#include "stdafx.h"
#include "dlg_serials.h"
#include "reg_key.h"
#include "virtual_binary.h"
#include "xcc_dirs.h"

IMPLEMENT_DYNAMIC(Cdlg_serials, ETSLayoutDialog)

Cdlg_serials::Cdlg_serials(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cdlg_serials::IDD, pParent)
{
	m_edit = _T("");
}

void Cdlg_serials::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT, m_edit);
}

BEGIN_MESSAGE_MAP(Cdlg_serials, ETSLayoutDialog)
END_MESSAGE_MAP()

BOOL Cdlg_serials::OnInitDialog() 
{
	xcc_dirs::load_from_registry();
	add_game("Software\\Westwood\\Renegade", game_rg, 0xc);
	add_game("Software\\Westwood\\Tiberian Sun", game_ts, 0x12);
	add_game("Software\\Westwood\\Emperor", game_ebfd, 0x1f);
	add_game("Software\\Westwood\\Red Alert 2", game_ra2, 0x21);
	add_game("Software\\Westwood\\Nox", game_nox, 0x25);
	add_game("Software\\Westwood\\Yuri's Revenge", game_ra2_yr, 0x29);
	CreateRoot(VERTICAL)
		<< item(IDC_EDIT, GREEDY)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
				<< itemGrowing(HORIZONTAL)
				<< item(IDCANCEL, NORESIZE)
			)
		;
	ETSLayoutDialog::OnInitDialog();
	return true;
}

void Cdlg_serials::add_game(const string& reg_key, int game, int gsku)
{
	Creg_key key;
	string serial;
	if (ERROR_SUCCESS != key.open(HKEY_LOCAL_MACHINE, reg_key, KEY_READ)
		|| ERROR_SUCCESS != key.query_value("Serial", serial)
		|| serial.size() != 22)
		return;
	Cvirtual_binary s;
	s.load(xcc_dirs::get_dir(static_cast<::t_game>(game)) + "woldata.key");
	for (int i = 0, j = 0; i < s.size(); i++, j++)
	{
		if (j == serial.length())
			j = 0;
		serial[j] = (262 - s.data()[i] + serial[j]) % 10 + '0';
	}
	m_edit += game_name[game];
	m_edit += ": ";
	m_edit += serial.c_str();
	m_edit += "\r\n";
}
