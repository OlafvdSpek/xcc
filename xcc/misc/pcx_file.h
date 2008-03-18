#pragma once

#include "cc_structures.h"
#include "image_file.h"
#include "palet.h"
#include "pcx_decode.h"
#include "virtual_image.h"

class Cpcx_file: public Cimage_file<t_pcx_header>  
{
public:
	void decode(void*) const;
	bool is_valid() const;
	Cvirtual_image vimage() const;

	int cb_pixel() const
	{
		return get_header()->c_planes;
	}

	int cx() const
	{
		return get_header()->xmax - get_header()->xmin + 1;
	}

	int cy() const
	{
		return get_header()->ymax - get_header()->ymin + 1;
	}

	void decode(byte* d) const
	{
		pcx_decode(get_image(), d, *get_header());
	}
	
	const byte* get_image() const
	{
		return get_data() + sizeof(t_pcx_header);
	}

    const t_palet* get_palet() const
    {
        return reinterpret_cast<const t_palet*>(get_data() + get_size() - sizeof(t_palet));
    }
};
