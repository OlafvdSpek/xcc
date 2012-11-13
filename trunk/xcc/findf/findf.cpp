#include "stdafx.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "fname.h"
#include "file32.h"
#include "id_log.h"
#include "mix_cache.h"
#include "mix_file.h"
#include "multi_line.h"
#include "string_conversion.h"
#include "virtual_tfile.h"
#include "xcc_dirs.h"

using namespace boost;
using namespace std;

typedef map<int, string> t_file_list;

const string filename_chars = "-.0123456789_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
t_file_list flist;
const t_game game = game_ra2;

void init_filename_chars()
{
	/*
	ifstream f((xcc_dirs::get_data_dir() + "global mix database.txt").c_str());
	string s;
	while (getline(f, s))
	{
		Cmulti_line l = s;
		l.get_next_line('\t');
		l.get_next_line('\t');
		s = l.get_next_line('\t');
		for (int i = 0; i < s.length(); i++)
			filename_chars[s[i]]++;
	}
	*/
}

int check_mix(Cmix_file& f, const string& mix_name)
{
	int r = 0;
	for (int i = 0; i < f.get_c_files(); i++)
	{
		const int id = f.get_id(i);
		const string name = mix_database::get_name(game, id);
		flist[id] = mix_name;
		r += name.empty();
		if (f.get_type(id) == ft_mix)
		{
			Cmix_file g;
			g.open(id, f);
			check_mix(g, name.empty() ? nh(8, id) : name);
			g.close();
		}
	}
	cout << mix_name << " (" << game_name[f.get_game()] << "): " << r << '/' << f.get_c_files() << endl;
	return r;
}

void check_mix(const string& name)
{
	Cmix_file f;
	if (f.open(name))
		return;
	check_mix(f, Cfname(name).get_fname());
	f.close();
}

void check_dir(const string& name)
{
	WIN32_FIND_DATA finddata;
	HANDLE findhandle = FindFirstFile((name + "*.mix").c_str(), &finddata);
	if (findhandle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (~finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				check_mix(name + finddata.cFileName);
		}
		while (FindNextFile(findhandle, &finddata));
		FindClose(findhandle);
	}
}

void check_name(const string& name, ostream& log_f, bool check_chars = true)
{
	if (name.empty())
		return;
	if (check_chars)
	{
		for (int i = 0; i < name.length(); i++)
		{
			if (filename_chars.find(name[i]) == string::npos)
				return;
		}
	}
	if (name.length() >= 2 && tolower(name[1]) == 'a')
	{
		check_name(name.substr(0, 1) + 'd' + name.substr(2), log_f, false);
		check_name(name.substr(0, 1) + 'g' + name.substr(2), log_f, false);
		check_name(name.substr(0, 1) + 'l' + name.substr(2), log_f, false);
		check_name(name.substr(0, 1) + 't' + name.substr(2), log_f, false);
		check_name(name.substr(0, 1) + 'u' + name.substr(2), log_f, false);
	}
	if (name.find('.') == string::npos)
	{
		check_name(name + ".aud", log_f, false);
		check_name(name + ".avi", log_f, false);
		check_name(name + ".bik", log_f, false);
		check_name(name + ".bin", log_f, false);
		check_name(name + ".cps", log_f, false);
		check_name(name + ".des", log_f, false);
		check_name(name + ".fnt", log_f, false);
		check_name(name + ".hva", log_f, false);
		check_name(name + "bar.hva", log_f, false);
		check_name(name + "barl.hva", log_f, false);
		check_name(name + "tur.hva", log_f, false);
		check_name(name + ".ini", log_f, false);
		check_name(name + ".lun", log_f, false);
		check_name(name + ".map", log_f, false);
		check_name(name + ".mix", log_f, false);
		check_name(name + ".mpr", log_f, false);
		check_name(name + ".mrf", log_f, false);
		check_name(name + ".pak", log_f, false);
		check_name(name + ".pal", log_f, false);
		check_name(name + ".pcx", log_f, false);
		check_name(name + ".shp", log_f, false);
		check_name(name + ".sno", log_f, false);
		check_name(name + ".tem", log_f, false);
		check_name(name + ".tmp", log_f, false);
		check_name(name + ".txt", log_f, false);
		check_name(name + ".ubn", log_f, false);
		check_name(name + ".urb", log_f, false);
		check_name(name + ".voc", log_f, false);
		check_name(name + ".vqa", log_f, false);
		check_name(name + ".vqp", log_f, false);
		check_name(name + ".vxl", log_f, false);
		check_name(name + "bar.vxl", log_f, false);
		check_name(name + "barl.vxl", log_f, false);
		check_name(name + "tur.vxl", log_f, false);
		check_name(name + ".wav", log_f, false);
		check_name(name + ".wsa", log_f, false);
	}
	int id = Cmix_file::get_id(game, name);
	if (flist.find(id) != flist.end() && mix_database::get_name(game, id).empty())
		log_f << to_lower_copy(name) << '\t' << endl;
}

