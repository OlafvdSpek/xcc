#include "stdafx.h"
#include "xcc_lmd_file_write.h"

#include "cc_structures.h"
#include "xcc_file.h"

void Cxcc_lmd_file_write::add_fname(const string& fname)
{
	m_index.push_back(to_lower_copy(fname));
}

Cvirtual_binary Cxcc_lmd_file_write::write(t_game game) const
{
	int size = sizeof(t_xcc_header) + sizeof(t_xcc_lmd_header);
	for (auto& i : m_index)
		size += i.length() + 1;
	Cvirtual_binary data;
	byte* w = data.write_start(size);
	t_xcc_header& header = *reinterpret_cast<t_xcc_header*>(w);
	strcpy(header.id, xcc_id);
	header.size = size;
	header.type = xcc_ft_lmd;
	header.version = 0;
	w += sizeof(t_xcc_header);
	t_xcc_lmd_header& lmd_header = *reinterpret_cast<t_xcc_lmd_header*>(w);
	lmd_header.c_fnames = m_index.size();
	lmd_header.game = game;
	w += sizeof(t_xcc_lmd_header);
	for (auto& i : m_index)
	{
		strcpy(reinterpret_cast<char*>(w), i.c_str());
		w += i.length() + 1;
	}
	return data;
}