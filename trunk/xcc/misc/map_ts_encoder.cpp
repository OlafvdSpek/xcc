#include "stdafx.h"
#include "map_ts_encoder.h"

#include <fstream>
#include <map>
#include <vector>
#include <zlib.h>
#include "file32.h"
#include "cc_structures.h"
#include "shp_decode.h"
#include "virtual_image.h"
#include "xste.h"

static const int format_version = 2;

static int get_x_inc(const Cmap_ts_encoder::t_header& header, int y)
{
	return y < header.cx ? -1 : 1;
}

static int get_r_inc(const Cmap_ts_encoder::t_header& header, int y)
{
	if (y < header.cy)
		return 1;
	return y > header.cy ? -1 : 0;
}

Cmap_ts_encoder::Cmap_ts_encoder(ostream& f, bool encode4):
	m_f(f)
{
	lower_case(false);
	m_w = NULL;
	m_encode4 = encode4;
}

void Cmap_ts_encoder::header(t_header v)
{
	m_header = v;
}

int Cmap_ts_encoder::process_section_start(const string& name)
{
	if (name == "IsoMapPack5")
		m_w = m_d.write_start(4 << 20);
	else if (m_encode4 && (name == "OverlayPack" || name == "OverlayDataPack") || name == "PreviewPack")
		m_w = m_d.write_start(1 << 20);
	else
		m_w = NULL;
	if (!m_encode4 || !m_w)
		m_f << '[' << name << ']' << endl;
	m_section_name = name;
	return 0;
}

bool Cmap_ts_encoder::process_section() const
{
	return true;
}

int Cmap_ts_encoder::process_key(const string& name, const string& value)
{
	if (m_w)
	{
		strcpy(reinterpret_cast<char*>(m_w), value.c_str());
		m_w += value.length();
	}
	else
		m_f << name << '=' << value << endl;
	return 0;
}

void Cmap_ts_encoder::map_encode4(const void* s, void* d, int count)
{
#if 1
	const int l = m_header.cx + m_header.cy;
	t_iso_map_pack_entry4* t = new t_iso_map_pack_entry4[l * l];
	memset(t, 0, l * l * sizeof(t_iso_map_pack_entry4));
	const t_iso_map_pack_entry* r = reinterpret_cast<const t_iso_map_pack_entry*>(s);
	while (count--)
	{
		t_iso_map_pack_entry4* e = t + r->x + l * r->y;
		e->tile = r->tile;
		e->sub_tile = r->sub_tile;
		e->z = r->z;
		r++;
	}
	t_iso_map_pack_entry4* w = reinterpret_cast<t_iso_map_pack_entry4*>(d);
	int x_line = m_header.cx;
	int r_line = m_header.cx + 1;
	int y = 1;
	int z = 0;
	while (x_line < r_line)
	{
		for (int x = x_line; x < r_line; x++)
		{
			t_iso_map_pack_entry4* r = t + x + l * y;
			int z_inc = r->z - z;
			z += z_inc;
			w->tile = r->tile;
			w->sub_tile = r->sub_tile;
			w->z = z_inc;
			w++;
		}
		x_line += get_x_inc(m_header, y);
		r_line += get_r_inc(m_header, y);
		y++;
	}
	delete[] t;
#else
	const t_iso_map_pack_entry* r = reinterpret_cast<const t_iso_map_pack_entry*>(s);
	t_iso_map_pack_entry4* w = reinterpret_cast<t_iso_map_pack_entry4*>(d);
	int x = 0;
	int y = 1;
	int z = 0;
	while (count--)
	{
		// int x_inc = r->x - x;
		// int y_inc = r->y - y;
		int z_inc = r->z - z;
		// x += x_inc;
		// y += y_inc;
		z += z_inc;
		w->tile = r->tile;
		w->sub_tile = r->sub_tile;
		w->z = z_inc;
		r++;
		w++;
	}
#endif
}

int Cmap_ts_encoder::overlay_encode4(const byte* s, byte* d) const
{
	byte* w = d;
	int x_line = m_header.cx;
	int r_line = m_header.cx + 1;
	int y = 1;
	while (x_line < r_line)
	{
		for (int x = x_line; x < r_line; x++)
			*w++ = s[x + (y << 9)];
		if (y < m_header.cx)
			x_line--;
		else
			x_line++;
		if (y < m_header.cy)
			r_line++;
		else if (y > m_header.cy)
			r_line--;
		y++;
	}
	return w - d;
}

