#include "stdafx.h"
#include <map>
#include "cc_file.h"
#include "crc.h"
#include "file32.h"
#include "mix_cache.h"
#include "xcc_dirs.h"

using namespace std;

/*
class Ccache_entry
{
public:
	const void* get_data() const
	{
		return m_data;
	}

	int get_size() const
	{
		return m_size;
	}

	Ccache_entry()
	{
		m_data = NULL;
		m_size = 0;
	}

	Ccache_entry(const void* data, int size)
	{
		m_data = new byte[size];
		m_size = size;
		memcpy(m_data, data, size);
	}

	Ccache_entry(const Ccache_entry& v)
	{
		m_data = new byte[v.m_size];
		m_size = v.m_size;
		memcpy(m_data, v.m_data, v.m_size);
	}

	const Ccache_entry& operator=(const Ccache_entry& v)
	{
		delete[] m_data;
		m_data = new byte[v.m_size];
		m_size = v.m_size;
		memcpy(m_data, v.m_data, v.m_size);
		return *this;
	}

	~Ccache_entry()
	{
		delete[] m_data;
	}
private:
	void* m_data;
	int m_size;
};

typedef map<int, Ccache_entry> t_cache;
*/
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

const void* mix_cache::get_data(int crc)
{
	t_cache::const_iterator i = cache.find(crc);
	return i == cache.end() ? NULL : i->second.data();
}

void mix_cache::set_data(int crc, const void* data, int size)
{
	cache[crc] = Cvirtual_binary(data, size);
}