// shp_dune2_file.h: interface for the Cshp_dune2_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHP_DUNE2_FILE_H__C3201020_41ED_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_SHP_DUNE2_FILE_H__C3201020_41ED_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "fname.h"
#include "palet.h"

class Cshp_dune2_file: public Ccc_file_sh<t_shp_dune2_header>  
{
public:
	int extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet _palet) const;

	bool is_valid() const
	{
		const t_shp_dune2_header& header = *get_header();
		int size = get_size();
		if (sizeof(t_shp_dune2_header) + 4 > size || header.c_images < 1 || header.c_images > 1000 || sizeof(t_shp_dune2_header) + get_cb_ofs() * header.c_images > size)
			return false;
		for (int i = 0; i < get_c_images(); i++)
		{
			if (get_ofs(i) < 0 || get_ofs(i) + sizeof(t_shp_dune2_image_header) > min(size, 32 << 10))
				return false;
			const t_shp_dune2_image_header& image_header = *get_image_header(i);
			if (image_header.compression & ~3 ||
				!image_header.cx || 
				!image_header.cy ||
				image_header.cy != image_header.cy2 ||
				image_header.size_in > size - get_ofs(i))
				return false;
		}
		return true;
	}

	int get_c_images() const
	{
		return get_header()->c_images;
	}

	const t_shp_dune2_image_header* get_image_header(int i) const
	{
		return reinterpret_cast<const t_shp_dune2_image_header*>(get_data() + get_ofs(i));
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
		return reinterpret_cast<const __int16*>(get_data() + sizeof(t_shp_dune2_header));
	}

	const __int32* get_index32() const
	{
		return reinterpret_cast<const __int32*>(get_data() + sizeof(t_shp_dune2_header));
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

#endif // !defined(AFX_SHP_DUNE2_FILE_H__C3201020_41ED_11D4_B606_0000B4936994__INCLUDED_)
