#pragma once

#include <vartypes.h>
#include <virtual_binary.h>

class Cvirtual_tfile
{
private:
	Cvirtual_binary m_data;
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
	void load_data(const Cvirtual_binary s);

	bool eof() const
	{
		return pos >= size();
	}

	void seek(int ipos)
	{
		pos = ipos;
	}
};
