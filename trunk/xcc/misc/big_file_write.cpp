#include "stdafx.h"
#include "big_file_write.h"

#include "cc_structures.h"

void Cbig_file_write::insert(const string& name, const Cvirtual_binary& d)
{
	m_index[name] = d;
}

void Cbig_file_write::clear()
{
	m_index.clear();
}

Cvirtual_binary Cbig_file_write::write()
{
	int cb_header = sizeof(t_big_header);
	int cb_d = sizeof(t_big_header);
	BOOST_FOREACH(auto& i, m_index)
	{
		cb_header += sizeof(t_big_index_entry) + i.first.length() + 1;
		cb_d += sizeof(t_big_index_entry) + i.first.length() + 1 + i.second.size();
	}
	Cvirtual_binary d;
	byte* w = d.write_start(cb_d);
	t_big_header& header = *reinterpret_cast<t_big_header*>(w);
	header.id = big_id;
	header.size = d.size();
	header.mc_files = reverse(m_index.size());
	header.mcb_header = reverse(cb_header);
	byte* w2 = w + cb_header;
	w += sizeof(t_big_header);
	BOOST_FOREACH(auto& i, m_index)
	{
		t_big_index_entry& e = *reinterpret_cast<t_big_index_entry*>(w);
		e.offset = reverse(w2 - d.data());
		e.size = reverse(i.second.size());
		w += sizeof(t_big_index_entry);
		memcpy(w, i.first.c_str(), i.first.length() + 1);
		w += i.first.length() + 1;
		w2 += i.second.read(w2);
	}
	assert(w2 == d.data_end());
	return d;
}
