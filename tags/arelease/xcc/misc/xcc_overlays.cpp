// xcc_overlays.cpp: implementation of the Cxcc_overlays class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xcc_dirs.h"
#include "xcc_overlays.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

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
		"wcrate"
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
		"tc05"
};

static const char* overlays_xif_fname = "overlays.xif";

struct t_overlay_data_entry
{
	dword ox;
	dword oy;
};

struct t_terrain_data_entry
{
	dword c_images;
	dword blocked;
};

Cxif_key base_key;
t_theater_id loaded_theater = static_cast<t_theater_id>(-1);
t_overlay_data_entry overlay_data[c_overlay_id];
t_terrain_data_entry terrain_data[c_terrain_id];
void* overlay_image_list[c_overlay_id];
void* terrain_image_list[c_terrain_id];


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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
	Ccc_file f(false);
	f.open(xcc_dirs::get_data_dir() + overlays_xif_fname);
	if (!f.is_open())
		return 1;
	const dword size = f.get_size();
	byte* data = new byte[size];
	f.read(data, size);
	f.close();
	base_key.load_key(data, size);
	delete[] data;
	{
		const Cxif_key& overlay_key = base_key.get_key(ki_overlay);
		for (int i = 0; i < c_overlay_id; i++)
		{
			t_overlay_data_entry& od = overlay_data[i];
			od.ox = od.oy = 0;
			const Cxif_key& ok = overlay_key.get_key(i);
			for (t_xif_value_map::const_iterator i = ok.m_values.begin(); i != ok.m_values.end(); i++)
			{
				switch (i->first)
				{
				case vi_od_ox:
					od.ox = i->second.get_data_dword();
					break;
				case vi_od_oy:
					od.oy = i->second.get_data_dword();
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
			td.c_images = tk.get_value_dword(vi_td_c_images);
			for (t_xif_value_map::const_iterator i = tk.m_values.begin(); i != tk.m_values.end(); i++)
			{
				switch (i->first)
				{
				case vi_td_blocked:
					td.blocked = i->second.get_data_dword();
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
				ok.set_value(vi_od_ox, od.ox);
			if (od.oy)
				ok.set_value(vi_od_oy, od.oy);
		}
	}
	{
		Cxif_key& terrain_key = base_key.set_key(ki_terrain);
		for (int i = 0; i < c_terrain_id; i++)
		{
			Cxif_key& tk = terrain_key.set_key(i);
			const t_terrain_data_entry& td = terrain_data[i];
			tk.set_value(vi_td_c_images, td.c_images);
			if (td.blocked)
				tk.set_value(vi_td_blocked, td.blocked);
		}
	}
	Cfile32 f;
	if (f.open_write(xcc_dirs::get_data_dir() + overlays_xif_fname))
		return 1;
	dword size = base_key.key_size();
	byte* data = new byte[size];
	base_key.save_key(data);
	f.write(data, size);
	delete[] data;
	f.close();
	return 0;
}

bool Cxcc_overlays::terrain_in(dword v, t_theater_id theater)
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
	{
		// load overlays
		for (int i = 0; i < c_overlay_id; i++)
		{		
			Cshp_file f;
			f.open(overlay_code[i] + ext, theater_mix);
			if (!f.is_open())
			{
				f.open(static_cast<string>(overlay_code[i]) + ".shp", conquer_mix);
				if (!f.is_open())		
					return 1;
			}
			int res = shp_images::load_shp(f, overlay_image_list[i]);
			f.close();
			if (res)
				return 1;
		}
	}
	{
		// load terrain
		for (int i = 0; i < c_terrain_id; i++)
		{		
			Cshp_file f;
			f.open(terrain_code[i] + ext, theater_mix);
			if (f.is_open())
			{
				terrain_data[i].c_images |= f.get_c_images() << (theater << 3);
				int res = shp_images::load_shp(f, terrain_image_list[i]);
				f.close();
				if (res)
					return 1;
			}
		}
	}
	loaded_theater = theater;
	return 0;
}

void Cxcc_overlays::destroy()
{
	if (loaded_theater == -1)
		return;
	{
		// destroy overlays
		for (int i = 0; i < c_overlay_id; i++)
		{
			if (overlay_image_list[i])
				shp_images::destroy_shp(overlay_image_list[i]);
		}
	}
	{
		// destroy terrain
		for (int i = 0; i < c_terrain_id; i++)
		{
			if (terrain_image_list[i])
				shp_images::destroy_shp(terrain_image_list[i]);
		}
	}
}

bool Cxcc_overlays::terrain_blocked(dword v)
{
	return terrain_data[v >> 8].blocked >> (v & 0xff) & 1;
}

void Cxcc_overlays::terrain_switch_blocked(dword v)
{
	terrain_data[v >> 8].blocked ^= 1 << (v & 0xff);
}

const byte* Cxcc_overlays::get_overlay_image(dword v, int& x, int& y, int& cx, int& cy)
{
	x = overlay_data[v >> 8].ox;
	y = overlay_data[v >> 8].oy;
	return shp_images::get_shp(overlay_image_list[v >> 8], v & 0xff, cx, cy);
}

const byte* Cxcc_overlays::get_terrain_image(dword v, int& x, int& y, int& cx, int& cy)
{
	x = 0;
	y = 0;
	return shp_images::get_shp(terrain_image_list[v >> 8], v & 0xff, cx, cy);
}
