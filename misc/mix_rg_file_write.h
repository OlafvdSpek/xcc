#pragma once

#include <virtual_binary.h>

class Cmix_rg_file_write  
{
public:
	void clear();
	void insert(string name, const Cvirtual_binary d);
	Cvirtual_binary write();
private:
	using t_index = map<string, Cvirtual_binary>;

	t_index m_index;
};