int overlay_data_encode4(const byte* r, byte* d, int cb_s, const byte* overlay)
{
	byte* w = d;
	while (cb_s--)
	{
		if (*overlay++ != 0xff)
			*w++ = *r;
		r++;
	}
	return w - d;
}

void Cmap_ts_encoder::map_decode4(const void* s, void* d, int count, const t_header& size)
{
	const t_iso_map_pack_entry4* r = reinterpret_cast<const t_iso_map_pack_entry4*>(s);
	t_iso_map_pack_entry* w = reinterpret_cast<t_iso_map_pack_entry*>(d);
	int x_line = size.cx;
	int r_line = size.cx + 1;
	int y = 1;
	int z = 0;
	while (x_line < r_line)
	{
		for (int x = x_line; x < r_line; x++)
		{
			assert(count);
			z += r->z;
			w->x = x;
			w->y = y;
			w->tile = r->tile;
			w->zero1 = 0;
			w->zero2 = 0;
			w->sub_tile = r->sub_tile;
			w->z = z;
			w->zero3 = 0;
			r++;
			w++;
			count--;
		}
		x_line += get_x_inc(size, y);
		r_line += get_r_inc(size, y);
		y++;
	}
	assert(!count);
}

int Cmap_ts_encoder::overlay_decode4(const byte* s, byte* d, const t_header& header)
{
	const int cb_d = 1 << 18;
	memset(d, -1, cb_d);
	const byte* r = s;
	int x_line = header.cx;
	int r_line = header.cx + 1;
	int y = 1;
	while (x_line < r_line)
	{
		for (int x = x_line; x < r_line; x++)
			d[x + (y << 9)] = *r++;
		x_line += get_x_inc(header, y);
		r_line += get_r_inc(header, y);
		y++;
	}
	return cb_d;
}

int Cmap_ts_encoder::overlay_data_decode4(const byte* s, byte* d, const byte* overlay, const t_header& header)
{
	const int cb_d = 1 << 18;
	memset(d, 0, cb_d);
	const byte* r = s;
	int x_line = header.cx;
	int r_line = header.cx + 1;
	int y = 1;
	while (x_line < r_line)
	{
		for (int x = x_line; x < r_line; x++)
		{
			if (*overlay++ != 0xff)
				d[x + (y << 9)] = *r++;
		}
		x_line += get_x_inc(header, y);
		r_line += get_r_inc(header, y);
		y++;
	}
	return cb_d;
}

static Cvirtual_binary preview_decode4(Cvirtual_binary s, const Cvirtual_binary palet)
{
	typedef vector<__int64> t_vector;

	t_vector default_vector;
	{
		const byte* r = palet.data();
		const byte* r_end = palet.data() + palet.size();
		while (r < r_end)
		{
			__int64 v = 0;
			memcpy(&v, r, 6);
			r += 6;
			default_vector.push_back(v);
		}
	}
	const __int16* r = reinterpret_cast<const __int16*>(s.data());
	const __int16* r_end = reinterpret_cast<const __int16*>(s.data() + s.size());
	int c_colors = *r++;
	while (c_colors--)
	{
		__int64 v = 0;
		memcpy(&v, r, 6);
		r += 3;
		default_vector.push_back(v);
	}
	Cvirtual_binary d;
	byte* w = d.write_start((r_end - r) * 6);
	while (r < r_end)
	{
		__int64 v = default_vector[*r++];
		*w++ = v >> 40 & 0xff;
		*w++ = v >> 32 & 0xff;
		*w++ = v >> 24 & 0xff;
		*w++ = v >> 16 & 0xff;
		*w++ = v >> 8 & 0xff;
		*w++ = v & 0xff;
	}
	return d;
}

