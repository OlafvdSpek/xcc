#include "stdafx.h"

#include <afx.h>
#ifdef __AFX_H__
#include <afxdlgs.h>
#endif
#include "dds_file.h"
#include "image_file.h"
#include "jpeg_file.h"
#include "pcx_file.h"
#include "pcx_file_write.h"
#include "png_file.h"
#include "tga_file.h"
#include "virtual_image.h"

Cvirtual_image::Cvirtual_image()
{
	m_cx = 0;
	m_cy = 0;
	mcb_pixel = 0;
}

Cvirtual_image::Cvirtual_image(const Cvirtual_binary& image, int cx, int cy, int cb_pixel, const t_palet_entry* palet, bool inflate)
{
	load(image, cx, cy, cb_pixel, palet, inflate);
}

Cvirtual_image::Cvirtual_image(const void* image, int cx, int cy, int cb_pixel, const t_palet_entry* palet, bool inflate)
{
	load(image, cx, cy, cb_pixel, palet, inflate);
}

const Cvirtual_image& Cvirtual_image::palet(const t_palet_entry* palet, bool inflate)
{
	if (palet)
	{
		memcpy(m_palet.write_start(sizeof(t_palet)), palet, sizeof(t_palet));
		if (inflate)
			convert_palet_18_to_24(reinterpret_cast<t_palet_entry*>(m_palet.data_edit()));
	}
	else
		m_palet.clear();
	return *this;
}

void Cvirtual_image::load(const Cvirtual_binary& image, int cx, int cy, int cb_pixel, const t_palet_entry* p, bool inflate)
{
	assert(cb_pixel == 1 || cb_pixel == 3 || cb_pixel == 4);
	m_cx = cx;
	m_cy = cy;
	mcb_pixel = cb_pixel;
	if (image.size() == cb_image())
		m_image = image;
	else
		m_image.write_start(cb_image());
	palet(p, inflate);
}

void Cvirtual_image::load(const void* image, int cx, int cy, int cb_pixel, const t_palet_entry* p, bool inflate)
{
	assert(cb_pixel == 1 || cb_pixel == 3 || cb_pixel == 4);
	m_cx = cx;
	m_cy = cy;
	mcb_pixel = cb_pixel;
	m_image.write_start(cb_image());
	if (image)
		memcpy(m_image.data_edit(), image, cb_image());
	palet(p, inflate);
}

int Cvirtual_image::load(const Cvirtual_binary& s)
{
	int error = 0;
	Cdds_file dds_f;
#ifdef JPEG_SUPPORT
	Cjpeg_file jpeg_f;
#endif
	Cpcx_file pcx_f;
#ifdef PNG_SUPPORT
	Cpng_file png_f;
#endif
	Ctga_file tga_f;
	if (dds_f.load(s), dds_f.is_valid())
		*this = dds_f.vimage();
	else 
#ifdef JPEG_SUPPORT
	if (jpeg_f.load(s), jpeg_f.is_valid())
		error = jpeg_f.decode(*this);
	else 
#endif
	if (pcx_f.load(s), pcx_f.is_valid())
		*this = pcx_f.vimage();
#ifdef PNG_SUPPORT
	else if (png_f.load(s), png_f.is_valid())
		error = png_f.decode(*this);
#endif
	else if (tga_f.load(s), tga_f.is_valid())
		error = tga_f.decode(*this);
	else
		error = 0x100;
	return error;
}

int Cvirtual_image::load(const Cvirtual_file& f)
{
	return load(f.read());
}

int Cvirtual_image::load(const string& fname)
{
	Cvirtual_binary s;
	int error = s.load(fname);
	if (!error)
		error = load(s);
	return error;
}

#ifdef JPEG_SUPPORT
int Cvirtual_image::load_as_jpeg(const string& fname)
{
	Cjpeg_file f;
	int error = f.open(fname);
	if (!error)
	{
		error = f.decode(*this);
		f.close();
	}
	return error;
}
#endif

