#include "stdafx.h"
#include "big_edit.h"

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

int Cbig_edit::open(const string& name)
{
	int error = m_f.open_edit(name);
	if (!error)
	{		
		Cbig_file f;
		error = f.open(m_f.h());
		if (!error)
			m_index = f.index();
		if (error)
			m_f.close();
	}
	return error;
}

void Cbig_edit::close()
{
	m_f.close();
}

int Cbig_edit::insert(const string& name, Cvirtual_binary d)
{
	int offset = new_block(d.size());
	m_f.seek(offset);
	int error = m_f.write(d);
	if (!error)
	{
		t_big_index_entry& e = m_index[name];
		e.offset = offset;
		e.size = d.size();
	}
	return error;
}

void Cbig_edit::erase(const string& name)
{
	m_index.erase(name);
}

void Cbig_edit::clear()
{
	m_index.clear();
}

int Cbig_edit::cb_header() const
{
	int v = sizeof(t_big_header);
	for (auto& i : m_index)
		v += sizeof(t_big_index_entry) + i.first.length() + 1;
	return v;
}

int Cbig_edit::write_index()
{
	Cvirtual_binary d;
	byte* w = d.write_start(cb_header());
	t_big_header& header = *reinterpret_cast<t_big_header*>(w);
	header.id = big_id;
	header.mc_files = reverse(m_index.size());
	header.mcb_header = reverse(d.size());
	w += sizeof(t_big_header);
	{
		t_block_map block_map = Cbig_edit::block_map();
		for (auto& i : block_map)
		{
			if (i.second->offset < d.size())
			{
				int offset = new_block(i.second->size);
				int error = copy_block(m_f, i.second->offset, m_f, offset, i.second->size);
				if (error)
					return error;
				i.second->offset = offset;
			}
		}
	}
	int total_size = d.size();
	for (auto& i : m_index)
	{
		t_big_index_entry& e = *reinterpret_cast<t_big_index_entry*>(w);
		e = i.second;
		e.offset = reverse(e.offset);
		e.size = reverse(e.size);
		w += sizeof(t_big_index_entry);
		memcpy(w, i.first.c_str(), i.first.length() + 1);
		w += i.first.length() + 1;
		total_size = max(total_size, i.second.offset + i.second.size);
	}	
	assert(w == d.data_end());
	m_f.seek(total_size);
	m_f.set_eof();
	header.size = m_f.size();
	m_f.seek(0);
	return m_f.write(d);
}

int Cbig_edit::compact()
{
	t_block_map block_map = Cbig_edit::block_map();
	int error = 0;
	int offset = cb_header();
	for (auto& i : block_map)
	{
		if (i.second->offset != offset)
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

Cbig_edit::t_block_map Cbig_edit::block_map()
{
	t_block_map block_map;
	for (auto& i : m_index)
		block_map[i.second.offset] = &i.second;
	return block_map;
}

int Cbig_edit::new_block(int size)
{
	t_block_map block_map = Cbig_edit::block_map();
	int r = cb_header() + 0x1ff & ~0x1ff;
	for (auto& i : block_map)
	{
		if (r + size <= i.first)
			return r;
		r = i.second->offset + i.second->size;
	}
	return r;
}