#if 0
static void log_iso_map_pack(const void* e, int count, const Cmap_ts_encoder::t_header& size)
{
	ofstream l("c:/temp/iso_map_pack.txt");
	Cvirtual_image buffer, z_buffer;
	t_palet palet;
	for (int i = 0; i < 16; i++)
		palet[i].r = palet[i].g = palet[i].b = i * 255 / 15;
	palet[255].r = 255;
	palet[255].g = palet[255].b = 0;
	const int cx = size.cx + size.cy;
	const int cy = cx;
	buffer.load(NULL, cx, cy, 1, palet);
	memset(buffer.image_edit(), -1, cx * cy);
	int z_min = INT_MAX;
	int z_max = INT_MIN;
	const t_iso_map_pack_entry* r = reinterpret_cast<const t_iso_map_pack_entry*>(e);
	while (count--)
	{
		z_min = min(z_min, r->z);
		z_max = max(z_max, r->z);
		buffer.pixel8(r->x, r->y, r->z);
		l << r->x << '\t' << r->y << '\t' << r->tile << '\t' << r->sub_tile << '\t' << r->z << endl;
		r++;
	}
	buffer.save_as_png("d:/temp/buffer_map.png");
	for (i = z_min; i <= z_max; i++)
		palet[i].r = palet[i].g = palet[i].b = (i - z_min) * 255 / (z_max - z_min);
	z_buffer.load(NULL, size.cx - 1, size.cy - 1, 1, palet);
	for (int y = 1; y < size.cy; y++)
	{
		for (int x = 1; x < size.cx; x++)
		{
			z_buffer.pixel8(x - 1, y - 1, buffer.pixel8(x + y, size.cx - x + y));
		}
	}
	z_buffer.save_as_png("d:/temp/height_map.png");
}

static void log_overlay_pack(const byte* s, const Cmap_ts_encoder::t_header& size)
{
	t_palet palet;
	for (int i = 0; i < 256; i++)
		palet[i].r = palet[i].g = palet[i].b = i;
	Cvirtual_image buffer, overlay_buffer;
	buffer.load(s, 512, 512, 1, palet);
	overlay_buffer.load(NULL, size.cx - 1, size.cy - 1, 1, palet);
	for (int y = 1; y < size.cy; y++)
	{
		for (int x = 1; x < size.cx; x++)
		{
			overlay_buffer.pixel8(x - 1, y - 1, buffer.pixel8(x + y, size.cx - x + y));
		}
	}
	overlay_buffer.save_as_png("d:/temp/overlay_map.png");
}
#endif

static void write_pack(ostream& os, const byte* s, int cb_s)
{
	Cvirtual_binary d = encode64(Cvirtual_binary(s, cb_s));
	// d.size(encode64(s, d.write_start(cb_s << 1), cb_s));
	const byte* r = d.data();
	const byte* r_end = d.data_end();
	int line_i = 1;
	while (r < r_end)
	{
		char line[80];
		int cb_line = min(r_end - r, 70);
		memcpy(line, r, cb_line);
		line[cb_line] = 0;
		r += cb_line;
		os << line_i++ << '=' << line << endl;
	}
	os << endl;
}

void Cmap_ts_encoder::process_section_end()
{
	if (m_w)
	{
		m_w = NULL;
		Cvirtual_binary d = decode64(m_d);
		if (m_encode4)
		{
			if (m_section_name == "IsoMapPack5")
			{
				int count = decode5(d, m_d.data_edit(), d.size(), 5) / sizeof(t_iso_map_pack_entry);
				t_iso_map_pack_entry4* f = new t_iso_map_pack_entry4[count];
				t_iso_map_pack_entry* g = new t_iso_map_pack_entry[count];
				map_encode4(m_d, f, count);
				// log_iso_map_pack(m_d, count, header);
				/*
				map_decode4(f, g, count, header);
				for (int i = 0; i < count; i++)
				{
					t_iso_map_pack_entry& a = reinterpret_cast<t_iso_map_pack_entry*>(m_d)[i];
					t_iso_map_pack_entry& b = g[i];
					if (memcmp(&a, &b, sizeof(t_iso_map_pack_entry)))
						assert(!memcmp(&a, &b, sizeof(t_iso_map_pack_entry)));
				}
				*/
				// assert(!memcmp(m_d, g, sizeof(t_iso_map_pack_entry) * count));
				m_iso_map_pack.write(f, sizeof(t_iso_map_pack_entry4) * count);
				delete[] g;
				delete[] f;
			}
			else if (m_section_name == "OverlayPack")
			{
				m_overlay_pack.size(decode5(d, m_overlay_pack.write_start(256 << 10), d.size(), 80));
				/*
				decode5(d, m_d, cb_d, 80);
				// log_overlay_pack(m_d, m_header);
				m_overlay_pack.size(overlay_encode4(m_d, m_overlay_pack.write_start(256 << 10)));
				*/
			}
			else if (m_section_name == "OverlayDataPack")
			{
				m_overlay_data_pack.size(decode5(d, m_overlay_data_pack.write_start(256 << 10), d.size(), 80));
				/*
				Cvirtual_binary t;
				t.size(overlay_encode4(m_d, t.write_start(256 << 10)));
				assert(m_overlay_pack.data());
				m_overlay_data_pack.size(overlay_data_encode4(t.data(), m_overlay_data_pack.write_start(256 << 10), t.size(), m_overlay_pack.data()));
				// m_overlay_data_pack.size(overlay_encode4(m_d, m_overlay_data_pack.write_start(256 << 10)));
				*/
			}
			else if (m_section_name == "PreviewPack")
			{
				if (strcmp(reinterpret_cast<const char*>(m_d.data()), "BIACcgAEwBtAMnRABAAaQCSANMAVQASAAnIABMAbQDJ0QAQAGkAkgDTAFUAEgAJyAATAG0yAsAIAXQ5PDQ5PDQ6JQATAEE6PDQ4PDI4JgBTAFEAkgAJyAATAG0AydEAEABpAJIA0wBVA"))
					m_preview_pack.write(m_d, decode5(d, m_d.data_edit(), d.size(), 5));
				else
					m_preview_pack.clear();
			}
		}
		else
		{
			byte* e = m_d.data_edit();
			int cb_e = decode5(d, e, d.size(), 5);
			d.size(encode5(e, d.data_edit(), cb_e, 5));
			// cb_e = encode64(d, e, cb_d);
			write_pack(m_f, d, d.size());
		}
	}
	else
		m_f << endl;
}

