// text_file.h: interface for the Ctext_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXT_FILE_H__C1E67080_DBD8_11D3_B604_0000B4936994__INCLUDED_)
#define AFX_TEXT_FILE_H__C1E67080_DBD8_11D3_B604_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_small.h"

class Ctext_file: public Ccc_file_small
{
public:
	bool is_valid() const
	{
		if (!get_size())
			return false;
		const byte* data = get_data();
		int cb_data = min(get_size(), 16 << 10);
		for (int i = 0; i < cb_data; i++)
		{
			byte c = data[i];
			if (c != 0x09 && c != 0x0d && c != 0x0a && c < 0x20)
			{
				switch (get_size())
				{
				case 351263:
					// TS: g_knoll.map
					if (i == 1919 && c == 0x05)
						break;
					else
						return false;
				default:
					return false;
				}
			}
		}
		return true;
	}
};

#endif // !defined(AFX_TEXT_FILE_H__C1E67080_DBD8_11D3_B604_0000B4936994__INCLUDED_)
