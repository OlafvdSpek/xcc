// shp_ra_file.h: interface for the Cshp_ra_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHP_RA_FILE_H__F496E440_DF9F_11D3_B604_0000B4936994__INCLUDED_)
#define AFX_SHP_RA_FILE_H__F496E440_DF9F_11D3_B604_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cc_file_sh.h>
#include <cc_structures.h>

class Cshp_ra_file: public Ccc_file_sh<t_shp_header>
{
public:
	bool is_valid() const
	{
		const t_shp_header& header = *get_header();
		int size = get_size();
		if (sizeof(t_shp_header) > size || header.c_images > 1024 || sizeof(t_shp_header) + get_cb_index() > size)
			return false;
		int c_images = get_c_images();
		return !(get_offset(c_images) != size || get_offset(c_images + 1));
	}

	int get_c_images() const
	{
		return get_header()->c_images;
	}

	int get_cx() const
	{
		return get_header()->cx;
	}

	int get_cy() const
	{
		return get_header()->cy;
	}

    int get_cb_index() const
    {
        return 8 * (get_header()->c_images + 2);
    }

    int get_format(int i) const
	{
        return static_cast<unsigned int>(get_index()[i << 1]) >> 28;
	}

	const byte* get_image(int i) const
	{
		return get_data() + get_offset(i);
	}

	const int* get_index() const
    {
        return reinterpret_cast<const int*>(get_data() + sizeof(t_shp_header));
    }

    int get_offset(int i) const
    {
        return get_index()[i << 1] & shp_o_mask;
    }
};

#endif // !defined(AFX_SHP_RA_FILE_H__F496E440_DF9F_11D3_B604_0000B4936994__INCLUDED_)