static void analyse_preview(Cvirtual_binary& s)
{
	typedef map<__int64, int> t_map;

	const t_palet_entry* r = reinterpret_cast<const t_palet_entry*>(s.data());
	int count = s.size() / 6;
	t_map map;
	while (count--)
	{
		__int64 v0 = r->r << 16 | r->g << 8 | r->b;
		r++;
		__int64 v1 = r->r << 16 | r->g << 8 | r->b;
		r++;
		__int64 v = v0 << 24 | v1;
		map[v]++;
	}
	static int cmax_colors = 0;
	int c_colors = map.size();
	cmax_colors = max(cmax_colors, c_colors);
}

static Cvirtual_binary preview_encode4(Cvirtual_binary s, const Cvirtual_binary palet)
{
	typedef map<__int64, int> t_map;

	t_map default_map;
	int j = 0;
	{
		const byte* r = palet.data();
		const byte* r_end = palet.data() + palet.size();
		while (r < r_end)
		{
			__int64 v = 0;
			memcpy(&v, r, 6);
			r += 6;
			default_map[v] = j++;
		}
	}
	Cvirtual_binary d;
	t_map map;
	int count = s.size() / 6;
	const t_palet_entry* r = reinterpret_cast<const t_palet_entry*>(s.data());
	__int16* w = reinterpret_cast<__int16*>(d.write_start(256 << 10));
	while (count--)
	{
		__int64 v0 = r->r << 16 | r->g << 8 | r->b;
		r++;
		__int64 v1 = r->r << 16 | r->g << 8 | r->b;
		r++;
		__int64 v = v0 << 24 | v1;
		t_map::const_iterator i = default_map.find(v);
		if (i == default_map.end())
			map[v] = -1;
	}
	*w++ = map.size();
	for (t_map::iterator i = map.begin(); i != map.end(); i++)
	{
		memcpy(w, &i->first, 6);
		w += 3;
		i->second = j++;
	}
	count = s.size() / 6;
	r = reinterpret_cast<const t_palet_entry*>(s.data());
	while (count--)
	{
		__int64 v0 = r->r << 16 | r->g << 8 | r->b;
		r++;
		__int64 v1 = r->r << 16 | r->g << 8 | r->b;
		r++;
		__int64 v = v0 << 24 | v1;
		t_map::const_iterator i = default_map.find(v);
		if (i == default_map.end())
			*w++ = map.find(v)->second;
		else
			*w++ = i->second;
	}
	d.size(reinterpret_cast<byte*>(w) - d.data());
	return d;
}

