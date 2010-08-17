#pragma once

#include "cc_structures.h"
#include "fname.h"
#include "palet.h"
#include "video_file.h"
#include "virtual_image.h"

const int shp_o_mask = 0x0fffffff;

class Cshp_file: public Cvideo_file<t_shp_header>  
{
public:
	void decode(void* d) const;
	Cvideo_decoder* decoder(const t_palet_entry*);
	bool is_valid() const;
	Cvirtual_image vimage() const;

	int cb_pixel() const
	{
		return 1;
	}

	int cf() const
	{
		return header().c_images;
	}

	int cx() const
	{
		return header().cx;
	}

	int cy() const
	{
		return header().cy;
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

    int get_ref_offset(int i) const
    {
        return get_index()[(i << 1) + 1] & shp_o_mask;
    }
};

Cvirtual_binary shp_file_write(const byte* s, int cx, int cy, int c_images);
