// mix_file.cpp: implementation of the Cmix_file class.
//
//////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include <assert.h>
#include <blowfish.h>
#include <crc.h>
#include "id_log.h"
#include "mix_cache.h"
#include <mix_decode.h>
#include "mix_file.h"
#include "pak_file.h"
#include <string_conversion.h>
#include "xcc_lmd_file.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cmix_file::Cmix_file():
    Ccc_file(false)
{
	m_mix_expansion = false;
    m_index = NULL;
	m_index_ft = NULL;
}

bool Cmix_file::is_valid()
{
	const byte* data = get_data();
	const t_mix_header& header = *reinterpret_cast<const t_mix_header*>(data);
	int size = get_size();
	if (sizeof(t_mix_header) > size)
		return false;
	if (header.c_files && sizeof(t_mix_header) + header.c_files * sizeof(t_mix_index_entry) + header.size == size)
		return true;
	if (header.flags & ~(mix_encrypted | mix_checksum))
		return false;
	m_has_checksum = header.flags & mix_checksum;
	m_is_encrypted = header.flags & mix_encrypted;
	Cblowfish bf;
	if (m_is_encrypted)
	{
		byte key[cb_mix_key];
		get_blowfish_key(data + 4, key);
		bf.set_key(key, cb_mix_key);
	}
	int error = 0;
	{
		if (m_is_encrypted)
		{
			t_mix_header* header = reinterpret_cast<t_mix_header*>(new byte[8]);
			bf.decipher(data + 84, header, 8);
			if (!header->c_files || 4 + (m_is_encrypted ? 80 : 0) + sizeof(t_mix_header) + 2 + (header->c_files * sizeof(t_mix_index_entry) + 5 & ~7) + header->size + (m_has_checksum ? 20 : 0) != size)
				error = true;
		}
		else
		{
			const t_mix_header* header = reinterpret_cast<const t_mix_header*>(data + 4);
			if (!header->c_files || 4 + sizeof(t_mix_header) + header->c_files * sizeof(t_mix_index_entry) + header->size + (m_has_checksum ? 20 : 0) != size)
				error = true;
		}
	}
	return !error;
}

#define test_fail(res) { int v = res; if (v) { clean_up(); return v; }}

