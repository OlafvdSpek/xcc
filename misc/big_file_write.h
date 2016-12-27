#pragma once

#include <virtual_binary.h>

class Cbig_file_write  
{
public:
	void clear();
	void insert(const string& name, const Cvirtual_binary& d);
	Cvirtual_binary write();
private:
	typedef map<string, Cvirtual_binary> t_index;

	t_index m_index;
};
