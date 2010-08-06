#pragma once

#include "cc_structures.h"
#include <virtual_binary.h>
#include "xcc_lmd_file_write.h"

class Cmix_file_write  
{
public:
	void add_file(int id, const Cvirtual_binary d);
	void add_file(string name, const Cvirtual_binary d);
	void clear();
	Cvirtual_binary write();
	Cmix_file_write(t_game game);
private:
	typedef map<int, Cvirtual_binary> t_index;

	int write_start();
	int write(byte* d) const;

	t_game m_game;
	t_index m_index;
	Cxcc_lmd_file_write m_lmd_fw;
};
