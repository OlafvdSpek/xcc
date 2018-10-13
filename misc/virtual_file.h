#pragma once

#include <list>
#include <virtual_binary.h>

using namespace std;

class Cvirtual_file  
{
public:
	int save(const string& fname) const;
	int load(const string& fname);
	void clear();
	void compact();
	const byte* data() const;
	int size() const;
	Cvirtual_binary read() const;
	int read(void* d) const;
	void write(const Cvirtual_binary& d);
	void write(const void* d, int cb_d);
	Cvirtual_file();
	Cvirtual_file(const Cvirtual_binary& d);
private:
	using t_data = list<Cvirtual_binary>;
	t_data m_data;
};
