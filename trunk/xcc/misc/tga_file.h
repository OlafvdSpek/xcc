// tga_file.h: interface for the Ctga_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TGA_FILE_H__526D089F_903E_4043_9FA3_B271662E92AC__INCLUDED_)
#define AFX_TGA_FILE_H__526D089F_903E_4043_9FA3_B271662E92AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "virtual_image.h"

class Ctga_file: public Ccc_file_sh<t_tga_header>
{
public:
	int decode(Cvirtual_image& d) const;
	bool is_valid() const;

	int cx() const
	{
		return get_header()->cx;
	}

	int cy() const
	{
		return get_header()->cy;
	}

	int cb_pixel() const
	{
		return get_header()->cb_pixel >> 3;
	}

	const byte* image() const
	{
		return get_data() + sizeof(t_tga_header) + get_header()->id_size;
	}
};

Cvirtual_file tga_file_write(const byte* image, int cx, int cy, int cb_pixel);
Cvirtual_file tga_file_write(const byte* image, int cx, int cy, const t_palet_entry* palet);

#endif // !defined(AFX_TGA_FILE_H__526D089F_903E_4043_9FA3_B271662E92AC__INCLUDED_)
