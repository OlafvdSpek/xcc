// cps_file.h: interface for the Ccps_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPS_FILE_H__7EF89731_D4B2_11D3_A718_0000F81AF8CC__INCLUDED_)
#define AFX_CPS_FILE_H__7EF89731_D4B2_11D3_A718_0000F81AF8CC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <cc_file_sh.h>
#include <cc_structures.h>
#include <palet.h>
#include "fname.h"

class Ccps_file: public Ccc_file_sh<t_cps_header>
{
public:
	int extract_as_pcx(const string& name, const t_palet _palet) const;

	bool is_valid() const
	{
		const t_cps_header& header = *get_header();
		int size = get_size();
		if (sizeof(t_cps_header) > size ||
			header.image_size != 320 * 200 ||				
			header.zero)
			return false;
		switch (header.unknown)
		{
		/*
		case 3:
			return header.size == size;
		*/
		case 4:
			return 2 + header.size == size;
		default:
			return false;
		}
	}

	const byte* get_image() const
	{
		return get_data() + sizeof(t_cps_header) + get_header()->palet_size;
	}

    const t_palet_entry* get_palet() const
    {
        return reinterpret_cast<const t_palet_entry*>(get_data() + sizeof(t_cps_header));
    }

	bool has_palet() const
	{
		return get_header()->palet_size;
	}
};

int cps_file_write(const byte* s, byte* d, const t_palet_entry* palet);


#endif // !defined(AFX_CPS_FILE_H__7EF89731_D4B2_11D3_A718_0000F81AF8CC__INCLUDED_)
