#include "stdafx.h"
#include "mix_file_write.h"

#include "mix_file.h"
#include "string_conversion.h"

Cmix_file_write::Cmix_file_write(t_game game)
{
	m_game = game;
}

void Cmix_file_write::add_file(int id, const Cvirtual_binary d)
{
	m_index[id] = d;
}

void Cmix_file_write::add_file(string name, const Cvirtual_binary d)
{
	add_file(Cmix_file::get_id(m_game, name), d);
	m_lmd_fw.add_fname(name);
}

void Cmix_file_write::clear()
{
	m_index.clear();
}

int Cmix_file_write::write_start()
{
	add_file("local mix database.dat", m_lmd_fw.write(m_game));
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
