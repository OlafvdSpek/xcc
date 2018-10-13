#pragma once

#include "cc_structures.h"
#include "file32.h"
#include "mix_rg_file.h"

class Cmix_rg_edit  
{
public:
	void close();
	void clear();
	int compact();
	void erase(const string& name);
	int insert(const string& name, Cvirtual_binary d);
	int open(const string& name);
	int write_index();
private:
	using t_block_map = map<int, t_mix_rg_index_entry*>;
	using t_index = Cmix_rg_file::t_index;

	t_block_map block_map();

	int new_block(int size);

	Cfile32 m_f;
	t_mix_rg_header m_header;
	t_index m_index;
	int m_index_size;
	int m_tailer_size;
};