int Cmix_file::post_open()
{
	Cpak_file f;
	byte* data;
	if (get_data())
	{
		data = NULL;
		f.load(get_data(), get_size());
	}
	else
	{
		int size = min(get_size(), 64 << 10);
		data = new byte[size];
		test_fail(read(data, size));
		f.load(data, get_size());
	}
	if (f.is_valid())
	{
		m_game = game_dune2;
		m_is_encrypted = m_has_checksum = false;
		m_c_files = f.get_c_files();
		if (m_c_files >> 12)
			test_fail(1);
		int cb_index = m_c_files * sizeof(t_mix_index_entry);
		m_index = new t_mix_index_entry[m_c_files];
		for (int i = 0; i < m_c_files; i++)
		{
			string name = f.get_name(i);
			mix_database::add_name(m_game, name, "-");
			m_index[i].id = get_id(get_game(), name);
			m_index[i].offset = f.get_offset(name);
			m_index[i].size = f.get_size(name);
		}
	}
	else
	{
		t_mix_header header;
		seek(0);
		test_fail(read(&header, sizeof(t_mix_header)));
		if (header.c_files)
		{
			m_game = game_td;
			m_is_encrypted = m_has_checksum = false;
			m_c_files = header.c_files;
			int cb_index = m_c_files * sizeof(t_mix_index_entry);
			if (header.c_files >> 12 || get_size() != 6 + cb_index + header.size)
				test_fail(1);
			m_index = new t_mix_index_entry[m_c_files];
			test_fail(read(m_index, cb_index));
			for (int i = 0; i < m_c_files; i++)
				m_index[i].offset += 6 + cb_index;
		}
		else
		{
			m_has_checksum = header.flags & mix_checksum;
			m_is_encrypted = header.flags & mix_encrypted;
			bool aligned = true;
			Cblowfish bf;
			seek(4);
			if (m_is_encrypted)
			{
				byte key_source[cb_mix_key_source];
				read(key_source, cb_mix_key_source);
				byte key[cb_mix_key];
				get_blowfish_key(key_source, key);
				bf.set_key(key, cb_mix_key);
				byte e[8];
				read(e, 8);
				bf.decipher(e, e, 8);
				memcpy(&header, e, sizeof(t_mix_header));
				m_c_files = header.c_files;
				const int cb_index = m_c_files * sizeof(t_mix_index_entry);
				const int cb_f = cb_index + 5 & ~7;
				if (get_size() != 92 + cb_f + header.size + (m_has_checksum ? 20 : 0))
					test_fail(1);
				if (m_c_files)
				{
					byte* f = new byte[cb_f];
					read(f, cb_f);
					bf.decipher(f, f, cb_f);
					m_index = new t_mix_index_entry[m_c_files];
					memcpy(m_index, e + 6, 2);
					memcpy(reinterpret_cast<byte*>(m_index) + 2, f, cb_index - 2);
					delete[] f;
					for (int i = 0; i < m_c_files; i++)
					{
						if (m_index[i].offset & 0xf)
							aligned = false;
						m_index[i].offset += 92 + cb_f;
					}
				}
			}
			else
			{
				read(&header, sizeof(header));
				m_c_files = header.c_files;
				const int cb_index = m_c_files * sizeof(t_mix_index_entry);
				if (get_size() != 4 + sizeof(t_mix_header) + cb_index + header.size + (m_has_checksum ? 20 : 0))
					test_fail(1);				
				m_index = new t_mix_index_entry[m_c_files];
				read(m_index, cb_index);
				for (int i = 0; i < m_c_files; i++)
				{
					if (m_index[i].offset & 0xf)
						aligned = false;
					m_index[i].offset += 4 + sizeof(t_mix_header) + cb_index;
				}
			}
			m_game = is_encrypted() ? game_ra : game_ts;
			for (int i = 0; i < get_c_files(); i++)
			{
				if (get_id(i) == 0x763c81dd)
				{
					m_game = game_ts;
					break;
				}
			}
			if (m_game == game_ra && aligned)
				m_game = game_ts;
		}
	}
	delete[] data;
	int count[game_unknown] = {0};
	for (int i = 0; i < get_c_files(); i++)
	{
		int id = get_id(i);
		for (int game = game_td; game < game_unknown; game++)
			count[game] += mix_database::get_name(static_cast<t_game>(game), id).empty();
	}
	int min = count[0];
	for (int game = 0; game < game_unknown; game++)
	{
		if (count[game] < min)
		{
			m_game = static_cast<t_game>(game);
			min = count[game];
		}
	}
	if (!m_data_loaded)
	{
#ifndef NO_FT_SUPPORT
		Ccrc crc;
		crc.init();
		crc.do_block(m_index, m_c_files * sizeof(t_mix_index_entry));
		const void* s = mix_cache::get_data(crc.get_crc());
		m_index_ft = new t_file_type[m_c_files];
		if (s)
			memcpy(m_index_ft, s, m_c_files * sizeof(t_file_type));
		else
		{
			for (int i = 0; i < m_c_files; i++)
			{
				Ccc_file f(false);
				f.open(get_id(i), *this);
				m_index_ft[i] = f.get_file_type();
				f.close();
			}
			mix_cache::set_data(crc.get_crc(), m_index_ft, m_c_files * sizeof(t_file_type));
		}
		for (int i = 0; i < m_c_files; i++)
		{
			int id = get_id(i);
			if (get_type(id) == ft_xcc_lmd)
			{
				Cxcc_lmd_file f;
				if (!f.open(id, *this))
				{
					if (f.is_valid())
					{
						m_game = f.get_game();
						int count = f.get_c_fnames();
						const char* r = f.get_fnames();
						while (count--)
						{
							string name = r;
							r += name.length() + 1;
							mix_database::add_name(m_game, name, "-");
						}
					}
					f.close();
				}
			}
		}
#endif
	}
	if (m_mix_expansion)
	{
		const int c_files = m_c_files;
		for (int i = 0; i < c_files; i++)
		{
			if (get_type(m_index[i].id) == ft_mix)
			{
				Cmix_file f;
				f.open(m_index[i].id, *this);				
				int new_c_files = f.get_c_files();
				t_mix_index_entry* new_index = new t_mix_index_entry[m_c_files + new_c_files];
				memcpy(new_index, m_index, m_c_files * sizeof(t_mix_index_entry));
				for (int j = 0; j < new_c_files; j++)
				{
					int id = new_index[m_c_files + j].id = f.get_id(j);
					new_index[m_c_files + j].offset = f.get_offset(id) + get_offset(m_index[i].id);
					new_index[m_c_files + j].size = f.get_size(id);
				}
				delete[] m_index;
				m_index = new_index;
				t_file_type* new_index_ft = new t_file_type[m_c_files + new_c_files];
				memcpy(new_index_ft, m_index_ft, m_c_files * sizeof(t_file_type));
				memcpy(new_index_ft + m_c_files, f.m_index_ft, new_c_files * sizeof(t_file_type));
				delete[] m_index_ft;
				m_index_ft = new_index_ft;
				m_c_files += new_c_files;
				f.close();
			}
		}
	}
    return 0;
}

void Cmix_file::close()
{
	delete[] m_index_ft;
	m_index_ft = NULL;
    delete[] m_index;
    m_index = NULL;
	Ccc_file::close();
}

string Cmix_file::get_name(int id)
{
	return mix_database::get_name(get_game(), id);
}

t_file_type Cmix_file::get_type(int id)
{
	assert(m_index_ft);
	return m_index_ft[get_index(id)];
}

int Cmix_file::get_id(t_game game, string name)
{
	name = to_upper(name);
	if (game != game_ts && game != game_ra2)
	{
		int i = 0;
		unsigned int id = 0;
		int l = name.length();
		while (i < l)
		{
			unsigned int a = 0;
			for (int j = 0; j < 4; j++)
			{
				a >>= 8;
				if (i < l)
					a += static_cast<unsigned int>(name[i]) << 24;
				i++;
			}
			id = (id << 1 | id >> 31) + a;
		}
		return id;
	}
	else
	{
		const int l = name.length();
		int a = l >> 2;
		if (l & 3)
		{
			name += static_cast<char>(l - (a << 2));
			int i = 3 - (l & 3);
			while (i--)
				name += name[a << 2];
		}
		Ccrc crc;
		crc.init();
		crc.do_block(name.c_str(), name.length());
		return crc.get_crc();
	}
}

int Cmix_file::get_index(unsigned int id) const
{
    assert(is_open());
    for (int i = 0; i < m_c_files; i++)
	{
        if (m_index[i].id == id)
            return i;
	}
    return -1;
}

void Cmix_file::clean_up()
{
    delete[] m_index_ft;
    m_index_ft = NULL;
    delete[] m_index;
    m_index = NULL;
    if (is_open())
        close();
}