// bin_file.h: interface for the Cbin_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIN_FILE_H__307FE925_D574_11D3_A718_0000F81AF8CC__INCLUDED_)
#define AFX_BIN_FILE_H__307FE925_D574_11D3_A718_0000F81AF8CC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <cc_file_small.h>

class Cbin_file: public Ccc_file_small  
{
public:
	bool is_valid() const
	{
		if (get_size() != 8192)
			return false;
		const byte* p = get_data();
		for (int i = 0; i < 64 * 64; i++)
		{
			int v = *p++;
			int w = *p++;
			if (v > 0xd7 && v != 0xff || w > 64)
				return false;
		}
		return true;
	}
};

#endif // !defined(AFX_BIN_FILE_H__307FE925_D574_11D3_A718_0000F81AF8CC__INCLUDED_)
