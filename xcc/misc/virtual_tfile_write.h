#pragma once

#include <strstream>

class Cvirtual_tfile_write  
{
public:
	Cvirtual_binary save();
	void write(const string& s);
	void write_line(const string& s);
private:
	ostrstream m_v;
};
