// mix_file_write.cpp: implementation of the Cmix_file_write class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mix_file.h"
#include "mix_file_write.h"
#include "string_conversion.h"

void Cmix_file_write::add_file(int id, const Cvirtual_binary d)
{
	m_index[id] = d;
}

void Cmix_file_write::add_file(string name, const Cvirtual_binary d)
{
	add_file(Cmix_file::get_id(game_ts, name), d);
	m_lmd_fw.add_fname(name);
}

int Cmix_file_write::write_start()
{
	byte* lmd_d;
	int cb_lmd_d = m_lmd_fw.write(lmd_d, game_ts);
	add_file("local mix database.dat", Cvirtual_binary(lmd_d, cb_lmd_d));
	delete[] lmd_d;
	int r = 4 + sizeof(t_mix_header) + m_index.size() * sizeof(t_mix_index_entry);
	for (t_index::const_iterator i = m_index.begin(); i != m_index.end(); i++)
		r += i->second.size();
	return r;
}

int Cmix_file_write::write(byte* d) const
{
	byte* w = d;
	*reinterpret_cast<__int32*>(w) = 0;
	w += 4;
	t_mix_header& header = *reinterpret_cast<t_mix_header*>(w);
	header.c_files = m_index.size();
	w += sizeof(t_mix_header);
	t_mix_index_entry* index = reinterpret_cast<t_mix_index_entry*>(w);
	w += m_index.size() * sizeof(t_mix_index_entry);
	byte* body_start = w;
	for (t_index::const_iterator i = m_index.begin(); i != m_index.end(); i++)
	{
		index->id = i->first;
		index->offset = w - body_start;
		index->size = i->second.size();
		index++;
		w += i->second.read(w);
	}
	header.size = w - body_start;
	return w - d;
}

Cvirtual_binary Cmix_file_write::write()
{
	Cvirtual_binary d;
	write(d.write_start(write_start()));
	return d;
}