void Cmap_ts_encoder::encode(const Cvirtual_binary palet)
{
	Cvirtual_binary t;

	t.size(overlay_encode4(overlay_pack().data(), t.write_start(256 << 10)));
	m_overlay_pack = t;

	t.size(overlay_encode4(overlay_data_pack().data(), t.write_start(256 << 10)));
	m_overlay_data_pack.size(overlay_data_encode4(t.data(), m_overlay_data_pack.write_start(256 << 10), t.size(), m_overlay_pack.data()));

	// create_heightmap().save_as_png("d:/temp/hm.png");
	// create_preview().save_as_png("d:/temp/pv.png");
	// analyse_preview(preview_pack());
	m_preview_pack = preview_encode4(preview_pack(), palet);
}

enum
{
	vi_format_version,
	vi_ini,
	vi_iso_map_pack,
	vi_overlay_pack,
	vi_overlay_data_pack,
	vi_preview_pack,
	vi_description,
	vi_gamemode,
	vi_cx,
	vi_cy,
	vi_cmax_players
};

bool Cmap_ts_encoder::wrong_version(const Cxif_key& k)
{
	return k.get_value_int(vi_format_version) != format_version;
}

bool Cmap_ts_encoder::write_mmx(const Cxif_key& k)
{
	return k.exists_value(vi_gamemode);
}

void Cmap_ts_encoder::write_pkt(ostream& os, const Cxif_key& k, string title)
{
	string description = k.get_value_string(vi_description);
	CXSTE xste;
	if (!xste.open(game_ra2))
	{
		xste.csf_f().set_value("XMM:" + title, Ccsf_file::convert2wstring(description), "");
		if (!xste.write())
			description = "XMM:" + title;
		xste.close();			
	}
	os << "[MultiMaps]" << endl
		<< "1=" << title << endl
		<< endl
		<< '[' << title << ']' << endl
		<< "Description=" << description << endl
		<< "CD=0,1" << endl
		<< "MinPlayers=2" << endl
		<< "MaxPlayers=" << k.get_value_int(vi_cmax_players) << endl
		<< "GameMode=" << k.get_value_string(vi_gamemode) << endl;
}

void Cmap_ts_encoder::write_map(ostream& os, const Cxif_key& k, const Cvirtual_binary palet)
{
	t_header header;
	header.cx = k.get_value_int(vi_cx);
	header.cy = k.get_value_int(vi_cy);
	byte* d = new byte[4 << 20];
	if (k.exists_value(vi_iso_map_pack))
	{
		os << "[IsoMapPack5]" << endl;
		int count = k.get_value(vi_iso_map_pack).get_size() / sizeof(t_iso_map_pack_entry4);
		t_iso_map_pack_entry* f = new t_iso_map_pack_entry[count];
		map_decode4(k.get_value(vi_iso_map_pack).get_data(), f, count, header);
		write_pack(os, d, encode5(reinterpret_cast<byte*>(f), d, sizeof(t_iso_map_pack_entry) * count, 5));
		delete[] f;
	}
	if (k.exists_value(vi_overlay_pack))
	{
		byte* e = d + overlay_decode4(k.get_value(vi_overlay_pack).get_data(), d, header);
		int cb_e = encode5(d, e, 1 << 18, 80);
		os << "[OverlayPack]" << endl;
		write_pack(os, e, cb_e);
		if (k.exists_value(vi_overlay_data_pack))
		{
			byte* e = d + overlay_data_decode4(k.get_value(vi_overlay_data_pack).get_data(), d, k.get_value(vi_overlay_pack).get_data(), header);
			int cb_e = encode5(d, e, 1 << 18, 80);
			os << "[OverlayDataPack]" << endl;
			write_pack(os, e, cb_e);
		}
	}
	if (k.exists_value(vi_preview_pack))
	{
		os << "[PreviewPack]" << endl;
		Cvirtual_binary t = preview_decode4(Cvirtual_binary(k.get_value(vi_preview_pack).get_data(), k.get_value(vi_preview_pack).get_size()), palet);
		write_pack(os, d, encode5(t.data(), d, t.size(), 5));
		// write_pack(os, d, encode5(k.get_value(vi_preview_pack).get_data(), d, k.get_value(vi_preview_pack).get_size(), 5));
	}
	os << k.get_value_string(vi_ini);
	delete[] d;
}

