#pragma once

#include "big_file.h"
#include "cc_structures.h"
#include "file32.h"

class Cbig_edit  
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
	typedef map<int, t_big_index_entry*> t_block_map;
	typedef Cbig_file::t_index t_index;

	t_block_map block_map();
	int cb_header() const;
	int new_block(int size);

	Cfile32 m_f;
	t_big_header m_header;
	t_index m_index;
};
