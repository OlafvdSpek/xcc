#include "stdafx.h"

class Creg_key
{
public:
	Creg_key();
	Creg_key(HKEY, const string& value_name, REGSAM sam_desired);
	Creg_key(const Creg_key&, const string& value_name, REGSAM sam_desired);
	~Creg_key();
	LONG open(HKEY, const string& value_name, REGSAM sam_desired);
	LONG open(const Creg_key&, const string& value_name, REGSAM sam_desired);
	LONG close();
	LONG query_value(const string& value_name, string& value);
	string query_value(const string& value_name);
	LONG set_value(const string& value_name, const string& value);
private:
	Creg_key(const Creg_key&);
	HKEY m_h;
};

Creg_key::Creg_key()
{
	m_h = NULL;
}

Creg_key::Creg_key(HKEY key, const string& value_name, REGSAM sam_desired)
{
	if (open(key, value_name, sam_desired) != ERROR_SUCCESS)
		throw exception();
}

Creg_key::Creg_key(const Creg_key& key, const string& value_name, REGSAM sam_desired)
{
	if (open(key.m_h, value_name, sam_desired) != ERROR_SUCCESS)
		throw exception();
}

Creg_key::~Creg_key()
{
	close();
}

LONG Creg_key::open(HKEY key, const string& value_name, REGSAM sam_desired)
{
	return RegOpenKeyEx(key, value_name.c_str(), 0, sam_desired, &m_h);
};

LONG Creg_key::open(const Creg_key& key, const string& value_name, REGSAM sam_desired)
{
	return open(key.m_h, value_name, sam_desired);
};

LONG Creg_key::close()
{
	if (!m_h)
		return ERROR_SUCCESS;
	LONG result = RegCloseKey(m_h);
	m_h = NULL;
	return result;
}

LONG Creg_key::query_value(const string& value_name, string& value)
{
	DWORD cb_d = 0;
	LONG result = RegQueryValueEx(m_h, value_name.c_str(), NULL, NULL, NULL, &cb_d);
	if (result != ERROR_SUCCESS)
		return result;
	vector<BYTE> d(cb_d);
	result = RegQueryValueEx(m_h, value_name.c_str(), NULL, NULL, &d.front(), &cb_d);
	if (result == ERROR_SUCCESS && cb_d)
		value.assign(reinterpret_cast<char*>(&d.front()), cb_d - 1);
	return result;
}

string Creg_key::query_value(const string& value_name)
{
	string d;
	if (query_value(value_name, d) != ERROR_SUCCESS)
		throw exception();
	return d;
}

LONG Creg_key::set_value(const string& value_name, const string& value)
{
	return RegSetValueEx(m_h, value_name.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(value.c_str()), value.size());
}

class Cgame
{
public:
	Cgame(Creg_key& key, const string& prefix);

	string m_folder;
	string m_executable;
	string m_args;
};

Cgame::Cgame(Creg_key& key, const string& prefix)
{
	m_folder = key.query_value(prefix + "folder");
	m_executable = key.query_value(prefix + "executable");
	m_args = key.query_value(prefix + "args");
}

wstring mbyte_to_wchar(const string& s)
{
	vector<wchar_t> t(MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, 0));
	if (!MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, &t.front(), t.size()))
		throw std::exception("MultiByteToWideChar failed");
	return &t.front();
}

HRESULT create_shortcut(const string& target, const string& arguments, const string& save_as)
{
	IShellLink* sl = NULL;
	HRESULT hres;
	if (SUCCEEDED(hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, reinterpret_cast<void**>(&sl))))
	{
		sl->SetPath(target.c_str());
		sl->SetArguments(arguments.c_str());
		IPersistFile* pf = NULL;
		if (SUCCEEDED(hres = sl->QueryInterface(IID_IPersistFile, reinterpret_cast<void**>(&pf))))
		{
			wstring name = mbyte_to_wchar(save_as.c_str());
			hres = pf->Save(name.c_str(), true);
			pf->Release();
		}
		sl->Release();
	}
	return hres;
}

bool get_special_folder_path(HWND hwnd, string& path, int folder, bool create)
{
	char d[MAX_PATH];
	bool result = SHGetSpecialFolderPath(hwnd, d, folder, create);
	if (result)
		path = d;
	return result;
}

