// virtual_image.h: interface for the Cvirtual_image class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUAL_IMAGE_H__6FC64BA7_CF65_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_VIRTUAL_IMAGE_H__6FC64BA7_CF65_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file.h"
#include "palet.h"
#include "virtual_file.h"

class Cvirtual_image
{
public:
	const Cvirtual_image& palet(const t_palet_entry* palet, bool inflate = false);
	void remove_alpha();
	void add_alpha();
	void cb_pixel(int cb_pixel, const t_palet_entry* palet = NULL);
	void decrease_color_depth(int cb_pixel, const t_palet_entry* palet = NULL);
	void increase_color_depth(int cb_pixel);
	void increase_palet_depth();
	void flip();
	int get_clipboard();
	int set_clipboard() const;
	int load();
	int save() const;
	void load(const void* image, int cx, int cy, int cb_pixel, const t_palet_entry* palet, bool inflate = false);
	int load(const Cvirtual_binary& s);
	int load(const Cvirtual_file& f);
	int load(const string& fname);
	int load_as_jpeg(const string& fname);
	int save(Cvirtual_file& f, t_file_type ft) const;
	Cvirtual_file save(t_file_type ft) const;
	int save(const string& fname, t_file_type ft) const;
	int save_as_jpeg(Cvirtual_file& f, int q = -1) const;
	int save_as_jpeg(const string& fname, int q = -1) const;
	void save_as_pcx(Cvirtual_file& f) const;
	int save_as_pcx(const string& fname) const;
	int save_as_png(Cvirtual_file& f) const;
	int save_as_png(const string& fname) const;
	void swap_rb();
	Cvirtual_image();
	Cvirtual_image(const void* image, int cx, int cy, int cb_pixel, const t_palet_entry* palet = NULL, bool inflate = false);

	const byte* image() const
	{
		return m_image.data();
	}

	byte* image_edit()
	{
		return m_image.data_edit();
	}

	int cx() const
	{
		return m_cx;
	}

	int cy() const
	{
		return m_cy;
	}

	int cb_pixel() const
	{
		return mcb_pixel;
	}

	const t_palet_entry* palet() const
	{
		return reinterpret_cast<const t_palet_entry*>(m_palet.data());
	}

	int cb_image() const
	{
		return m_cx * m_cy * mcb_pixel;
	}

	int ofs8(int x, int y) const
	{
		return x + m_cx * y;
	}

	int ofs24(int x, int y) const
	{
		return ofs8(x, y) * 3;
	}

	int pixel8(int x, int y) const
	{
		return m_image.data()[ofs8(x, y)];
	}

	void pixel8(int x, int y, int v)
	{
		m_image.data_edit()[ofs8(x, y)] = v;
	}

	t_palet_entry pixel24(int x, int y) const
	{
		return reinterpret_cast<const t_palet_entry*>(m_image.data())[ofs8(x, y)];
	}
	
	void pixel24(int x, int y, t_palet_entry v)
	{
		reinterpret_cast<t_palet_entry*>(m_image.data_edit())[ofs8(x, y)] = v;
	}
private:
	Cvirtual_binary m_image;
	Cvirtual_binary m_palet;
	int m_cx;
	int m_cy;
	int mcb_pixel;
};

#endif // !defined(AFX_VIRTUAL_IMAGE_H__6FC64BA7_CF65_11D4_A95D_0050042229FC__INCLUDED_)
