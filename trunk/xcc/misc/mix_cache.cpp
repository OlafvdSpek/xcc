#include "stdafx.h"
#include <map>
#include "cc_file.h"
#include "crc.h"
#include "file32.h"
#include "mix_cache.h"
#include "xcc_dirs.h"

map<int, Cvirtual_binary> cache;

static string get_fname()
{
	return xcc_dirs::get_data_dir() + "global mix cache.dat";
}

static int get_ft_crc()
{
  boost::crc_32_type crc;
	for (int i = 0; i < ft_count; i++)
		crc.process_bytes(ft_name[i], strlen(ft_name[i]));
	return crc();
}

int mix_cache::load()
{
	Ccc_file f(true);
	if (f.open(get_fname()) || f.get_size() < 8)
		return 1;
	const byte* s = f.get_data();
	if (*reinterpret_cast<const int*>(s) != get_ft_crc())
		return 0;
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
	return 0;
}

int mix_cache::save()
{
	Cfile32 f;
	if (f.open(get_fname(), GENERIC_WRITE))
		return 1;
	f.write(get_ft_crc());
	f.write(cache.size());
	BOOST_FOREACH (auto& i, cache)
	{
		f.write(i.first);
		f.write(i.second.size());
		f.write(i.second.data(), i.second.size());
	}	
	return 0;
}

Cvirtual_binary mix_cache::get_data(int crc)
{
	auto i = find_ptr(cache, crc);
	return i ? *i : Cvirtual_binary();
}

void mix_cache::set_data(int crc, const Cvirtual_binary& v)
{
	cache[crc] = v;
}