// st_file.h: interface for the Cst_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ST_FILE_H__2FC66021_06EE_11D4_B605_0000B4936994__INCLUDED_)
#define AFX_ST_FILE_H__2FC66021_06EE_11D4_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
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
		return reinterpret_cast<const unsigned __int16*>(get_data());
	}

	int get_offset(int i) const
	{
		return get_index()[i];
	}

	const char* get_string(int i) const
	{
		return reinterpret_cast<const char*>(get_data() + get_offset(i));
	}
};

#endif // !defined(AFX_ST_FILE_H__2FC66021_06EE_11D4_B605_0000B4936994__INCLUDED_)
