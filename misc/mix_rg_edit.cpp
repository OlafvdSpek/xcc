/*
    XCC Utilities and Library
    Copyright (C) 2002  Olaf van der Spek  <olafvdspek@gmail.com>

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
#include "mix_rg_edit.h"

#include "mix_file.h"

static int copy_block(Cfile32& s, int s_p, Cfile32& d, int d_p, int size)
{
	int error = 0;
	Cvirtual_binary buffer;
	while (!error && size)
	{
		int cb_buffer = min(size, 4 << 20);
		s.seek(s_p);
		error = s.read(buffer.write_start(cb_buffer), cb_buffer);
		if (!error)
		{
			d.seek(d_p);
			error = d.write(buffer.data(), cb_buffer);
			if (!error)
			{
				s_p += cb_buffer;
				d_p += cb_buffer;
				size -= cb_buffer;
			}
		}
	}
	return error;
}

int Cmix_rg_edit::open(const string& name)
{
	int error = m_f.open_edit(name);
	if (!error)
	{		
		error = m_f.read(&m_header, sizeof(t_mix_rg_header));
		if (!error)
		{
			Cmix_rg_file f;
			error = f.open(m_f.h());
			if (!error)
			{				
				m_index = f.index();
				m_index_size = 4 + sizeof(t_mix_rg_index_entry) * m_index.size();
				m_tailer_size = 4 + 2 * m_index.size();
				for (auto& i : m_index)
					m_tailer_size += i.first.length();
			}				
		}
		if (error)
			m_f.close();
	}
	return error;
}

void Cmix_rg_edit::close()
{
	m_f.close();
}

int Cmix_rg_edit::insert(const string& name, Cvirtual_binary d)
{
	int offset = new_block(d.size());
	m_f.seek(offset);
	int error = m_f.write(d);
	if (!error)
	{
		t_mix_rg_index_entry e;
		e.id = Cmix_file::get_id(game_rg, name);
		e.offset = offset;
		e.size = d.size();
		m_index[name] = e;
	}
	return error;
}

void Cmix_rg_edit::erase(const string& name)
{
	m_index.erase(name);
}

void Cmix_rg_edit::clear()
{
	m_index.clear();
}

int Cmix_rg_edit::write_index()
{
	using t_id_index = map<unsigned int, string>;

	t_id_index id_index;
	for (auto& i : m_index)
		id_index[i.second.id] = i.first;
	int cb_index = 4 + sizeof(t_mix_rg_index_entry) * m_index.size();
	int cb_tailer = 4 + 2 * m_index.size();
	t_id_index::const_iterator i;
	for (i = id_index.begin(); i != id_index.end(); i++)
		cb_tailer += m_index.find(i->second)->first.length();
	Cvirtual_binary d;
	byte* w = d.write_start(cb_index + cb_tailer);
	*reinterpret_cast<__int32*>(w) = m_index.size();
	w += 4;
	for (i = id_index.begin(); i != id_index.end(); i++)
	{
		memcpy(w, &m_index.find(i->second)->second, sizeof(t_mix_rg_index_entry));
		w += sizeof(t_mix_rg_index_entry);
	}
	*reinterpret_cast<__int32*>(w) = m_index.size();
	w += 4;
	for (i = id_index.begin(); i != id_index.end(); i++)
	{
		t_index::const_iterator j = m_index.find(i->second);		
		*w++ = j->first.length() + 1;
		strcpy(reinterpret_cast<char*>(w), j->first.c_str());
		w += j->first.length() + 1;
	}
	m_index_size = m_tailer_size = 0;
	int offset = new_block(INT_MAX); 
	m_f.seek(offset);
	int error = m_f.write(d);
	if (!error)
	{
		m_f.set_eof();
		m_header.index_offset = offset;
		m_header.tailer_offset = offset + cb_index;
		m_index_size = cb_index;
		m_tailer_size = cb_tailer;
		m_f.seek(0);
		error = m_f.write(&m_header, sizeof(t_mix_rg_header));
	}
	return error;
}

int Cmix_rg_edit::compact()
{
	t_block_map block_map = Cmix_rg_edit::block_map();
	int error = 0;
	int offset = sizeof(t_mix_rg_header);
	for (auto& i : block_map)
	{
		if (1 && i.second->offset != offset)
		{
			assert(i.second->offset > offset);
			error = copy_block(m_f, i.second->offset, m_f, offset, i.second->size);
			if (error)
				break;
			i.second->offset = offset;
		}
		offset += i.second->size;
	}
	error = error ? write_index(), error : write_index();
	return error;
}

Cmix_rg_edit::t_block_map Cmix_rg_edit::block_map()
{
	t_block_map block_map;
	for (auto& i : m_index)
		block_map[i.second.offset] = &i.second;
	return block_map;
}

int Cmix_rg_edit::new_block(int size)
{
	t_block_map block_map = Cmix_rg_edit::block_map();
	t_mix_rg_index_entry index_block, tailer_block;
	if (m_index_size)
	{	
		index_block.offset = m_header.index_offset;
		index_block.size = m_index_size;
		block_map[m_header.index_offset] = &index_block;
	}
	if (m_tailer_size)
	{
		tailer_block.offset = m_header.tailer_offset;
		tailer_block.size = m_tailer_size;
		block_map[m_header.tailer_offset] = &tailer_block;
	}
	int r = sizeof(t_mix_rg_header);
	for (auto& i : block_map)
	{
		if (size != INT_MAX && r + size <= i.first)
			return r;
		r = i.second->offset + i.second->size;
	}
	return r;
}
