#include "stdafx.h"
#include <map>
#include "cc_file.h"
#include "crc.h"
#include "file32.h"
#include "mix_cache.h"
#include "xcc_dirs.h"

using namespace std;

typedef map<int, Cvirtual_binary> t_cache;

t_cache cache;

static string get_fname()
{
	return xcc_dirs::get_data_dir() + "global mix cache.dat";
}

static int get_ft_crc()
{
	Ccrc crc;
	crc.init();
	for (int i = 0; i < ft_count; i++)
		crc.do_block(ft_name[i], strlen(ft_name[i]));
	return crc.get_crc();
}

int mix_cache::load()
{
	int error = 0;
	Ccc_file f(true);
	if (f.open(get_fname()))
		error = 1;
	else 
	{
		if (f.get_size() < 8)
			error = 1;
		else
		{
			const byte* s = f.get_data();
			if (*reinterpret_cast<const int*>(s) == get_ft_crc())
			{
				s += 4;
				int count = *reinterpret_cast<const int*>(s);
				s += 4;
				while (count--)
				{
					int crc = *reinterpret_cast<const int*>(s);
					s += 4;
					int size = *reinterpret_cast<const int*>(s);
					s += 4;
					cache[crc] = Cvirtual_binary(s, size);
					s += size;
				}
			}
		}
		f.close();
	}
	return error;
}

int mix_cache::save()
{
	int error = 0;
	Cfile32 f;
	if (f.open(get_fname(), GENERIC_WRITE))
		error = 1;
	else 
	{
		f.write(get_ft_crc());
		f.write(cache.size());
		for (t_cache::const_iterator i = cache.begin(); i != cache.end(); i++)
		{
			f.write(i->first);
			f.write(i->second.size());
			f.write(i->second.data(), i->second.size());
		}	
		f.close();
	}
	return error;
}

Cvirtual_binary mix_cache::get_data(int crc)
{
	t_cache::const_iterator i = cache.find(crc);
	return i == cache.end() ? Cvirtual_binary() : i->second;
}

void mix_cache::set_data(int crc, const Cvirtual_binary& v)
{
	cache[crc] = v;
}