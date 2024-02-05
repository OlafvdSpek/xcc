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
#include "mix_rg_file.h"

Cmix_rg_file::Cmix_rg_file():
	Ccc_file(false)
{
}

bool Cmix_rg_file::is_valid()
{
	if (get_size() < sizeof(t_mix_rg_header))
		return false;
	t_mix_rg_header header;
	seek(0);
	if (read(&header, sizeof(t_mix_rg_header))
		|| header.id != mix_rg_id
		|| header.index_offset + 4 > header.tailer_offset
		|| header.tailer_offset + 4 > get_size()
		|| header.zero)
		return false;
	return true;
}

int Cmix_rg_file::post_open()
{
	m_index.clear();
	m_old_index.clear();
	if (!is_valid())
		return 1;
	if (get_data() && vdata().size() != get_size())
		return 0;
	t_mix_rg_header header;
	seek(0);
	int error = read(&header, sizeof(t_mix_rg_header));
	Cvirtual_binary index, tailer;
	if (!error)
	{
		index.write_start(header.tailer_offset - header.index_offset);
		seek(header.index_offset);
		error = read(index.data_edit(), index.size());
	}
	if (!error)
	{
		tailer.write_start(get_size() - header.tailer_offset);
		seek(header.tailer_offset);
		error = read(tailer.data_edit(), tailer.size());
	}
	if (!error)
	{
		int size = *reinterpret_cast<const __int32*>(index.data());
		assert(*reinterpret_cast<const __int32*>(tailer.data()) == size);
		m_old_index.reserve(size);
		const t_mix_rg_index_entry* r_index = reinterpret_cast<const t_mix_rg_index_entry*>(index.data() + 4);
		const byte* r_tailer = tailer.data() + 4;
		while (size--)
		{
			int cb_v = *r_tailer++;
			string v = reinterpret_cast<const char*>(r_tailer);
			r_tailer += cb_v;
			m_index[v] = *r_index++;
			m_old_index.push_back(v);
		}
	}
	return error;
}