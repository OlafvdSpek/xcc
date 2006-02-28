// ucr_container_ws_ra_mix.cpp: implementation of the Cucr_container_ws_ra_mix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ucr_container_ws_ra_mix.h"

#include "blowfish.h"
#include "mix_decode.h"
#include "pcx_file_write.h"
#include "shp_decode.h"
#include "string_conversion.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int Cucr_container_ws_ra_mix::open(const Cvirtual_binary& d)
{
	if (!m_objects.empty())
		close();
	if (!d)
		return 1;
	Cstream_reader sr(d);
	int flags = sr.read_int();
	if (flags & ~0x30000)
		return 1;
	if (flags & 0x20000)
	{
		Cblowfish bf;
		byte key[56];
		get_blowfish_key(sr.read(80), key);
		bf.set_key(key, 56);
		byte e[8];
		bf.decipher(sr.read(8), e, 8);
		int c = *reinterpret_cast<const __int16*>(e);
		if (84 + (12 * c + 13 & ~7) + *reinterpret_cast<const __int32*>(e + 2) + (flags & 0x10000 ? 20 : 0) != d.size())
			return 1;
		Cvirtual_binary f(NULL, 2 + (12 * c + 5 & ~7));
		memcpy(f.data_edit(), e + 6, 2);
		bf.decipher(sr.read(12 * c + 5 & ~7), f.data_edit() + 2, 12 * c + 5 & ~7);
		int object_offset_delta = 84 + (12 * c + 13 & ~7);
		Cstream_reader sr(f);
		while (c--)
		{
			int id = sr.read_int();
			int offset = sr.read_int() + object_offset_delta;
			int size = sr.read_int();
			m_objects.push_back(Cucr_object(d, nh(8, id), offset, size));
		}
	}
	else
	{
		int c = *reinterpret_cast<const __int16*>(sr.read(2));
		if (10 + 12 * c + sr.read_int() + (flags & 0x10000 ? 20 : 0) != d.size())
			return 1;
		int object_offset_delta = 10 + 12 * c;
		while (c--)
		{
			int id = sr.read_int();
			int offset = sr.read_int() + object_offset_delta;
			int size = sr.read_int();
			m_objects.push_back(Cucr_object(d, nh(8, id), offset, size));
		}
	}
	return 0;
}

Cucr_object_ws_ts_shp::Cucr_object_ws_ts_shp(const Cvirtual_binary& d, int i)
{
	const t_header& h = reinterpret_cast<const t_header*>(d + 8)[i];
	m_d = d;
	m_name = nwzl(8, i) + ".pcx";
	m_offset = i;
	m_size = h.cx * h.cy;
}

Cvirtual_binary Cucr_object_ws_ts_shp::d() const
{
	Cvirtual_binary s;
	const byte* r;
	if (h().compression & 2)
	{
		decode3(m_d + h().offset, s.write_start(h().cx * h().cy), h().cx, h().cy);
		r = s;
	}
	else
		r = m_d + h().offset;
	/*
	byte* w = d + h.x + global_cx * h.y;
	for (int y = 0; y < cy; y++)
	{
		memcpy(w, r, cx);
		r += cx;
		w += global_cx;
	}
	*/
	t_palet palet;
	convert_palet_18_to_24(reinterpret_cast<const t_palet_entry*>(Cvirtual_binary("c:/temp/bzip/nukeanim.pal").data()), palet);
	return pcx_file_write(s, palet, h().cx, h().cy);
}

const Cucr_object_ws_ts_shp::t_header& Cucr_object_ws_ts_shp::h() const
{
	return reinterpret_cast<const t_header*>(m_d + 8)[m_offset];
}

int Cucr_container_ws_ts_shp::open(const Cvirtual_binary& d)
{
	if (!m_objects.empty())
		close();
	if (!d)
		return 1;
	Cstream_reader sr(d);
	if (sr.read_short())
		return 1;
	short global_cx = sr.read_short();
	short global_cy = sr.read_short();
	short c = sr.read_short();
	for (int i = 0; i < c; i++)
		m_objects.push_back(Cucr_object_ws_ts_shp(d, i));
	return 0;
}