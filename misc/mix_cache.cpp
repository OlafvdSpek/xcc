/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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

static int write_int(Cfile32& f, int32_t v)
{
  return f.write(data_ref(&v, sizeof(v)));
}

int mix_cache::load()
{
	Ccc_file f(true);
	if (f.open(get_fname()) || f.get_size() < 8)
		return 1;
	const byte* s = f.data();
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
	write_int(f, get_ft_crc());
	write_int(f, cache.size());
	for (auto& i : cache)
	{
		write_int(f, i.first);
		write_int(f, i.second.size());
		f.write(i.second);
	}	
	return 0;
}

Cvirtual_binary mix_cache::get_data(int crc)
{
	return find_ptr2(cache, crc);
}

void mix_cache::set_data(int crc, const Cvirtual_binary& v)
{
	cache[crc] = v;
}