#pragma once

#include <string>
#include "assert.h"
#include "vartypes.h"
#include "virtual_binary.h"

using namespace std;

class Cvirtual_tfile  
{
private:
	Cvirtual_binary m_data;
	bool force_upper_case;
	int pos;

	const char* data() const
	{
		return reinterpret_cast<const char*>(m_data.data());
	}

	int size() const
	{
		return m_data.size();
	}
public:
	string read_line();
	string read_line(bool remove_ws);
	void write(const string& s);
	void write_line(const string& s);
	void release_memory();
	void load_data(const Cvirtual_binary s);
	void save_data(byte*& _data, dword& _size) const;

	bool eof() const
	{
		return pos >= size();
	}

	void set_force_upper_case(bool v)
	{
		force_upper_case = v;
	}

	void seek(dword ipos)
	{
		pos = ipos;
	}
};