int Cvirtual_image::save(Cvirtual_file& f, t_file_type ft) const
{
	return image_file_write(f, ft, image(), palet(), m_cx, m_cy);
}

Cvirtual_file Cvirtual_image::save(t_file_type ft) const
{
	return image_file_write(ft, image(), palet(), m_cx, m_cy);
}

int Cvirtual_image::save(const string& fname, t_file_type ft) const
{
	return image_file_write(fname, ft, image(), palet(), m_cx, m_cy);
}

#ifdef JPEG_SUPPORT
int Cvirtual_image::save_as_jpeg(Cvirtual_file& f, int q ) const
{
	return jpeg_file_write(f, image(), palet(), m_cx, m_cy, q);
}

int Cvirtual_image::save_as_jpeg(const string& fname, int q) const
{
	return jpeg_file_write(fname, image(), palet(), m_cx, m_cy, q);
}
#endif

void Cvirtual_image::save_as_pcx(Cvirtual_file& f) const
{
	pcx_file_write(f, image(), palet(), m_cx, m_cy);
}

int Cvirtual_image::save_as_pcx(const string& fname) const
{
	return pcx_file_write(fname, image(), palet(), m_cx, m_cy);
}

#ifdef PNG_SUPPORT
int Cvirtual_image::save_as_png(Cvirtual_file& f) const
{
	return png_file_write(f, image(), palet(), m_cx, m_cy);
}

int Cvirtual_image::save_as_png(const string& fname) const
{
	return png_file_write(fname, image(), palet(), m_cx, m_cy);
}
#endif

void Cvirtual_image::swap_rb()
{
	int count = m_cx * m_cy;
	t_palet_entry* r = reinterpret_cast<t_palet_entry*>(m_image.data_edit());
	while (count--)
	{
		swap(r->r, r->b);
		r++;
	}
}

static void flip_frame(const byte* s, byte* d, int cx, int cy, int cb_pixel)
{
	int cb_line = cx * cb_pixel;
	const byte* r = s;
	byte* w = d + cb_line * cy;
	while (cy--)
	{
		w -= cb_line;
		memcpy(w, r, cb_line);
		r += cb_line;
	}
}

void Cvirtual_image::flip()
{
	Cvirtual_binary t = m_image;
	flip_frame(t.data(), image_edit(), cx(), cy(), cb_pixel());
}


void Cvirtual_image::cb_pixel(int cb_pixel, const t_palet_entry* palet)
{
	if (cb_pixel < mcb_pixel)
		decrease_color_depth(cb_pixel, palet);
	else if (cb_pixel > mcb_pixel)
		increase_color_depth(cb_pixel);
}

void Cvirtual_image::decrease_color_depth(int new_cb_pixel, const t_palet_entry* palet)
{
	if (new_cb_pixel == 3)
	{
		remove_alpha();
		return;
	}
	assert(new_cb_pixel == 1);
	int old_cb_pixel = cb_pixel();
	Cvirtual_binary t = m_image;
	load(NULL, cx(), cy(), new_cb_pixel, palet);
	byte* w = image_edit();
	int count = m_cx * m_cy;
	if (old_cb_pixel == 3)
	{
		const t_palet_entry* r = reinterpret_cast<const t_palet_entry*>(t.data());
		while (count--)
		{
			*w++ = find_color(r->r, r->g, r->b, palet);
			r++;
		}
	}
	else
	{
		assert(old_cb_pixel == 4);
		const t_palet32entry* r = reinterpret_cast<const t_palet32entry*>(t.data());
		while (count--)
		{
			*w++ = r->a < 0x80 ? find_color(r->r, r->g, r->b, palet) : 0;
			r++;
		}
	}
}

inline static t_palet32entry p32e(int r, int g, int b, int a = 0)
{
	t_palet32entry e;
	e.r = r;
	e.g = g;
	e.b = b;
	e.a = a;
	return e;
}

inline static t_palet32entry p32e(t_palet_entry e)
{
	return p32e(e.r, e.g, e.b);
}

