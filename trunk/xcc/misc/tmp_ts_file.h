// tmp_ts_file.h: interface for the Ctmp_ts_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TMP_TS_FILE_H__2ADB87E0_2208_11D4_B605_0000B4936994__INCLUDED_)
#define AFX_TMP_TS_FILE_H__2ADB87E0_2208_11D4_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <assert.h>
#include <cc_file_sh.h>
#include <cc_structures.h>
#include "fname.h"
#include "palet.h"

class Ctmp_ts_file: public Ccc_file_sh<t_tmp_ts_header>
{
public:
	void draw(byte* d) const;
	int extract_as_pcx(const string& name, const t_palet _palet) const;
	void get_rect(int& x, int& y, int& cx, int& cy) const;

	bool is_valid() const
	{
		const t_tmp_ts_header& header = *get_header();
		int size = get_size();
		if (sizeof(t_tmp_ts_header) > size || 
			!header.cblocks_x || !header.cblocks_y ||
			header.cx != 48 && header.cx != 60 ||
			2 * header.cy != header.cx ||
			sizeof(t_tmp_ts_header) + 4 * get_c_tiles() > size)
			return false;
		for (int i = 0; i < min(get_c_tiles(), 64); i++)
		{
			if (get_index()[i])
			{
				const t_tmp_image_header& image_header = *get_image_header(i);
			}
		}
		return true;
	}

	int get_c_tiles() const
	{
		return get_cblocks_x() * get_cblocks_y();
	}

	int get_cblocks_x() const
	{
		return get_header()->cblocks_x;
	}

	int get_cblocks_y() const
	{
		return get_header()->cblocks_y;
	}

	const t_tmp_image_header* get_image_header(int i) const
	{
		return reinterpret_cast<const t_tmp_image_header*>(get_data() + get_index()[i]);
	}

	int get_x(int i) const
	{
		return get_image_header(i)->x;
	}

	int get_y(int i) const
	{
		return get_image_header(i)->y;
	}

	int get_cx() const
	{
		return get_header()->cx;
	}

	int get_cy() const
	{
		return get_header()->cy;
	}

	int get_x_extra(int i) const
	{
		return get_image_header(i)->x_extra;
	}
	
	int get_height() const
	{
		int height = 0;
		for (int i = 0; i < get_c_tiles(); i++)
		{
			if (get_index()[i])
			{
				if (get_height(i) > height)
					height = get_height(i);
			}
		}
		return height;
	}

	int get_height(int i) const
	{
		return get_image_header(i)->height;
	}

	/*
	int get_ramp_type(int i) const
	{
		return get_image_header(i)->ramp_type;
	}

	int get_terrain_type(int i) const
	{
		return get_image_header(i)->terrain_type;
	}
	*/

	int get_y_extra(int i) const
	{
		return get_image_header(i)->y_extra;
	}

	int get_cx_extra(int i) const
	{
		return get_image_header(i)->cx_extra;
	}

	int get_cy_extra(int i) const
	{
		return get_image_header(i)->cy_extra;
	}

	bool has_extra_graphics(int i) const
	{
		return get_image_header(i)->has_extra_data;
	}

	int get_cb_diamond() const
	{
		return get_cx() * get_cy() >> 1;
	}

	int get_cb_extra_data(int i) const
	{
		return get_cx_extra(i) * get_cy_extra(i);
	}

	const byte* get_image(int i) const
	{
		return reinterpret_cast<const byte*>(get_image_header(i) + 1);
	}

	const byte* get_z_image(int i) const
	{
		int a = get_index()[i] + get_image_header(i)->z_ofs;
		int b = get_image(i) + get_cb_diamond() - get_data();
		assert(a == b);
		return get_data() + get_index()[i] + get_image_header(i)->z_ofs;
	}
	
	const byte* get_extra_data(int i) const
	{
		return get_data() + get_index()[i] + get_image_header(i)->extra_ofs;
	}

	const byte* get_extra_z_data(int i) const
	{
		return get_data() + get_index()[i] + get_image_header(i)->extra_z_ofs;
	}

	const int* get_index() const
	{
		return reinterpret_cast<const int*>(get_data() + sizeof(t_tmp_ts_header));
	}
};

int decode_tile(const byte* s, byte* d, int cx_d);
int encode_tile(const byte* s, byte* d, int cx_s);
int tmp_ts_file_write(const byte* s, byte* d, int cx, int cy);

#endif // !defined(AFX_TMP_TS_FILE_H__2ADB87E0_2208_11D4_B605_0000B4936994__INCLUDED_)
