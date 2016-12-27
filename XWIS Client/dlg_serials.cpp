#include "stdafx.h"
#include "dlg_serials.h"

#include "reg_key.h"
#include <virtual_binary.h>
#include "xcc_dirs.h"

Cdlg_serials::Cdlg_serials(CWnd* pParent /*=NULL*/)
	: CDialog(Cdlg_serials::IDD, pParent)
	, m_ts(_T(""))
	, m_ra2(_T(""))
	, m_yr(_T(""))
	, m_rg(_T(""))
{
}

void Cdlg_serials::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TS, m_ts);
	DDX_Text(pDX, IDC_RA2, m_ra2);
	DDX_Text(pDX, IDC_YR, m_yr);
	DDX_Text(pDX, IDC_RG, m_rg);
}

BEGIN_MESSAGE_MAP(Cdlg_serials, CDialog)
END_MESSAGE_MAP()

BOOL Cdlg_serials::OnInitDialog() 
{
	xcc_dirs::load_from_registry();
	add_game("Software\\Westwood\\Tiberian Sun", game_ts, m_ts);
	add_game("Software\\Westwood\\Red Alert 2", game_ra2, m_ra2);
	add_game("Software\\Westwood\\Yuri's Revenge", game_ra2_yr, m_yr);
	add_game("Software\\Westwood\\Renegade", game_rg, m_rg);
	CDialog::OnInitDialog();
	return true;
}

void Cdlg_serials::add_game(const string& reg_key, t_game game, CString& edit)
{
	Creg_key key;
	string serial;
	if (ERROR_SUCCESS != key.open(HKEY_LOCAL_MACHINE, reg_key, KEY_READ)
		|| ERROR_SUCCESS != key.query_value("Serial", serial)
		|| serial.size() != 22)
		return;
	Cvirtual_binary s;
	s.load(xcc_dirs::get_dir(game) + "woldata.key");
	for (size_t i = 0, j = 0; i < s.size(); i++, j++)
	{
		if (j == serial.size())
			j = 0;
		serial[j] = (serial[j] - s.data()[i] + 262) % 10 + '0';
	}
	edit = serial.c_str();
}

static void save_serial(const string& reg_key, t_game game, const CString& edit)
{
	string serial = edit;
	if (serial.size() != 22)
		return;
	Cvirtual_binary s;
	s.load(xcc_dirs::get_dir(game) + "woldata.key");
	for (size_t i = 0, j = 0; i < s.size(); i++, j++)
	{
		if (j == serial.size())
			j = 0;
		serial[j] = (serial[j] + s.data()[i] + 2) % 10 + '0';
	}
	Creg_key key;
	if (ERROR_SUCCESS == key.open(HKEY_LOCAL_MACHINE, reg_key, KEY_WRITE))
		key.set_value("Serial", serial);
}

void Cdlg_serials::OnCancel()
{
	OnOK();
}

void Cdlg_serials::OnOK()
{
	CDialog::OnOK();
	save_serial("Software\\Westwood\\Tiberian Sun", game_ts, m_ts);
	save_serial("Software\\Westwood\\Red Alert 2", game_ra2, m_ra2);
	save_serial("Software\\Westwood\\Yuri's Revenge", game_ra2_yr, m_yr);
	save_serial("Software\\Westwood\\Renegade", game_rg, m_rg);
}