inline static t_palet32entry p32e(const t_palet palet, int i)
{
	return i ? p32e(palet[i]) : p32e(0x80, 0x80, 0x80, 0xff);
}

void Cvirtual_image::increase_color_depth(int new_cb_pixel)
{
	if (cb_pixel() == 3)
	{
		if (new_cb_pixel == 4)
			add_alpha();
		return;
	}
	assert(cb_pixel() == 1);
	Cvirtual_image t = *this;
	const byte* r = t.image();
	load(NULL, cx(), cy(), new_cb_pixel, NULL);
	int count = m_cx * m_cy;
	if (cb_pixel() == 3)
	{
		t_palet_entry* w = reinterpret_cast<t_palet_entry*>(image_edit());
		while (count--)
			*w++ = t.palet()[*r++];
	}
	else
	{
		assert(cb_pixel() == 4);
		t_palet32entry* w = reinterpret_cast<t_palet32entry*>(image_edit());
		while (count--)
			*w++ = p32e(t.palet(), *r++);
	}
}

void Cvirtual_image::add_alpha()
{
	assert(cb_pixel() == 3);
	Cvirtual_binary t = m_image;
	load(NULL, cx(), cy(), 4, NULL);
	int count = m_cx * m_cy;
	const byte* r = t.data();
	byte* w = image_edit();
	while (count--)
	{
		*w++ = *r++;
		*w++ = *r++;
		*w++ = *r++;
		*w++ = 0;
	}
}

void Cvirtual_image::remove_alpha()
{
	if (cb_pixel() != 4)
		return;
	Cvirtual_binary t = m_image;
	load(NULL, cx(), cy(), 3, NULL);
	int count = m_cx * m_cy;
	const byte* r = t.data();
	byte* w = image_edit();
	while (count--)
	{
		*w++ = *r++;
		*w++ = *r++;
		*w++ = *r++;
		r++;
	}
}

void Cvirtual_image::increase_palet_depth()
{
	assert(false);
	Cvirtual_binary t = m_palet;
	const t_palet_entry* s = reinterpret_cast<const t_palet_entry*>(t.data());
	t_palet_entry* d = reinterpret_cast<t_palet_entry*>(t.data_edit());
	for (int i = 0; i < 256; i++)
	{
		d[i].r = (s[i].r & 63) * 255 / 63;
		d[i].g = (s[i].g & 63) * 255 / 63;
		d[i].b = (s[i].b & 63) * 255 / 63;
	}
}

#ifdef __AFX_H__
int Cvirtual_image::get_clipboard()
{
	int error = 0;
	if (!OpenClipboard(NULL))
		error = 0x100;
	else
	{
		void* h_mem = GetClipboardData(CF_DIB);
		if (!h_mem)
			error = 0x101;
		else
		{
			byte* mem = reinterpret_cast<byte*>(GlobalLock(h_mem));
			if (!mem)
				error = 0x102;
			else
			{	const BITMAPINFOHEADER* header = reinterpret_cast<BITMAPINFOHEADER*>(mem);
				int cb_pixel = header->biBitCount >> 3;
				if (cb_pixel != 1 && cb_pixel != 3)
					error = 0x103;
				else
				{
					t_palet_entry* palet = cb_pixel == 1 ? new t_palet : NULL;
					const RGBQUAD* r = reinterpret_cast<RGBQUAD*>(mem + header->biSize);
					if (palet)
					{
						for (int i = 0; i < (header->biClrUsed ? header->biClrUsed : 256); i++)
						{
							palet[i].r = r->rgbRed;
							palet[i].g = r->rgbGreen;
							palet[i].b = r->rgbBlue;
							r++;
						}
					}
					int cx = header->biWidth;
					int cy = header->biHeight;
					if (cx * cb_pixel & 3)
					{
						int cb_line = cx * cb_pixel;
						byte* d = new byte[cb_line * cy];
						byte* w = d;
						for (int y = 0; y < cy; y++)
						{
							memcpy(w, r, cb_line);
							r += cb_line + 3 >> 2;
							w += cb_line;
						}
						load(d, cx, cy, cb_pixel, palet);
						delete[] d;
					}
					else
						load(r, cx, cy, cb_pixel, palet);
					flip();
					if (cb_pixel == 3)
						swap_rb();
					delete palet;
				}
				GlobalUnlock(h_mem);
			}
		}
		CloseClipboard();
	}
	return error;
}

