// xcc_file.h: interface for the Cxcc_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCC_FILE_H__5C6F2860_FDAB_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_XCC_FILE_H__5C6F2860_FDAB_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cc_file_sh.h>
#include <cc_structures.h>

enum t_xcc_ft
{
	xcc_ft_lmd, xcc_ft_xif, xcc_ft_unknown
};

const char* xcc_ft_name[];

class Cxcc_file: public Ccc_file_sh<t_xcc_header>
{
public:
	bool is_valid() const
	{
		const t_xcc_header& header = *get_header();
		int size = get_size();
		return !(sizeof(t_xcc_header) > size || 
			strcmp(header.id, xcc_id) ||
			header.size != size ||
			header.version);
	}

	t_xcc_ft get_ft() const
	{
		return static_cast<t_xcc_ft>(get_header()->type);
	}
};

#endif // !defined(AFX_XCC_FILE_H__5C6F2860_FDAB_11D3_B605_0000B4936994__INCLUDED_)
