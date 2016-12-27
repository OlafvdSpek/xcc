#include "stdafx.h"

#include "XCC TMP EditorDoc.h"

#include <boost/algorithm/string.hpp>
#include "mix_file.h"
#include "pal_file.h"
#include "string_conversion.h"
#include "xcc_dirs.h"

using namespace boost;

IMPLEMENT_DYNCREATE(CXCCTMPEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CXCCTMPEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CXCCTMPEditorDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CXCCTMPEditorDoc::CXCCTMPEditorDoc()
{
}

CXCCTMPEditorDoc::~CXCCTMPEditorDoc()
{
}

BOOL CXCCTMPEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_header.cblocks_x = m_header.cblocks_y = 0;
	m_header.cx = 60;
	m_header.cy = 30;
	m_map.clear();
	load_temperate_palet(false);

	return TRUE;
}

void CXCCTMPEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// m_header.cblocks_x = 0;
		// m_header.cblocks_y = 0;
		int cblocks_x = m_header.cblocks_x;
		int cblocks_y = m_header.cblocks_y;
		int half_cx = m_header.cx / 2;
		int half_cy = m_header.cy / 2;

		Cvirtual_binary d;
		byte* w = d.write_start(256 << 10);

		*reinterpret_cast<t_tmp_ts_header*>(w) = m_header;
		w += sizeof(t_tmp_ts_header);
		int* index = reinterpret_cast<int*>(w);
		w += 4 * m_header.cblocks_x * m_header.cblocks_y;
		for (int y = 0; y < cblocks_y; y++)
		{
			for (int x = 0; x < cblocks_x; x++)
			{
				t_map::iterator i;
				for (i = m_map.begin(); i != m_map.end(); i++)
				{
					t_map_entry& e = i->second;
					if (e.header.x == half_cx * (x - y) && e.header.y == half_cy * (x + y))
					{
						*index++ = w - d.data();
						int cb_diamond = m_header.cx * m_header.cy >> 1;
						int cb_extra_data = e.header.cx_extra * e.header.cy_extra;
						e.header.z_ofs = cb_diamond + sizeof(t_tmp_image_header);
						e.header.extra_ofs = 2 * cb_diamond + sizeof(t_tmp_image_header);
						if (e.extra_data.data())
							e.header.extra_z_ofs = 2 * cb_diamond + cb_extra_data + sizeof(t_tmp_image_header);
						e.header.has_extra_data = static_cast<bool>(e.extra_data.data());
						e.header.has_z_data = static_cast<bool>(e.z_data.data());
						e.header.has_damaged_data = true; // false;
						*reinterpret_cast<t_tmp_image_header*>(w) = e.header;
						w += sizeof(t_tmp_image_header);
						assert(e.data.size() == cb_diamond);
						w += e.data.read(w);
						if (e.z_data.data())
							w += e.z_data.read(w);
						if (e.extra_data.data())
						{
							w += e.extra_data.read(w);
							if (e.extra_z_data.data())
								w += e.extra_z_data.read(w);
						}
						break;
					}
				}
				if (i == m_map.end())
					*index++ = 0;
			}
		}
		ar.Write(d.data(), w - d.data());
	}
	else
	{
		int cb_s = ar.GetFile()->GetLength();
		Cvirtual_binary s;
		Ctmp_ts_file f;
		if (ar.Read(s.write_start(cb_s), cb_s) != cb_s)
			AfxThrowArchiveException(CArchiveException::badIndex, ar.m_strFileName);
		f.load(s, cb_s);
		if (!f.is_valid())
			AfxThrowArchiveException(CArchiveException::badIndex, ar.m_strFileName);
		else
		{
			m_header = f.header();
			int cb_diamond = f.get_cb_diamond();
			for (int i = 0; i < f.get_c_tiles(); i++)
			{
				if (!f.get_index()[i])
					continue;
				const t_tmp_image_header& header = *f.get_image_header(i);
				t_map_entry& e = m_map[m_map.empty() ? 0 : m_map.rbegin()->first + 1];
				e.header = header;
				bool has_z_data = header.has_z_data;
				e.data = Cvirtual_binary(f.get_image(i), cb_diamond);
				if (has_z_data)
					e.z_data = Cvirtual_binary(f.get_z_image(i), cb_diamond);
				if (header.has_extra_data)
				{
					int cb_extra_data = f.get_cb_extra_data(i);
					e.extra_data = Cvirtual_binary(f.get_extra_data(i), cb_extra_data);
					if (has_z_data)
						e.extra_z_data = Cvirtual_binary(f.get_extra_z_data(i), cb_extra_data);
				}
			}
			string ext = to_lower_copy(Cfname(static_cast<string>(ar.m_strFileName)).get_fext());
			if (ext == ".des")
				load_desert_palet(false);
			else if (ext == ".lun")
				load_lunar_palet(false);
			else if (ext == ".sno")
				load_snow_palet(false);
			else if (ext == ".ubn")
				load_urban2_palet(false);
			else if (ext == ".urb")
				load_urban_palet(false);
			else
				load_temperate_palet(false);
		}
	}
}

