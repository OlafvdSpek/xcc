#include "stdafx.h"
#include "xcc_overlays.h"

#include "shp_images.h"
#include "xcc_dirs.h"
#include "xcc_mixs.h"
#include "xif_key.h"

const char* overlay_code[] =
{
	"ti1",
	"ti2",
	"ti3",
	"ti4",
	"ti5",
	"ti6",
	"ti7",
	"ti8",
	"ti9",
	"ti10",
	"ti11",
	"ti12",
	"barb",
	"wood",
	"sbag",
	"cycl",
	"brik",
	"scrate",
	"wcrate",
	NULL
};

const char* terrain_code[] =
{
	"rock1",
	"rock2",
	"rock3",
	"rock4",
	"rock5",
	"rock6",
	"rock7",
	"split2",
	"split3",
	"t01",
	"t02",
	"t03",
	"t04",
	"t05",
	"t06",
	"t07",
	"t08",
	"t09",
	"t10",
	"t11",
	"t12",
	"t13",
	"t14",
	"t15",
	"t16",
	"t17",
	"t18",
	"tc01",
	"tc02",
	"tc03",
	"tc04",
	"tc05",
	NULL
};

static const char* overlays_xif_fname = "overlays.xif";

struct t_overlay_data_entry
{
	int ox;
	int oy;
};

struct t_terrain_data_entry
{
	int c_images;
	int blocked;
};

Cxif_key base_key;
t_theater_id loaded_theater = static_cast<t_theater_id>(-1);
t_overlay_data_entry overlay_data[c_overlay_id];
t_terrain_data_entry terrain_data[c_terrain_id];
void* overlay_image_list[c_overlay_id];
void* terrain_image_list[c_terrain_id];


enum
{
	ki_overlay,
	ki_terrain
};

enum
{
	vi_od_ox,
	vi_od_oy,
};

enum
{
	vi_td_c_images,
	vi_td_blocked
};

int Cxcc_overlays::load_data()
{
	if (base_key.load_key(Cvirtual_binary(xcc_dirs::get_data_dir() + overlays_xif_fname)))
		return 1;
	{
		const Cxif_key& overlay_key = base_key.get_key(ki_overlay);
		for (int i = 0; i < c_overlay_id; i++)
		{
			t_overlay_data_entry& od = overlay_data[i];
			od.ox = od.oy = 0;
			const Cxif_key& ok = overlay_key.get_key(i);
			BOOST_FOREACH(auto& i, ok.m_values)
			{
				switch (i.first)
				{
				case vi_od_ox:
					od.ox = i.second.get_int();
					break;
				case vi_od_oy:
					od.oy = i.second.get_int();
					break;
				}
			}
		}
	}
	{
		const Cxif_key& terrain_key = base_key.get_key(ki_terrain);
		for (int i = 0; i < c_terrain_id; i++)
		{
			t_terrain_data_entry& td = terrain_data[i];
			const Cxif_key& tk = terrain_key.get_key(i);
			td.c_images = tk.get_value_int(vi_td_c_images);
			BOOST_FOREACH(auto& i, tk.m_values)
			{
				switch (i.first)
				{
				case vi_td_blocked:
					td.blocked = i.second.get_int();
					break;
				}
			}
		}
	}
	return 0;
}

int Cxcc_overlays::save_data()
{
	{
		Cxif_key& overlay_key = base_key.set_key(ki_overlay);
		for (int i = 0; i < c_overlay_id; i++)
		{
			Cxif_key& ok = overlay_key.set_key(i);
			const t_overlay_data_entry& od = overlay_data[i];
			if (od.ox)
				ok.set_value_int(vi_od_ox, od.ox);
			if (od.oy)
				ok.set_value_int(vi_od_oy, od.oy);
		}
	}
	{
		Cxif_key& terrain_key = base_key.set_key(ki_terrain);
		for (int i = 0; i < c_terrain_id; i++)
		{
			Cxif_key& tk = terrain_key.set_key(i);
			const t_terrain_data_entry& td = terrain_data[i];
			tk.set_value_int(vi_td_c_images, td.c_images);
			if (td.blocked)
				tk.set_value_int(vi_td_blocked, td.blocked);
		}
	}
	return base_key.vdata().save(xcc_dirs::get_data_dir() + overlays_xif_fname);
}

bool Cxcc_overlays::terrain_in(int v, t_theater_id theater)
{
	return (terrain_data[v >> 8].c_images >> (theater << 3)) & 0xff;
}

int Cxcc_overlays::load_images(t_theater_id theater)
{
	if (theater == loaded_theater)
		return 0;
	destroy();
	const string ext = '.' + string(Cxcc_mixs::get_theater_fname(theater)).substr(0, 3);
	Cmix_file& conquer_mix = Cxcc_mixs::get_conquer_mix();
	Cmix_file& theater_mix = Cxcc_mixs::get_theater_mix(theater);
	for (int i = 0; i < c_overlay_id; i++)
	{
		if (shp_images::load_shp(overlay_code[i] + ext, theater_mix, overlay_image_list[i])
			&& shp_images::load_shp(static_cast<string>(overlay_code[i]) + ".shp", conquer_mix, overlay_image_list[i]))
			return 1;
	}
	for (int i = 0; i < c_terrain_id; i++)
	{
		Cshp_file f;
		if (f.open(terrain_code[i] + ext, theater_mix))
			continue;
		terrain_data[i].c_images |= f.get_c_images() << (theater << 3);
		if (shp_images::load_shp(f, terrain_image_list[i]))
			return 1;
	}
	loaded_theater = theater;
	return 0;
}

void Cxcc_overlays::destroy()
{
	if (loaded_theater == -1)
		return;
	for (int i = 0; i < c_overlay_id; i++)
	{
		if (overlay_image_list[i])
			shp_images::destroy_shp(overlay_image_list[i]);
	}
	for (int i = 0; i < c_terrain_id; i++)
	{
		if (terrain_image_list[i])
			shp_images::destroy_shp(terrain_image_list[i]);
	}
}

bool Cxcc_overlays::terrain_blocked(int v)
{
	return terrain_data[v >> 8].blocked >> (v & 0xff) & 1;
}

void Cxcc_overlays::terrain_switch_blocked(int v)
{
	terrain_data[v >> 8].blocked ^= 1 << (v & 0xff);
}

const byte* Cxcc_overlays::get_overlay_image(int v, int& x, int& y, int& cx, int& cy)
{
	x = overlay_data[v >> 8].ox;
	y = overlay_data[v >> 8].oy;
	return shp_images::get_shp(overlay_image_list[v >> 8], v & 0xff, cx, cy);
}

const byte* Cxcc_overlays::get_terrain_image(int v, int& x, int& y, int& cx, int& cy)
{
	x = 0;
	y = 0;
	return shp_images::get_shp(terrain_image_list[v >> 8], v & 0xff, cx, cy);
}
