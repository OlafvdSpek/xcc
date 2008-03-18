#include "stdafx.h"
#include "mix_edit.h"

#include "id_log.h"
#include "xcc_lmd_file_write.h"

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

int Cmix_edit::open(const string& name)
{
	int error = m_f.open_edit(name);
	if (!error)
	{		
		Cmix_file f;
		error = f.open(m_f.h());
		if (!error)
		{
			m_game = f.get_game();
			m_index.clear();
			for (int i = 0; i < f.get_c_files(); i++)
				m_index[f.get_id(i)] = f.index()[i];
		}				
		if (error)
			m_f.close();
	}
	return error;
}

void Cmix_edit::close()
{
	m_f.close();
}

int Cmix_edit::cb_header(int size)
{
	return 4 + sizeof(t_mix_header) + sizeof(t_mix_index_entry) * size;
}

int Cmix_edit::id(const string& name) const
{
	return Cmix_file::get_id(m_game, name);
}

int Cmix_edit::insert(const string& name, Cvirtual_binary d)
{
	mix_database::add_name(m_game, name, "-");
	int offset = new_block(d.size());
	m_f.seek(offset);
	int error = m_f.write(d.data(), d.size());
	if (!error)
	{
		t_mix_index_entry e;
		e.id = id(name);
		e.offset = offset;
		e.size = d.size();
		m_index[e.id] = e;
	}
	return error;
}

void Cmix_edit::erase(int id)
{
	m_index.erase(id);
}

void Cmix_edit::erase(const string& name)
{
	erase(id(name));
}

void Cmix_edit::clear()
{
	m_index.clear();
}

int Cmix_edit::write_index()
{
	{
		Cxcc_lmd_file_write lmd_fw;
		for (t_index::const_iterator i = m_index.begin(); i != m_index.end(); i++)
		{
			string name = mix_database::get_name(m_game, i->second.id);
			if (!name.empty())
				lmd_fw.add_fname(name);
		}
		insert("local mix database.dat", lmd_fw.write(m_game));
	}
	Cvirtual_binary d;
	byte* w = d.write_start(cb_header(m_index.size()));
	*reinterpret_cast<__int32*>(w) = 0;
	w += 4;
	t_mix_header& header = *reinterpret_cast<t_mix_header*>(w);
	header.c_files = m_index.size();
	w += sizeof(t_mix_header);
	{
		t_block_map block_map = Cmix_edit::block_map();
		for (t_block_map::const_iterator i = block_map.begin(); i != block_map.end(); i++)
		{
			if (i->second->offset < d.size())
			{
				int offset = new_block(i->second->size);
				int error = copy_block(m_f, i->second->offset, m_f, offset, i->second->size);
				if (error)
					return error;
				i->second->offset = offset;
			}
		}
	}
	int total_size = d.size();
	t_mix_index_entry* index = reinterpret_cast<t_mix_index_entry*>(w);
	for (t_index::const_iterator i = m_index.begin(); i != m_index.end(); i++)
	{
		index->id = i->first;
		index->offset = i->second.offset - d.size();
		index->size = i->second.size;
		index++;
		total_size = max(total_size, i->second.offset + i->second.size);
	}	
	m_f.seek(total_size);
	m_f.set_eof();
	header.size = m_f.get_size() - d.size();
	m_f.seek(0);
	return m_f.write(d.data(), d.size());
}

int Cmix_edit::compact()
{
	t_block_map block_map = Cmix_edit::block_map();
	int error = 0;
	int offset = cb_header(m_index.size());
	for (t_block_map::const_iterator i = block_map.begin(); i != block_map.end(); i++)
	{
		if (i->second->offset != offset)
		{
			assert(i->second->offset > offset);
			error = copy_block(m_f, i->second->offset, m_f, offset, i->second->size);
			if (error)
				break;
			i->second->offset = offset;
		}
		offset += i->second->size;
	}
	error = error ? write_index(), error : write_index();
	return error;
}

Cmix_edit::t_block_map Cmix_edit::block_map()
{
	t_block_map block_map;
	for (t_index::iterator i = m_index.begin(); i != m_index.end(); i++)
		block_map[i->second.offset] = &i->second;
	return block_map;
}

int Cmix_edit::new_block(int size)
{
	t_block_map block_map = Cmix_edit::block_map();
	int r = cb_header(m_index.size() + 4);
	for (t_block_map::const_iterator i = block_map.begin(); i != block_map.end(); i++)
	{
		if (r + size <= i->first)
			return r;
		r = i->second->offset + i->second->size;
	}
	return r;
}