int CXCCTMPEditorDoc::load_palet(string fname, bool probe)
{
	if (Cfname(fname).get_path().size())
	{
		Cpal_file f;
		int error = f.open(fname);
		if (!error && !f.is_valid())
			error = 0x100;
		else
		{
			f.decode(m_palet);
			f.close();
			UpdateAllViews(NULL);
		}
		return error;
	}
	Cmix_file main_mix;
	int error = 0;
	for (int i = 0; i < 2; i++)
	{
		t_game game = m_header.cx == 48 ? game_ts : game_ra2;
		switch (i)
		{
		case 0:
			error = main_mix.open(xcc_dirs::get_main_mix(game));
			break;
		case 1:
			error = game == game_ra2 ? main_mix.open(xcc_dirs::get_dir(game) + "ra2md.mix") : 1;
			break;
		}
		if (!error)
		{
			Cmix_file cache_mix;
			error = cache_mix.open("cache.mix", main_mix);
			if (error)
				error = cache_mix.open("cachemd.mix", main_mix);
			if (!error)
			{
				Cpal_file f;
				error = f.open(fname, cache_mix);
				if (!error)
				{
					if (!f.is_valid())
						error = 0x100;
					else
					{
						if (!probe)
						{
							f.decode(m_palet);
							UpdateAllViews(NULL);
						}
					}
					f.close();
				}
				cache_mix.close();
			}
			main_mix.close();
		}
		if (!error)
			break;
	}
	return error;
}

int CXCCTMPEditorDoc::load_desert_palet(bool probe)
{
	return load_palet("isodes.pal", probe);
}

int CXCCTMPEditorDoc::load_lunar_palet(bool probe)
{
	return load_palet("isolun.pal", probe);
}

int CXCCTMPEditorDoc::load_snow_palet(bool probe)
{
	return load_palet("isosno.pal", probe);
}

int CXCCTMPEditorDoc::load_temperate_palet(bool probe)
{
	return load_palet("isotem.pal", probe);
}

int CXCCTMPEditorDoc::load_urban_palet(bool probe)
{
	return load_palet("isourb.pal", probe);
}

int CXCCTMPEditorDoc::load_urban2_palet(bool probe)
{
	return load_palet("isoubn.pal", probe);
}

/////////////////////////////////////////////////////////////////////////////
// CXCCTMPEditorDoc commands

void CXCCTMPEditorDoc::SetModifiedFlag(BOOL bModified)
{
	if (IsModified() == bModified)
		return;
	CDocument::SetModifiedFlag(bModified);
	CString title = GetTitle();
	if (bModified)
	{
		if (title.Find('*') < 0)
			title += '*';
	}
	else
	{
		if (title.Find('*') >= 0)
			title.Delete(title.GetLength() - 1);
	}
	SetTitle(title);
}

