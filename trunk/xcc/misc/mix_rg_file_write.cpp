// mix_rg_file_write.cpp: implementation of the Cmix_rg_file_write class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mix_rg_file_write.h"

#include "cc_structures.h"
#include "mix_file.h"

void Cmix_rg_file_write::insert(string name, const Cvirtual_binary d)
{
	m_index[name] = d;
}

void Cmix_rg_file_write::clear()
{
	m_index.clear();
}

Cvirtual_binary Cmix_rg_file_write::write()
{
	typedef map<unsigned int, string> t_id_index;

	t_id_index id_index;
	{
		for (t_index::const_iterator i = m_index.begin(); i != m_index.end(); i++)
			id_index[Cmix_file::get_id(game_rg, i->first)] = i->first;
	}
	int cb_d = sizeof(t_mix_rg_header) + 8 + (sizeof(t_mix_rg_index_entry) + 2) * m_index.size();
	t_id_index::const_iterator i;
	for (i = id_index.begin(); i != id_index.end(); i++)
		cb_d += m_index.find(i->second)->first.length() + m_index.find(i->second)->second.size();
	Cvirtual_binary d;
	byte* w = d.write_start(cb_d);
	t_mix_rg_header& header = *reinterpret_cast<t_mix_rg_header*>(w);
	header.id = mix_rg_id;
	header.zero = 0;
	w += sizeof(t_mix_rg_header);
	for (i = id_index.begin(); i != id_index.end(); i++)
		w += m_index.find(i->second)->second.read(w);
	header.index_offset = w - d.data();
	*reinterpret_cast<__int32*>(w) = m_index.size();
	w += 4;
	int offset = sizeof(t_mix_rg_header);
	for (i = id_index.begin(); i != id_index.end(); i++)
	{
		t_index::const_iterator j = m_index.find(i->second);
		t_mix_rg_index_entry& e = *reinterpret_cast<t_mix_rg_index_entry*>(w);
		e.id = Cmix_file::get_id(game_rg, j->first);
		e.offset = offset;
		offset += e.size = j->second.size();
		w += sizeof(t_mix_rg_index_entry);		
	}
	header.tailer_offset = w - d.data();
	*reinterpret_cast<__int32*>(w) = m_index.size();
	w += 4;
	for (i = id_index.begin(); i != id_index.end(); i++)
	{
		t_index::const_iterator j = m_index.find(i->second);
		*w++ = j->first.length() + 1;
		strcpy(reinterpret_cast<char*>(w), j->first.c_str());
		w += j->first.length() + 1;
	}
	assert(w == d.data_end());
	return d;
}
