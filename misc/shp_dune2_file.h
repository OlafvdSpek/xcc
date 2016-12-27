#pragma once

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "fname.h"
#include "palet.h"

class Cshp_dune2_file: public Ccc_file_sh<t_shp_dune2_header>  
{
public:
	int extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet _palet) const;
	bool is_valid() const;

	int get_c_images() const
	{
		return header().c_images;
	}

	const t_shp_dune2_image_header* get_image_header(int i) const
	{
		return reinterpret_cast<const t_shp_dune2_image_header*>(data() + get_ofs(i));
	}

	int get_cx(int i) const
	{
		return get_image_header(i)->cx;
	}

	int get_cy(int i) const
	{
		return get_image_header(i)->cy;
	}

	int get_cb_ofs() const
	{
		return get_index16()[1] ? 2 : 4;
	}

	int get_ofs(int i) const
	{
		return get_cb_ofs() == 2 ? get_index16()[i] : get_index32()[i] + 2;			
	}

	const __int16* get_index16() const
	{
		return reinterpret_cast<const __int16*>(data() + sizeof(t_shp_dune2_header));
	}

	const __int32* get_index32() const
	{
		return reinterpret_cast<const __int32*>(data() + sizeof(t_shp_dune2_header));
	}

	const byte* get_image(int i) const
	{
		const byte* r = reinterpret_cast<const byte*>(get_image_header(i) + 1);
		if (get_image_header(i)->compression & 1)
			r += 16;
		return r;
	}

	const byte* get_reference_palet(int i) const
	{
		return get_image_header(i)->compression & 1 ? reinterpret_cast<const byte*>(get_image_header(i) + 1) : NULL;
	}

	bool is_compressed(int i) const
	{
		return ~get_image_header(i)->compression & 2;
	}
};