void CXCCTMPEditorDoc::insert()
{
	t_map_entry& e = m_map[m_map.empty() ? 0 : m_map.rbegin()->first + 1];
	{
		t_tmp_image_header& h = e.header;
		h.x = 0;
		h.y = 0;
		h.x_extra = 0;
		h.y_extra = 0;
		h.cx_extra = 0;
		h.cy_extra = 0;
		h.height = 0;
		h.terrain_type = 0;
		h.ramp_type = 0;
		h.radar_red_left = 0x80;
		h.radar_green_left = 0x80;
		h.radar_blue_left = 0x80;
		h.radar_red_right = 0x80;
		h.radar_green_right = 0x80;
		h.radar_blue_right = 0x80;
	}
	e.data = Cvirtual_binary(NULL, m_header.cx * m_header.cy >> 1);
	// e = m_map.begin()->second;
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

void CXCCTMPEditorDoc::remove(int id)
{
	m_map.erase(id);
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

void CXCCTMPEditorDoc::remove_extra_image(int id)
{
	m_map.find(id)->second.extra_data.clear();
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

Cvirtual_image CXCCTMPEditorDoc::get_complete() const
{
	t_rect global = get_rect();
	int cx = global.r - global.x;
	int cy = global.b - global.y;
	byte* d = new byte[cx * cy];
	draw(d);
	Cvirtual_image image;
	image.load(d, cx, cy, 1, palet());
	delete[] d;
	return image;
}

void CXCCTMPEditorDoc::set_complete(const Cvirtual_image& image)
{
	t_rect global = get_rect();
	int cx = global.r - global.x;
	int cy = global.b - global.y;
	if (image.cx() != cx || image.cy() != cy)
		return;
	draw_reverse(image.image());
}

Cvirtual_image CXCCTMPEditorDoc::get_image(int id)
{
	const t_map_entry& e = map().find(id)->second;
	int cx = header().cx;
	int cy = header().cy;
	byte* d = new byte[cx * cy];
	decode_tile(e.data.data(), d, cx);
	Cvirtual_image image;
	image.load(d, cx, cy, 1, palet());
	delete[] d;
	return image;
}

Cvirtual_image CXCCTMPEditorDoc::get_extra_image(int id)
{
	const t_map_entry& e = map().find(id)->second;
	Cvirtual_image image;
	image.load(e.extra_data.data(), e.header.cx_extra, e.header.cy_extra, 1, palet());
	return image;
}

void CXCCTMPEditorDoc::set_image(int id, const Cvirtual_image& image)
{
	int cx = header().cx;
	int cy = header().cy;
	if (image.cx() != cx || image.cy() != cy)
		return;
	t_map_entry& e = map_edit().find(id)->second;
	encode_tile(image.image(), e.data.data_edit(), cx);
	if (e.header.has_z_data && !e.z_data.data())
		encode_tile(image.image(), e.z_data.data_edit(), cx);
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

void CXCCTMPEditorDoc::set_extra_image(int id, const Cvirtual_image& image)
{
	t_map_entry& e = map_edit().find(id)->second;
	e.extra_data.write(image.image(), image.cb_image());
	if (e.header.has_z_data && (!e.extra_z_data.data() || e.header.cx_extra != image.cx() || e.header.cy_extra != image.cy()))
		e.extra_z_data.write(image.image(), image.cb_image());
	if (!e.header.has_extra_data)
		e.header.x_extra = e.header.y_extra = 0;
	e.header.cx_extra = image.cx();
	e.header.cy_extra = image.cy();
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

void CXCCTMPEditorDoc::set_image_header(int id, const t_tmp_image_header& header)
{
	map_edit().find(id)->second.header = header;
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

t_rect CXCCTMPEditorDoc::get_rect(bool view_true_height) const
{
	int half_cy = m_header.cy / 2;
	t_rect rect;
	if (m_map.empty())
	{
		rect.x = rect.y = 0;
		rect.r = rect.b = 0;
	}
	else
	{
		rect.x = rect.y = INT_MAX;
		rect.r = rect.b = INT_MIN;
		for (t_map::const_iterator i = m_map.begin(); i != m_map.end(); i++)
		{
			const t_tmp_image_header& header = i->second.header;
			t_rect t;
			t.x = header.x;
			t.y = header.y;
			t.r = t.x + m_header.cx;
			t.b = t.y + m_header.cy;
			if (header.has_extra_data)
			{
				t.x = min(t.x, header.x_extra);
				t.y = min(t.y, header.y_extra);
				t.r = max(t.r, header.x_extra + header.cx_extra);
				t.b = max(t.b, header.y_extra + header.cy_extra);
			}
			t.y -= header.height * half_cy;
			t.b -= header.height * half_cy;
			rect.x = min(rect.x, t.x);
			rect.y = min(rect.y, t.y);
			rect.r = max(rect.r, t.r);
			rect.b = max(rect.b, t.b);
		}
	}
	if (view_true_height)
	{
		int y = half_cy * (m_header.cblocks_x + m_header.cblocks_y);
		rect.b = max(rect.b, y);
	}
	return rect;
}

byte* get_p(byte* d, int x, int y, int cx, int cy)
{
	return d + x + cx * y;
}

const byte* get_p(const byte* d, int x, int y, int cx, int cy)
{
	return d + x + cx * y;
}

void CXCCTMPEditorDoc::draw(byte* d, int outline, bool view_true_height) const
{
	int half_cy = m_header.cy / 2;
	t_rect global = get_rect(view_true_height);
	int global_cx = global.r - global.x;
	int global_cy = global.b - global.y;
	memset(d, 0, global_cx * global_cy);
	for (t_map::const_iterator i = m_map.begin(); i != m_map.end(); i++)
	{
		const t_map_entry& e = i->second;
		const t_tmp_image_header& header = e.header;
		const byte* r = e.data.data();
		byte* w_line = get_p(d, header.x - global.x, header.y - global.y - header.height * half_cy, global_cx, global_cy);
		int x = m_header.cx / 2;
		int cx = 0;
		int y = 0;
		for (; y < half_cy; y++)
		{
			cx += 4;
			x -= 2;
			memcpy(w_line + x, r, cx);
			if (outline == i->first)
			{
				memset(w_line + x, 0xff, 2);
				memset(w_line + x + cx - 2, 0xff, 2);
			}
			r += cx;
			w_line += global_cx;
		}
		for (; y < m_header.cy; y++)
		{
			cx -= 4;
			x += 2;
			memcpy(w_line + x, r, cx);
			if (outline == i->first && cx)
			{
				memset(w_line + x, 0xff, 2);
				memset(w_line + x + cx - 2, 0xff, 2);
			}
			r += cx;
			w_line += global_cx;
		}
		if (e.extra_data.data())
		{
			r = e.extra_data.data();
			byte* w_line = get_p(d, header.x_extra - global.x, header.y_extra - global.y - header.height * half_cy, global_cx, global_cy);
			int cx = header.cx_extra;
			int cy = header.cy_extra;
			for (y = 0; y < cy; y++)
			{
				byte* w = w_line;
				for (int i = 0; i < cx; i++)
				{
					int v = *r++;
					if (v)
						*w = v;
					w++;
				}
				w_line += global_cx;
			}
		}
	}
}

void CXCCTMPEditorDoc::draw_reverse(const byte* d)
{
	int half_cy = m_header.cy / 2;
	t_rect global = get_rect();
	int global_cx = global.r - global.x;
	int global_cy = global.b - global.y;
	for (t_map::iterator i = m_map.begin(); i != m_map.end(); i++)
	{
		t_map_entry& e = i->second;
		t_tmp_image_header& header = e.header;
		byte* r = e.data.data_edit();
		const byte* w_line = get_p(d, header.x - global.x, header.y - global.y - header.height * half_cy, global_cx, global_cy);
		int x = m_header.cx / 2;
		int cx = 0;
		int y = 0;
		for (; y < half_cy; y++)
		{
			cx += 4;
			x -= 2;
			memcpy(r, w_line + x, cx);
			r += cx;
			w_line += global_cx;
		}
		for (; y < m_header.cy; y++)
		{
			cx -= 4;
			x += 2;
			memcpy(r, w_line + x, cx);
			r += cx;
			w_line += global_cx;
		}
		if (e.extra_data.data())
		{
			r = e.extra_data.data_edit();
			const byte* w_line = get_p(d, header.x_extra - global.x, header.y_extra - global.y - header.height * half_cy, global_cx, global_cy);
			int cx = header.cx_extra;
			int cy = header.cy_extra;
			for (y = 0; y < cy; y++)
			{
				const byte* w = w_line;
				for (int i = 0; i < cx; i++)
				{
					int v = *r;
					if (v)
						*r = *w;
					r++;
					w++;
				}
				w_line += global_cx;
			}
		}
	}
	SetModifiedFlag();
	UpdateAllViews(NULL);
}
