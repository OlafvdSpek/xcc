// cps_file.h: interface for the Ccps_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPS_FILE_H__7EF89731_D4B2_11D3_A718_0000F81AF8CC__INCLUDED_)
#define AFX_CPS_FILE_H__7EF89731_D4B2_11D3_A718_0000F81AF8CC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "cc_structures.h"
#include "image_file.h"
#include "palet.h"

class Ccps_file: public Cimage_file<t_cps_header>
{
public:
	void decode(void*) const;
	bool is_valid() const;
	Cvirtual_image vimage() const;

	int cb_pixel() const
	{
		return 1;
	}

	int cx() const
	{
		return 320;
	}

	int cy() const
	{
		return 200;
	}

	const byte* get_image() const
	{
		return get_data() + sizeof(t_cps_header) + get_header()->palet_size;
	}

	const t_palet_entry* palet() const
	{
		return get_header()->palet_size ? reinterpret_cast<const t_palet_entry*>(get_data() + sizeof(t_cps_header)) : NULL;
	}
};

Cvirtual_binary cps_file_write(const byte* s, const t_palet_entry* palet);


#endif // !defined(AFX_CPS_FILE_H__7EF89731_D4B2_11D3_A718_0000F81AF8CC__INCLUDED_)
