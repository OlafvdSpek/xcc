// xif_value.cpp: implementation of the Cxif_value class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <minmax.h>
#include <zlib.h>
#include "xif_value.h"

#include "string_conversion.h"

static void dump_spaces(ostream& os, int count)
{
	while (count--)
		os << ' ';
}

void Cxif_value::dump(ostream& os, int depth) const
{
	switch (get_type())
	{
	case vt_binary:
		{			
			int count = min(get_size(), 32);
			const byte* r = get_data();
			while (count--)
				os << nh(2, *r++) + ' ';
			if (get_size() > 32)
				os << "...";
			os << endl;
			break;
		}
	case vt_bin32:
		os << nh(8, get_int()) << endl;
		break;
	case vt_int32:
		os << get_int() << endl;
		break;
	case vt_string:
		{
			string s = get_string();
			if (s.find('\n') == string::npos)
				os << s << endl;
			else
				os << s.substr(0, s.find('\n')) << " ..." << endl;
			break;
		}
	}
}