string find_file(const string& name)
{
	t_file_list::const_iterator i = flist.find(Cmix_file::get_id(game, name));
	return i == flist.end() ? "" : i->second;
}

void check_binary_file(const string& name, ostream& log_f)
{
	Ccc_file f(false);
	f.open(name);
	int size = f.get_size();
	char* data = new char[size + 1];
	f.read(data, size);
	data[size] = 0;
	f.close();
	int h = 0;
	while (h < size)
	{
		int p = h;
		while (p < size && data[p])
			p++;
		const string name = data + h;
		h = p + 1;
		check_name(name, log_f);
		/*
		for (int i = 0; i < name.length(); i++)
			check_name(name.substr(i), log_f);
		*/
	}
}

void check_text_file(const string& name, ostream& log_f)
{
	Ccc_file f(false);
	f.open(name);
	int size = f.get_size();
	char* data = new char[size + 1];
	f.read(data, size);
	data[size] = 0;
	f.close();
	int h = 0;
	while (h < size)
	{
		int p = h;
		while (p < size && filename_chars.find(data[p]) != string::npos)
			p++;
		data[p] = 0;
		const string name = data + h;
		h = p + 1;			
		check_name(name, log_f);
		/*
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 26; j++)
			check_name(name + nwzl(2, i) + static_cast<char>('a' + j), log_f);
		}
		*/
	}
}

int main()
{
	xcc_dirs::load_from_registry();
	Cmix_file::enable_ft_support();
	mix_cache::load();
	mix_database::load();
	check_dir(xcc_dirs::get_dir(game));
	check_dir(xcc_dirs::get_cd_dir());
	check_dir("f:/");
	int known = 0;
	int total = flist.size();
	for (t_file_list::const_iterator i = flist.begin(); i != flist.end(); i++)
		known += !mix_database::get_name(game, i->first).empty();
	ofstream log_f("c:/log.txt");
	for (t_file_list::const_iterator i = flist.begin(); i != flist.end(); i++)
		check_name(mix_database::get_name(game, i->first), log_f);
	if (0)
	{
		init_filename_chars();
		for (int i = 0; i < 256; i++)
		{
			if (filename_chars[i])
				log_f << static_cast<char>(i);
		}
		log_f << endl;
	}
	if (0)
	{
		Ccc_file f(true);
		f.open("c:/temp/filemon.log");
		Cvirtual_tfile t;
		t.load_data(f.vdata());
		while (!t.eof())
		{
			Cmulti_line l = t.read_line();
			l.get_next_line('\t');
			l.get_next_line('\t');
			l.get_next_line('\t');
			l.get_next_line('\t');
			check_name(static_cast<Cfname>(l.get_next_line('\t')).get_fname(), log_f);
		}
		f.close();
	}
	if (0)
	{
		for (t_file_list::const_iterator i = flist.begin(); i != flist.end(); i++)
		{
			Cfname name = mix_database::get_name(game, i->first);
			name.set_ext(".hva");
			int id = Cmix_file::get_id(game, name);
			if (flist.find(id) != flist.end() && mix_database::get_name(game, id).empty())
			{
				cout << "found: " << name.get_fname() << endl;
				log_f << name.get_fname() << '\t' << endl;
			}
		}
	}
	if (1)
	{
		// check_binary_file("c:/games/ra2/game.exe", log_f);
		// check_binary_file("c:/games/ra2/gamemd.exe", log_f);
		// check_text_file("c:/temp/missions.pkt", log_f);
		string name = "c:/temp/";
		WIN32_FIND_DATA finddata;
		HANDLE findhandle = FindFirstFile((name + "*.ini").c_str(), &finddata);
		if (findhandle != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (~finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					check_text_file(name + finddata.cFileName, log_f);
			}
			while (FindNextFile(findhandle, &finddata));
			FindClose(findhandle);
		}
	}
	if (0)
	{
		int id = Cmix_file::get_id(game, "");
		if (flist.find(id) != flist.end() && mix_database::get_name(game, id).empty())
			cout << "not found" << endl;
	}
	cout << "Known: " << known << endl
		<< "Total: " << total << endl;
	mix_cache::save();
	return 0;
}