// xcc_lmd_file.h: interface for the Cxcc_lmd_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCC_LMD_FILE_H__5C6F2863_FDAB_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_XCC_LMD_FILE_H__5C6F2863_FDAB_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xcc_file_sh.h"

class Cxcc_lmd_file: public Cxcc_file_sh<t_xcc_lmd_header>
{
public:
	bool is_valid() const
	{
		return Cxcc_file_sh<t_xcc_lmd_header>::is_valid() && get_ft() == xcc_ft_lmd;
	}

	t_game get_game() const
	{
		return static_cast<t_game>(get_header()->game);
	}

	int get_c_fnames() const
	{
		return get_header()->c_fnames;
	}

	const char* get_fnames() const
	{
		return reinterpret_cast<const char*>(get_data() + sizeof(t_xcc_header) + sizeof(t_xcc_lmd_header));
	}
};

#endif // !defined(AFX_XCC_LMD_FILE_H__5C6F2863_FDAB_11D3_B605_0000B4936994__INCLUDED_)
