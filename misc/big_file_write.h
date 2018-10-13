#pragma once

#include <virtual_binary.h>

class Cbig_file_write  
{
public:
	void clear();
	void insert(const string& name, const Cvirtual_binary& d);
	Cvirtual_binary write();
private:
	map<string, Cvirtual_binary> m_index;
};
