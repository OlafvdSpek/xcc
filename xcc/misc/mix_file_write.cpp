// mix_file_write.cpp: implementation of the Cmix_file_write class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mix_file.h"
#include "mix_file_write.h"
#include "string_conversion.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cmix_file_write::~Cmix_file_write()
{
	for (t_index::iterator i = m_index.begin(); i != m_index.end(); i++)
		delete[] i->second.d;
}

void Cmix_file_write::add_file(int id, const byte* d, int cb_d)
{
	t_index::iterator i = m_index.find(id);
	if (i != m_index.end())
	{
		delete[] i->second.d;
		m_index.erase(i);
	}
	t_index_entry e;
	e.d = new byte[cb_d];
	e.cb_d = cb_d;
	memcpy(e.d, d, cb_d);
	m_index[id] = e;
}

void Cmix_file_write::add_file(string name, const byte* d, int cb_d)
{
	add_file(Cmix_file::get_id(game_ts, name), d, cb_d);
	m_lmd_fw.add_fname(name);
}

int Cmix_file_write::write_start()
{
	byte* lmd_d;
	int cb_lmd_d = m_lmd_fw.write(lmd_d, game_ts);
	add_file("local mix database.dat", lmd_d, cb_lmd_d);
	delete[] lmd_d;
	int r = 4 + sizeof(t_mix_header) + m_index.size() * sizeof(t_mix_index_entry);
	for (t_index::const_iterator i = m_index.begin(); i != m_index.end(); i++)
		r += i->second.cb_d;
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
		index->size = i->second.cb_d;
		index++;
		memcpy(w, i->second.d, i->second.cb_d);
		w += i->second.cb_d;
	}
	header.size = w - body_start;
	return w - d;
}