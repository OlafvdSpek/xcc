#include "stdafx.h"
#include "XCC RA2 Map Updater.h"

#include <boost/algorithm/string.hpp>
#include <afxinet.h>
#include <fstream>
#include "download_dlg.h"
#include "file32.h"
#include "multi_line.h"
#include "string_conversion.h"
#include <virtual_binary.h>
#include "virtual_file.h"
#include "virtual_tfile.h"
#include "xcc_dirs.h"
#include "xcc_registry.h"
#include "xif_key.h"

BEGIN_MESSAGE_MAP(CXCCRA2MapUpdaterApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCRA2MapUpdaterApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CXCCRA2MapUpdaterApp::CXCCRA2MapUpdaterApp()
{
}

CXCCRA2MapUpdaterApp theApp;

BOOL CXCCRA2MapUpdaterApp::InitInstance()
{
	xcc_dirs::load_from_registry();

	if (Cfname(xcc_dirs::get_exe(game_ra2)).exists())
	{
		if (0)
			create();
		else if (!update())
			ShellExecute(NULL, "open", xcc_dirs::get_exe(game_ra2).c_str(), NULL, NULL, SW_SHOW);
	}
	else
		MessageBox(NULL, "Unable to find RA2.", NULL, MB_ICONERROR);
	
	return false;
}

int CXCCRA2MapUpdaterApp::update()
{
	int error = 0;
	try
	{
		CWaitCursor wait;
		CInternetSession is;
		CHttpFile* f = reinterpret_cast<CHttpFile*>(is.OpenURL("http://xccu.sourceforge.net/ra2_maps/official.ucf"));
		if (!f)
			error = 1;
		else
		{
			string s;
			while (1)
			{
				int cb_p = f->GetLength();
				if (!cb_p)
					break;
				char* p = new char[cb_p + 1];
				f->Read(p, cb_p);
				p[cb_p] = 0;
				s += p;
				delete[] p;
			}
			f->Close();
			Cvirtual_tfile f;
			f.load_data(Cvirtual_binary(s.c_str(), s.length()));
			while (!f.eof())
			{
				Cmulti_line l = f.read_line();
				Cfname fname = xcc_dirs::get_dir(game_ra2) + l.get_next_line('=') + ".mmx";
				if (!fname.exists())
				{
					string version = l.get_next_line(',');
					string link = l.get_next_line(',');
					error = download_update(link, fname);
					if (error)
					{
						delete_file(fname);
						MessageBox(NULL, "Error retrieving update.", NULL, MB_ICONERROR);
						error = 0;
					}
				}
			}
		}
	}
	catch (CInternetException*)
	{
		error = 1;
	}
	if (error)
		MessageBox(NULL, "Error querying for update.", NULL, MB_ICONERROR);
	return error;
}

enum 
{
	vi_fname,
	vi_fdata,
};

int CXCCRA2MapUpdaterApp::download_update(string link, string fname)
{
	int error = 0;
	CInternetSession is;
	CHttpFile* f = reinterpret_cast<CHttpFile*>(is.OpenURL(link.c_str(), INTERNET_FLAG_TRANSFER_BINARY));
	if (!f)
		error = 1;
	else 
	{
		Cvirtual_file h;
		DWORD status;
		if (!f->QueryInfoStatusCode(status))
			error = 2;
		else if (status != 200)
			error = 3;
		else
		{
			int total_size = f->Seek(0, CFile::end);
			f->Seek(0, CFile::begin);
			Cdownload_dlg dlg;
			dlg.set(link, fname, total_size);
			dlg.Create(Cdownload_dlg::IDD, NULL);
			dlg.EnableWindow(false);
			Cvirtual_binary t;
			while (!error)
			{
				int cb_p = min<int>(f->GetLength(), 1 << 10);
				if (!cb_p)
					break;
				f->Read(t.write_start(cb_p), cb_p);
				h.write(t);
				dlg.set_size(h.size());
				dlg.UpdateWindow();
			}
			h.compact();
			Cxif_key k;
			if (k.load_key(h.data(), h.size()))
				error = 5;
			else
			{
				for (t_xif_key_map::const_iterator ki = k.m_keys.begin(); ki != k.m_keys.end(); ki++)
				{
					if (error)
						break;
					const Cxif_key& l = ki->second;
					string fext = boost::to_lower_copy(Cfname(l.get_value_string(vi_fname)).get_fext());
					if (fext != ".mmx"
						&& (fext != ".yro") || !Cfname(xcc_dirs::get_exe(game_ra2_yr)).exists())
						continue;
					if (file32_write(Cfname(fname).get_path() + l.get_value_string(vi_fname), l.get_value(vi_fdata).get_data(), l.get_value(vi_fdata).get_size()))
						error = 6;
				}
			}
			dlg.DestroyWindow();
		}
		f->Close();
	}
	return error;
}

static void scan_dir(string in_dir, string out_dir, string postfix, ofstream& f)
{
	WIN32_FIND_DATA fd;
	HANDLE findhandle = FindFirstFile((in_dir + '*' + postfix).c_str(), &fd);
	if (findhandle != INVALID_HANDLE_VALUE)
	{		
		do
		{
			if (~fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				string title = boost::to_lower_copy(Cfname(fd.cFileName).get_ftitle());
				Cvirtual_binary fdata;
				fdata.load(in_dir + fd.cFileName);
				Cxif_key k;
				Cxif_key& l = k.open_key_write(0);
				l.set_value_string(vi_fname, boost::to_lower_copy(string(fd.cFileName)));
				l.set_value_binary(vi_fdata, fdata);
				k.vdata().save(out_dir + title + ".xmuf");
				f << title << "=,http://xccu.sourceforge.net/ra2_maps/" << title << ".xmuf" << endl;
			}
		}
		while (FindNextFile(findhandle, &fd));
		FindClose(findhandle);
	}
}

void CXCCRA2MapUpdaterApp::create()
{
	const string in_dir = xcc_dirs::get_dir(game_ra2);
	const string out_dir = "z:/xhp/ra2_maps/";
	ofstream f((out_dir + "official.ucf").c_str());
	scan_dir(in_dir, out_dir, ".mmx", f);
	scan_dir(in_dir, out_dir, ".yro", f);
}
