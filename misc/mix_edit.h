#pragma once

#include "cc_structures.h"
#include "file32.h"
#include "mix_file.h"

class Cmix_edit  
{
public:
	static int cb_header(int size);
	void close();
	void clear();
	int compact();
	void erase(int id);
	void erase(const string& name);
	int id(const string& name) const;
	int insert(const string& name, Cvirtual_binary d);
	int open(const string& name);
	int write_index();
private:
	using t_block_map = map<int, t_mix_index_entry*>;

	t_block_map block_map();
	int new_block(int size);

	Cfile32 m_f;
	t_game m_game;
	map<int, t_mix_index_entry> m_index;
};
