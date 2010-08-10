#include "stdafx.h"
#include "shp_file.h"

#include "image_file.h"
#include "shp_decode.h"
#include "shp_images.h"
#include "string_conversion.h"

class Cshp_decoder: public Cvideo_decoder
{
public:
	int cb_pixel() const
	{
		return m_f.cb_pixel();
	}

	int cf() const
	{
		return m_f.cf();
	}

	int cx() const
	{
		return m_f.cx();
	}

	int cy() const
	{
		return m_f.cy();
	}

	int decode(void* d0)
	{
		if (m_frame_i >= cf())
			return 1;
		memcpy(d0, m_video + cb_image() * m_frame_i, cb_image());
		m_frame_i++;
		return 0;
	}

	const t_palet_entry* palet() const
	{
		return m_palet;
	}

	int seek(int f)
	{
		m_frame_i = f;
		return 0;
	}

	Cshp_decoder(const Cshp_file& f, const t_palet_entry* palet)
	{
		m_f.load(f);
		m_f.decode(m_video.write_start(cb_video()));
		m_frame_i = 0;
		memcpy(m_palet, palet, sizeof(t_palet));
	}
private:
	Cshp_file m_f;
	int m_frame_i;
	t_palet m_palet;
	Cvirtual_binary m_video;
};

Cvideo_decoder* Cshp_file::decoder(const t_palet_entry* palet)
{
	return new Cshp_decoder(*this, palet);
}

bool Cshp_file::is_valid() const
{
	const t_shp_header& header = *get_header();
	int size = get_size();
	if (sizeof(t_shp_header) > size || header.c_images < 1 || header.c_images > 1000 || sizeof(t_shp_header) + 8 * (get_header()->c_images + 2) > size)
		return false;
	int c_images = get_c_images();
	return !(get_offset(c_images) != size || get_offset(c_images + 1));
}

void Cshp_file::decode(void* d) const
{
	shp_images::t_image_data* p;
	if (shp_images::load_shp(*this, p))
		return;
	byte* w = reinterpret_cast<byte*>(d);
	for (int i = 0; i < cf(); i++)
	{
		memcpy(w, shp_images::get_shp(p, i), cb_image());
		w += cb_image();
	}
	shp_images::destroy_shp(p);
}

Cvirtual_image Cshp_file::vimage() const
{
	Cvirtual_binary image;
	decode(image.write_start(cb_video()));
	return Cvirtual_image(image, cx(), cf() * cy(), cb_pixel());
}

int Cshp_file::extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet _palet) const
{
	t_palet palet;
	memcpy(palet, _palet, sizeof(t_palet));
	convert_palet_18_to_24(palet);
	int error = 0;
	const int cx = get_cx();
	const int cy = get_cy();
	const int c_images = get_c_images();
	shp_images::t_image_data* p;
	if (!shp_images::load_shp(*this, p))
	{
		Cfname t = name;
		for (int i = 0; i < c_images; i++)
		{
			// xcc_log::write_line("<tr><td>" + name.get_ftitle() + "</td><td><img src=td_icons/" + name.get_fname() + "></td></tr>");
			t.set_title(name.get_ftitle() + " " + nwzl(3, i));
			if (error = image_file_write(t, ft, shp_images::get_shp(p, i), palet, cx, cy))
				break;
		}
		shp_images::destroy_shp(p);
	}
	return error;
}

Cvirtual_binary shp_file_write(const byte* s, int cx, int cy, int c_images)
{
	Cvirtual_binary d;
	const byte* r = s;
	byte* w = d.write_start(sizeof(t_shp_ts_header) + (sizeof(t_shp_ts_image_header) + cx * cy) * c_images);
	t_shp_header& header = *reinterpret_cast<t_shp_header*>(w);
    header.c_images = c_images;
    header.unknown1 = 0;
    header.unknown2 = 0;
    header.cx = cx;
    header.cy = cy;
    header.unknown3 = 0;
	w += sizeof(t_shp_header);
	int* index = reinterpret_cast<int*>(w);
	w += 8 * (c_images + 2);
	for (int i = 0; i < c_images; i++)
	{
		*index++ = 0x80000000 | w - d;
		*index++ = 0;
		w += encode80(r, w, cx * cy);
		r += cx * cy;
	}
	*index++ = w - d;
	*index++ = 0;
	*index++ = 0;
	*index++ = 0;
	d.size(w - d);
	return d;
}