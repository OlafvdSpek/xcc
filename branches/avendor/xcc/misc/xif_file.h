// xif_file.h: interface for the Cxif_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XIF_FILE_H__93731940_3FA3_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XIF_FILE_H__93731940_3FA3_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "xif_key.h"

class Cxif_file: public Ccc_file_sh<t_xif_header>  
{
public:
	bool is_valid() const
	{
 		int size = get_size();
		const t_xif_header& header = *get_header();
		return !(sizeof(t_xif_header) > size ||
			header.id != file_id ||
			header.version != file_version_old && header.version != file_version_new);
	}
};

#endif // !defined(AFX_XIF_FILE_H__93731940_3FA3_11D4_B606_0000B4936994__INCLUDED_)
