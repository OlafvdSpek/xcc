// tmp_ra_file.h: interface for the Ctmp_ra_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TMP_RA_FILE_H__3C483120_DF9D_11D3_B604_0000B4936994__INCLUDED_)
#define AFX_TMP_RA_FILE_H__3C483120_DF9D_11D3_B604_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "fname.h"
#include "image_file.h"
#include "palet.h"

class Ctmp_ra_file: public Cimage_file<t_tmp_ra_header>
{
public:
	void decode(void*) const;

	bool is_valid() const
	{
		const t_tmp_ra_header& header = *get_header();
		int size = get_size();
		return !(sizeof(t_tmp_ra_header) > size || 
			header.cx != 24 || 
			header.cy != 24 || 
			header.c_tiles > 64 ||
			header.zero1 ||
			header.size != size ||
			header.image_offset > size ||
			header.zero2);
	}

	int cb_pixel() const
	{
		return 1;
	}

	int cx() const
	{
		return 24 * get_cblocks_x();
	}

	int cy() const
	{
		return 24 * get_cblocks_y();
	}

	int get_c_tiles() const
	{
		return get_header()->c_tiles;
	}

	int get_cblocks_x() const
	{
		return get_header()->cblocks_x;
	}

	int get_cblocks_y() const
	{
		return get_header()->cblocks_y;
	}

	const byte* get_image(int i) const
	{
		return get_data() + get_header()->image_offset + 576 * get_index1()[i];
	}

	const byte* get_index1() const
	{
		return get_data() + get_header()->index1;
	}
};

int tmp_ra_file_write(const byte* s, byte* d, int cx, int cy);

#endif // !defined(AFX_TMP_RA_FILE_H__3C483120_DF9D_11D3_B604_0000B4936994__INCLUDED_)
