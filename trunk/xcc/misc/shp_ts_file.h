// shp_file_ts.h: interface for the Cshp_file_ts class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHP_TS_FILE_H__26D17BE0_F135_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_SHP_TS_FILE_H__26D17BE0_F135_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_structures.h"
#include "fname.h"
#include "palet.h"
#include "video_file.h"
#include "virtual_file.h"
#include "virtual_image.h"

class Cshp_ts_file: public Cvideo_file<t_shp_ts_header>  
{
public:
	int extract_as_pcx(Cvirtual_image& d, const t_palet _palet, bool combine_shadows) const;
	int extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet palet, bool combine_shadows = false) const;
	int extract_as_pcx_single(Cvirtual_image& d, const t_palet _palet, bool combine_shadows = false) const;
	int extract_as_pcx_single(const Cfname& name, t_file_type ft, const t_palet palet, bool combine_shadows = false) const;

	bool is_valid() const
	{
		const t_shp_ts_header& header = *get_header();
		int size = get_size();
		if (sizeof(t_shp_ts_header) > size || 
			header.zero ||
			header.c_images < 1 || header.c_images > 10000 || 
			sizeof(t_shp_ts_header) + get_cb_index() > size)
			return false;
		for (int i = 0; i < min(get_c_images(), 1000); i++)
		{
			const t_shp_ts_image_header& image_header = *get_image_header(i);
			if (!image_header.cx && !image_header.cy && !image_header.offset)
				continue;
			if (!image_header.cx || image_header.x + image_header.cx > header.cx ||
				!image_header.cy || image_header.y + image_header.cy > header.cy ||
				image_header.zero ||
				image_header.offset < sizeof(t_shp_ts_header) + get_cb_index())
				return false;
			if (is_compressed(i))
			{
				if (image_header.offset > size)
					return false;
			}
			else
			{
				if (image_header.offset + image_header.cx * image_header.cy > size)
					return false;
			}
		}
		return true;
	}

	int cf() const
	{
		return get_header()->c_images;
	}

	int cx() const
	{
		return get_header()->cx;
	}

	int cy() const
	{
		return get_header()->cy;
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

	int get_x(int i) const
	{
		return get_image_header(i)->x;
	}

	int get_y(int i) const
	{
		return get_image_header(i)->y;
	}

	int get_cx(int i) const
	{
		return get_image_header(i)->cx;
	}

	int get_cy(int i) const
	{
		return get_image_header(i)->cy;
	}

    int get_cb_index() const
    {
        return sizeof(t_shp_ts_image_header) * get_c_images();
    }

	bool is_compressed(int i) const
	{
		return get_image_header(i)->compression & 2;
	}

	const t_shp_ts_image_header* get_image_header(int i) const
	{
		return reinterpret_cast<const t_shp_ts_image_header*>(get_data() + sizeof(t_shp_ts_header) + sizeof(t_shp_ts_image_header) * i);
	}

	int get_offset(int i) const
	{
		return get_image_header(i)->offset;
	}

	const byte* get_image(int i) const
	{
		return get_data() + get_offset(i);
	}

	static int get_max_size(int cx, int cy, int c_images)
	{
		return sizeof(t_shp_ts_header) + (sizeof(t_shp_ts_image_header) + (2 * (cx + 1) * cy + 7 & ~7)) * c_images;
	}
};

int shp_decode4_size(const byte* s);
Cvirtual_binary shp_decode4(const byte* s, int cb_d);
int shp_encode4(const Cshp_ts_file& f, byte* d);
void shp_split_frames(Cvirtual_image& image, int cblocks_x, int cblocks_y);
void shp_split_shadows(Cvirtual_image& image);
void shp_xor_decode_frames(Cvirtual_image& image, int c_frames);
void shp_xor_encode_frames(Cvirtual_image& image, int c_frames);

#endif // !defined(AFX_SHP_TS_FILE_H__26D17BE0_F135_11D3_B605_0000B4936994__INCLUDED_)