int Cvirtual_image::set_clipboard() const
{
	int error = 0;
	int cb_line = cx() * cb_pixel();
	void* h_mem = GlobalAlloc(GMEM_MOVEABLE, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + (cb_line + 3 & ~3) * cy());
	if (!h_mem)
		error = 0x100;
	else
	{
		byte* mem = reinterpret_cast<byte*>(GlobalLock(h_mem));
		if (!mem)
			error = 0x101;
		else
		{
			BITMAPINFOHEADER* header = reinterpret_cast<BITMAPINFOHEADER*>(mem);
			ZeroMemory(header, sizeof(BITMAPINFOHEADER));
			header->biSize = sizeof(BITMAPINFOHEADER);
			header->biWidth = cx();
			header->biHeight = cy();
			header->biPlanes = 1;
			header->biBitCount = cb_pixel() << 3;
			header->biCompression = BI_RGB;
			RGBQUAD* palet = reinterpret_cast<RGBQUAD*>(mem + sizeof(BITMAPINFOHEADER));
			if (cb_pixel() == 1)
			{
				for (int i = 0; i < 256; i++)
				{
					palet->rgbBlue = this->palet()[i].b;
					palet->rgbGreen = this->palet()[i].g;
					palet->rgbRed = this->palet()[i].r;
					palet->rgbReserved = 0;
					palet++;
				}
			}
			const byte* r = image() + cb_image();
			byte* w = reinterpret_cast<byte*>(palet);
			for (int y = 0; y < cy(); y++)
			{
				r -= cb_line;
				if (cb_pixel() == 3)
				{
					for (int x = 0; x < cx(); x++)
					{
						const t_palet_entry* v = reinterpret_cast<const t_palet_entry*>(r) + x;
						*w++ = v->b;
						*w++ = v->g;
						*w++ = v->r;
					}
					w -= cb_line;
				}
				else
					memcpy(w, r, cb_line);
				w += cb_line + 3 & ~3;
			}
			GlobalUnlock(h_mem);
			if (!OpenClipboard(NULL))
				error = 0x102;
			else
			{
				if (EmptyClipboard() && SetClipboardData(CF_DIB, h_mem))
					h_mem = NULL;
				else
					error = 0x103;
				CloseClipboard();
			}
		}
		if (h_mem)
			GlobalFree(h_mem);
	}
	return error;
}

int Cvirtual_image::load()
{
	const char* load_filter = "Image files (*.jpeg;*.jpg;*.pcx;*.png)|*.jpeg;*.jpg;*.pcx;*.png|JPEG files (*.jpeg;*.jpg)|*.jpeg;*.jpg|PCX files (*.pcx)|*.pcx|PNG files (*.png)|*.png|";

	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, load_filter, NULL);
	if (IDOK == dlg.DoModal())
		return load(static_cast<string>(dlg.GetPathName()));
	return 2;
}

int Cvirtual_image::save() const
{
	const char* save_filter = "JPEG files (*.jpeg;*.jpg)|*.jpeg;*.jpg|PCX files (*.pcx)|*.pcx|PNG files (*.png)|*.png|";

	CFileDialog dlg(false, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, save_filter, NULL);
	dlg.m_ofn.nFilterIndex = 2;
	if (IDOK == dlg.DoModal())
	{
		t_file_type ft = ft_pcx;
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			ft = ft_jpeg;
			break;
		case 2:
			ft = ft_pcx;
			break;
		case 3:
			ft = ft_png;
			break;
		}
		return save(static_cast<string>(dlg.GetPathName()), ft);
	}
	return 2;
}
#endif