string get_special_folder_path(HWND hwnd, int folder, bool create)
{
	string d;
	if (!get_special_folder_path(hwnd, d, folder, create))
		throw exception();
	return d;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
	{
		CoInitialize(NULL); 
		string common_programs = get_special_folder_path(NULL, CSIDL_COMMON_PROGRAMS, true) + "\\Command & Conquer";
		CreateDirectory(common_programs.c_str(), NULL);
		Creg_key key_ea_games(HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Games", KEY_QUERY_VALUE | KEY_SET_VALUE);
		Creg_key key_tfd(HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA Games\\Command and Conquer The First Decade", KEY_QUERY_VALUE);
		Creg_key key_westwood(HKEY_LOCAL_MACHINE, "SOFTWARE\\Westwood", KEY_QUERY_VALUE | KEY_SET_VALUE);
		try
		{
			Cgame td(key_tfd, "cc_");
			Creg_key(key_westwood, "Command & Conquer Windows 95 Edition", KEY_QUERY_VALUE | KEY_SET_VALUE).set_value("InstallPath", td.m_folder + "\\" + td.m_executable);
			create_shortcut(td.m_folder + "\\" + td.m_executable, td.m_args, common_programs + "\\Tiberian Dawn.lnk");
		}
		catch (exception&)
		{
		}
		try
		{
			Cgame ra(key_tfd, "ra_");
			Creg_key(key_westwood, "Red Alert Windows 95 Edition", KEY_QUERY_VALUE | KEY_SET_VALUE).set_value("InstallPath", ra.m_folder + "\\" + ra.m_executable);
			create_shortcut(ra.m_folder + "\\" + ra.m_executable, ra.m_args, common_programs + "\\Red Alert.lnk");
		}
		catch (exception&)
		{
		}
		try
		{
			Cgame ts(key_tfd, "ts_");
			Creg_key(key_westwood, "Tiberian Sun", KEY_QUERY_VALUE | KEY_SET_VALUE).set_value("InstallPath", ts.m_folder + "\\" + ts.m_executable);
			create_shortcut(ts.m_folder + "\\" + ts.m_executable, ts.m_args, common_programs + "\\Tiberian Sun.lnk");
		}
		catch (exception&)
		{
		}
		try
		{
			Cgame ra2(key_tfd, "r2_");
			Creg_key(key_westwood, "Red Alert 2", KEY_QUERY_VALUE | KEY_SET_VALUE).set_value("InstallPath", ra2.m_folder + "\\" + ra2.m_executable);
			create_shortcut(ra2.m_folder + "\\" + ra2.m_executable, ra2.m_args, common_programs + "\\Red Alert 2.lnk");
		}
		catch (exception&)
		{
		}
		try
		{
			Cgame ra2_yr(key_tfd, "yr_");
			Creg_key(key_westwood, "Yuri's Revenge", KEY_QUERY_VALUE | KEY_SET_VALUE).set_value("InstallPath", ra2_yr.m_folder + "\\" + ra2_yr.m_executable);
			create_shortcut(ra2_yr.m_folder + "\\" + ra2_yr.m_executable, ra2_yr.m_args, common_programs + "\\Yuri's Revenge.lnk");
		}
		catch (exception&)
		{
		}
		try
		{
			Cgame rg(key_tfd, "rn_");
			Creg_key(key_westwood, "Renegade", KEY_QUERY_VALUE | KEY_SET_VALUE).set_value("InstallPath", rg.m_folder + "\\" + rg.m_executable);
			create_shortcut(rg.m_folder + "\\" + rg.m_executable, rg.m_args, common_programs + "\\Renegade.lnk");
		}
		catch (exception&)
		{
		}
		try
		{
			Cgame gr(key_tfd, "gr_");
			Creg_key(key_ea_games, "Generals", KEY_QUERY_VALUE | KEY_SET_VALUE).set_value("InstallPath", gr.m_folder + "\\" + gr.m_executable);
			create_shortcut(gr.m_folder + "\\" + gr.m_executable, gr.m_args, common_programs + "\\Generals.lnk");
		}
		catch (exception&)
		{
		}
		try
		{
			Cgame gr_zh(key_tfd, "zh_");
			Creg_key(key_ea_games, "Command and Conquer Generals Zero Hour", KEY_QUERY_VALUE | KEY_SET_VALUE).set_value("InstallPath", gr_zh.m_folder + "\\" + gr_zh.m_executable);
			create_shortcut(gr_zh.m_folder + "\\" + gr_zh.m_executable, gr_zh.m_args, common_programs + "\\Zero Hour.lnk");
		}
		catch (exception&)
		{
		}
	}
	catch (exception&)
	{
		return 1;
	}
	return 0;
}
