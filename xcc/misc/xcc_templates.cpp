#include "stdafx.h"
#include "xcc_templates.h"

#include "fname.h"
#include "palet.h"
#include "shp_images.h"
#include "tmp_file.h"
#include "xcc_dirs.h"
#include "xcc_level.h"
#include "xcc_mixs.h"
#include "xif_key.h"

const char* theater_xif_fname = "theater.xif";

array<void*, 3> Cxcc_templates::bib;
byte* image_data = 0;
array<byte*, 256> Cxcc_templates::image_list;
t_palet Cxcc_templates::palet;
byte Cxcc_templates::shade_rp[256];
t_template_data_entry Cxcc_templates::template_data[256];
byte Cxcc_templates::template_list[256][64];

enum
{
	vi_td_cx,
	vi_td_cy,
	vi_td_c_images,
	vi_td_buildable,
	vi_td_moveable,
	vi_td_fname,
	vi_td_flags,
};

int Cxcc_templates::load_data()
{
	Cxif_key base_key;
	if (base_key.load_key(Cvirtual_binary(xcc_dirs::get_data_dir() + theater_xif_fname)))
		return 1;
	for (int i = 0; i < 0xd8; i++)
	{
		t_template_data_entry& td = template_data[i];
		const Cxif_key& tk = base_key.get_key(i);
		td.cx = tk.get_value_int(vi_td_cx);
		td.cy = tk.get_value_int(vi_td_cy);
		td.c_images = tk.get_value_int(vi_td_c_images);
		td.buildable = 0;
		td.moveable = 0;
		td.flags = 0;
		const string fname = template_code[i];
		/*
		if (fname.substr(0, 1) == "s")
			td.flags |= td_flags_ridge;
		if (fname.substr(0, 1) == "d")
			td.flags |= td_flags_road;
		if (fname.substr(0, 2) == "rv")
			td.flags |= td_flags_river;
		if (fname.substr(0, 2) == "sh")
			td.flags |= td_flags_shore;
		*/
		for (t_xif_value_map::const_iterator i = tk.m_values.begin(); i != tk.m_values.end(); i++)
		{
			switch (i->first)
			{
			case vi_td_buildable:
				td.buildable = *reinterpret_cast<const __int64*>(i->second.get_data());
				break;
			case vi_td_moveable:
				td.moveable = *reinterpret_cast<const __int64*>(i->second.get_data());
				break;
			case vi_td_flags:
				td.flags = i->second.get_int();
				break;
			}
		}
	}
	return 0;
}

int Cxcc_templates::save_data()
{
	Cxif_key base_key;
	for (int i = 0; i < 0xd8; i++)
	{
		Cxif_key& template_key = base_key.set_key(i);
		const t_template_data_entry& td = template_data[i];
		template_key.set_value_int(vi_td_cx, td.cx);
		template_key.set_value_int(vi_td_cy, td.cy);
		template_key.set_value_int(vi_td_c_images, td.c_images);
		template_key.set_value_string(vi_td_fname, template_code[i]);
		if (td.buildable)
			template_key.set_value_int64(vi_td_buildable, td.buildable);
		if (td.moveable)
			template_key.set_value_int64(vi_td_moveable, td.moveable);
		if (td.flags)
			template_key.set_value_int(vi_td_flags, td.flags);
	}
	return base_key.vdata().save(xcc_dirs::get_data_dir() + theater_xif_fname);
}

int Cxcc_templates::load_images(t_theater_id theater)
{
	delete[] image_data;
	image_data = 0;
	const string fname = Cxcc_mixs::theater_fname(theater);
	const string ext = '.' + fname.substr(0, 3);
	Cmix_file& mixf = Cxcc_mixs::theater(theater);
	image_list.assign(NULL);
	memset(template_list, -1, sizeof(template_list));
	int write_i = 0;
// #define RELOAD
	for (int i = 0; i < 0xd8; i++)
	{
#ifdef RELOAD
		t_template_data_entry& td = template_data[i];
		td.c_images &= ~(0xff << (theater << 3));
		f.open(string(template_code[i]) + ext, mixf);
		if (f.is_open())
		{
			f.read_header();
			td.c_images |= f.get_c_images() << (theater << 3);
			f.close();
		}
#endif
		write_i += template_data[i].c_images >> (theater << 3) & 0xff;
	}
	image_data = new byte[576 * write_i];
	write_i = 0;
	byte* write_p = image_data;
	for (int i = 0; i < 0xd8; i++)
	{
		t_template_data_entry& td = template_data[i];
		const int c_images = td.c_images >> (theater << 3) & 0xff;
		if (!c_images)
			continue;
		Ctmp_file f;
		if (f.open(string(template_code[i]) + ext, mixf))
			return 1;
		image_list[i] = write_p;
		const int c_tiles = td.cx * td.cy;
		const byte* ofs_list = f.get_index1();
		for (int j = 0; j < c_tiles; j++)
		{
			if (ofs_list[j] == 0xff)
				continue;
			template_list[i][j] = (write_p - image_list[i]) / 576;
			memcpy(write_p, f.get_image(j), 576);
			write_i++;
			write_p += 576;
		}
	}
	{
		Ccc_file f(false);
		f.open(fname + ".pal", mixf);
		f.read(palet, 768);
		f.close();
		convert_palet_18_to_24(palet);
		f.open(fname.substr(0, 1) + "shade.mrf", mixf);
		f.read(shade_rp, 256);
		f.close();
	}
	for (int i = 0; i < 3; i++)
		shp_images::load_shp("bib" + n(3 - i), bib[i]);
	return 0;
}