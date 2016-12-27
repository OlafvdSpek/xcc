#pragma once

#include "cc_file_small.h"

class Cst_file: public Ccc_file_small
{
public:
	ostream& extract_as_text(ostream&) const;
	bool is_valid() const;

	int get_c_strings() const
	{
		return get_offset(0) >> 1;
	}

	const unsigned __int16* get_index() const
	{
		return reinterpret_cast<const unsigned __int16*>(data());
	}

	int get_offset(int i) const
	{
		return get_index()[i];
	}

	const char* get_string(int i) const
	{
		return reinterpret_cast<const char*>(data() + get_offset(i));
	}
};
