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
		if (get_size() < sizeof(t_w3d_header))
			return false;
		const byte* r = get_data();
		const byte* r_end = get_data() + get_vdata().size();
		while (r < r_end)
		{
			if (r_end - r < sizeof(t_w3d_header))
				return true;
			const t_w3d_header& header = *reinterpret_cast<const t_w3d_header*>(r);
			if (header.size() > (header.container() ? 16 << 20 : 1 << 20))
				return false;
			if (sizeof(t_w3d_header) + header.size() > get_size())
				return false;
			r += sizeof(t_w3d_header);
			if (!header.container())
				r += header.size();
		}
		return true;
	}
};

#endif // !defined(AFX_W3D_FILE_H__9BF3E0A1_32BC_11D6_B861_0000B4936994__INCLUDED_)
