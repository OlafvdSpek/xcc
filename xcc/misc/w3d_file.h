// w3d_file.h: interface for the Cw3d_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_W3D_FILE_H__9BF3E0A1_32BC_11D6_B861_0000B4936994__INCLUDED_)
#define AFX_W3D_FILE_H__9BF3E0A1_32BC_11D6_B861_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_sh.h"
#include "cc_structures.h"

class Cw3d_file: public Ccc_file_sh<t_w3d_header>
{
public:
	bool is_valid() const
	{
		const t_w3d_header& header = *get_header();
		return get_size() >= sizeof(t_w3d_header) && sizeof(t_w3d_header) + header.size() <= get_size() && header.m_size & 0x80000000 && !(header.size() & ~0xfffff);
	}
};

#endif // !defined(AFX_W3D_FILE_H__9BF3E0A1_32BC_11D6_B861_0000B4936994__INCLUDED_)