int Cmap_ts_encoder::write_map(string fname, const string& ini)
{
	Cxif_key k;
	k.set_value_int(vi_format_version, format_version);
	k.set_value_string(vi_ini, ini);
	if (m_header.gamemode.size())
	{
		k.set_value_string(vi_description, m_header.description);
		k.set_value_string(vi_gamemode, m_header.gamemode);
		k.set_value_int(vi_cmax_players, m_header.cmax_players);
	}
	k.set_value_binary(vi_iso_map_pack, iso_map_pack());
	k.set_value_binary(vi_overlay_pack, overlay_pack());
	k.set_value_binary(vi_overlay_data_pack, overlay_data_pack());
	k.set_value_binary(vi_preview_pack, preview_pack());
	k.set_value_int(vi_cx, m_header.cx);
	k.set_value_int(vi_cy, m_header.cy);
	return k.vdata().save(fname);
}

static int get_y(int a, int b, int cx)
{
	return a + b - cx - 1 >> 1;
}

static int get_x(int a, int b, int cx)
{
	return a - get_y(a, b, cx) - 1;
}

Cvirtual_image Cmap_ts_encoder::create_heightmap() const
{
	Cvirtual_image image;
	t_palet palet;
	for (int i = 0; i < 16; i++)
		palet[i].r = palet[i].g = palet[i].b = i * 255 / 15;
	image.load(NULL, m_header.cx << 1, m_header.cy, 1, palet);
	const t_iso_map_pack_entry4* r = reinterpret_cast<const t_iso_map_pack_entry4*>(m_iso_map_pack.data());
	int x_line = m_header.cx;
	int r_line = m_header.cx + 1;
	int y = 1;
	int z = 0;
	while (x_line < r_line)
	{
		for (int x = x_line; x < r_line; x++)
		{
			z += r->z;
			if (x + y & 1)
			{
				int a = get_x(x, y, m_header.cx) << 1;
				int b = get_y(x, y, m_header.cx);
				image.pixel8(a, b, z);
				image.pixel8(a + 1, b, z);
			}
			r++;
		}
		x_line += get_x_inc(m_header, y);
		r_line += get_r_inc(m_header, y);
		y++;
	}
	return image;
}

void Cmap_ts_encoder::extract_map(t_iso_map_pack_entry4* d) const
{
	if (!m_header.cx)
		return;
	const t_iso_map_pack_entry4* r = reinterpret_cast<const t_iso_map_pack_entry4*>(m_iso_map_pack.data());
	int x_line = m_header.cx;
	int r_line = m_header.cx + 1;
	int y = 1;
	int z = 0;
	while (x_line < r_line)
	{
		for (int x = x_line; x < r_line; x++)
		{
			z += r->z;
			t_iso_map_pack_entry4& e = d[x << 9 | y];
			e.tile = r->tile;
			e.sub_tile = r->sub_tile;
			e.z = z;
			r++;
		}
		x_line += get_x_inc(m_header, y);
		r_line += get_r_inc(m_header, y);
		y++;
	}
}

static const t_palet_entry* get_radar_colors(Cvirtual_binary& s, int tile, int sub_tile)
{
	const byte* r = s.data();
	if (tile != -1)
	{
		while (tile--)
		{
			int count = *r++;
			r += 6 * count;
		}
	}
	int count = *r++;
	r += 6 * sub_tile;
	return reinterpret_cast<const t_palet_entry*>(r);
}

Cvirtual_image Cmap_ts_encoder::create_preview() const
{
	Cvirtual_binary s;
	s.load("d:/temp/snow_colormap.bin");
	Cvirtual_image image;
	image.load(NULL, m_header.cx << 1, m_header.cy, 3, NULL);
	const t_iso_map_pack_entry4* r = reinterpret_cast<const t_iso_map_pack_entry4*>(m_iso_map_pack.data());
	int x_line = m_header.cx;
	int r_line = m_header.cx + 1;
	int y = 1;
	while (x_line < r_line)
	{
		for (int x = x_line; x < r_line; x++)
		{
			if (x + y & 1)
			{
				const t_palet_entry* c = get_radar_colors(s, r->tile, r->sub_tile);
				int a = get_x(x, y, m_header.cx) << 1;
				int b = get_y(x, y, m_header.cx);	
				image.pixel24(a, b, c[0]);
				image.pixel24(a + 1, b, c[1]);
			}
			r++;
		}
		x_line += get_x_inc(m_header, y);
		r_line += get_r_inc(m_header, y);
		y++;
	}
	return image;
}
