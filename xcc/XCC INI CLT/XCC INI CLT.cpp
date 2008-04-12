#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "cc_file.h"
#include "neat_ini_reader.h"

void sub_section(const string& name, const Cneat_key_list& a, const Cneat_key_list& b, ofstream& f)
{
	const Cneat_key_list::t_key_list& akl = a.get_key_list();
	const Cneat_key_list::t_key_map& akm = a.get_key_map();
	const Cneat_key_list::t_key_list& bkl = b.get_key_list();
	const Cneat_key_list::t_key_map& bkm = b.get_key_map();
	bool write_header = true;
	Cneat_key_list::t_key_list::const_iterator i;
	for (i = akl.begin(); i != akl.end(); i++)
	{
		string key_name = (*i)->first;
		string key_value = (*i)->second;
		Cneat_key_list::t_key_map::const_iterator j = bkm.find(key_name);
		if (j == bkm.end() || key_value != j->second)
		{
			if (write_header)
			{
				f << '[' << name << ']' << endl;
				write_header = false;
			}
			f << key_name << '=' << key_value << endl;
		}
	}
	for (i = bkl.begin(); i != bkl.end(); i++)
	{
		string key_name = (*i)->first;
		if (akm.find(key_name) == akm.end())
		{
			if (write_header)
			{
				f << '[' << name << ']' << endl;
				write_header = false;
			}
			f << key_name << '=' << endl;
		}
	}
	if (!write_header)
		f << endl;
}

int main(int c_args, char** arg)
{
	cerr << " XCC INI CLT, Copyright (C) Olaf van der Spek 2002         OlafvdSpek@GMail.Com" << endl
		<< endl;
	if (c_args != 5)
	{
		cerr << "Syntax:" << endl
			<< "  xcc_ini_clt <inifile> - <inifile> <inifile> or" << endl
			<< "  xcc_ini_clt <inifile> + <inifile> <inifile>" << endl;
		return 1;
	}
	Cneat_ini_reader ir1, ir2;
	const string fname1 = arg[1];
	const string mode = arg[2];
	const string fname2 = arg[3];
	const string fname3 = arg[4];
	Ccc_file f1(true);
	int error = f1.open(fname1);
	if (error)
		cerr << "Unable to open " << fname1 << endl;
	else
	{
		Ccc_file f2(true);
		error = f2.open(fname2);
		if (error)
			cerr << "Unable to open " << fname2 << endl;
		else
		{
			ir1.process(f1.get_data(), f1.get_size());
			if (mode == "+")
				ir1.process(f2.get_data(), f2.get_size());
			else
				ir2.process(f2.get_data(), f2.get_size());
			f2.close();
		}
		f1.close();
	}
	if (error)
		return error;
	ofstream f3(fname3.c_str());
	if (mode == "-")
	{
		const Cneat_ini_reader::t_section_list& sl1 = ir1.get_section_list();
		const Cneat_ini_reader::t_section_list& sl2 = ir2.get_section_list();
		const Cneat_ini_reader::t_section_map& sm1 = ir1.get_section_map();
		const Cneat_ini_reader::t_section_map& sm2 = ir2.get_section_map();
		Cneat_ini_reader::t_section_list::const_iterator i;
		for (i = sl1.begin(); i != sl1.end(); i++)
		{
			string section_name = (*i)->first;
			Cneat_ini_reader::t_section_map::const_iterator j = sm2.find(section_name);
			sub_section(section_name, (*i)->second, j == sm2.end() ? Cneat_key_list() : j->second, f3);
		}
		for (i = sl2.begin(); i != sl2.end(); i++)
		{
			string section_name = (*i)->first;
			if (sm1.find(section_name) == sm1.end())
				sub_section(section_name, Cneat_key_list(), (*i)->second, f3);
		}
	}
	else if (mode == "+")
	{
		const Cneat_ini_reader::t_section_list& sl1 = ir1.get_section_list();
		for (Cneat_ini_reader::t_section_list::const_iterator i = sl1.begin(); i != sl1.end(); i++)
		{
			bool write_header = true;
			const Cneat_key_list::t_key_list& kl = (*i)->second.get_key_list();
			for (Cneat_key_list::t_key_list::const_iterator j = kl.begin(); j != kl.end(); j++)
			{
				string key_value = (*j)->second;
				if (key_value.empty())
					continue;
				if (write_header)
				{
					f3 << '[' << (*i)->first << ']' << endl;
					write_header = false;
				}
				f3 << (*j)->first << '=' << key_value << endl;
			}
			if (!write_header)
				f3 << endl;
		}
	}
	return 0;
}
