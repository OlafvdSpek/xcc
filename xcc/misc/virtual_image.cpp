// virtual_image.cpp: implementation of the Cvirtual_image class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afx.h>
#ifdef __AFX_H__
#include <afxdlgs.h>
#endif
#include "image_file.h"
#include "jpeg_file.h"
#include "pcx_file.h"
#include "pcx_file_write.h"
#include "png_file.h"
#include "virtual_image.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cvirtual_image::Cvirtual_image()
{
	m_image = NULL;
	m_palet = NULL;
}

Cvirtual_image::Cvirtual_image(const Cvirtual_image& v)
{
	m_image = NULL;
	m_palet = NULL;
	*this = v;
}

Cvirtual_image::~Cvirtual_image()
{
	delete m_palet;
	delete[] m_image;
}

const Cvirtual_image& Cvirtual_image::operator=(const Cvirtual_image& v)
{
	load(v.image(), v.cx(), v.cy(), v.cb_pixel(), v.palet());
	return *this;
}

void Cvirtual_image::load(const void* image, int cx, int cy, int cb_pixel, const t_palet_entry* palet)
{
	delete m_palet;
	delete[] m_image;
	m_cx = cx;
	m_cy = cy;
	mcb_pixel = cb_pixel;
	m_image = new byte[cb_image()];
	memcpy(m_image, image, cb_image());
	if (palet)
	{
		m_palet = new t_palet;
		memcpy(m_palet, palet, sizeof(t_palet));
	}
	else
		m_palet = NULL;
}

/*
int Cvirtual_image::load(Cvirtual_file& f)
{
}
*/

int Cvirtual_image::load(string fname)
{
	Ccc_file f(true);
	int error = f.open(fname);
	if (!error)
	{
#ifdef JPEG_SUPPORT
		Cjpeg_file jpeg_f;
#endif
		Cpcx_file pcx_f;
#ifdef PNG_SUPPORT
		Cpng_file png_f;
#endif
#ifdef JPEG_SUPPORT
		if (jpeg_f.load(f), jpeg_f.is_valid())
			error = jpeg_f.decode(*this);
		else 
#endif
		if (pcx_f.load(f), pcx_f.is_valid())
			pcx_f.decode(*this);
#ifdef PNG_SUPPORT
		else if (png_f.load(f), png_f.is_valid())
			error = png_f.decode(*this);
#endif
		else
			error = 0x100;
		f.close();
	}
	return error;
}

#ifdef JPEG_SUPPORT
/*
int Cvirtual_image::load_as_jpeg(Cvirtual_file& f)
{
}
*/

int Cvirtual_image::load_as_jpeg(string fname)
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

/*
int Cvirtual_image::load_as_pcx(Cvirtual_file& f)
{
}
*/

int Cvirtual_image::load_as_pcx(string fname)
{
	Cpcx_file f;
	int error = f.open(fname);
	if (!error)
	{
		f.decode(*this);
		f.close();
	}
	return error;
}

int Cvirtual_image::save(Cvirtual_file& f, t_file_type ft) const
{
	return image_file_write(f, ft, m_image, m_palet, m_cx, m_cy);
}

int Cvirtual_image::save(string fname, t_file_type ft) const
{
	return image_file_write(fname, ft, m_image, m_palet, m_cx, m_cy);
}

#ifdef JPEG_SUPPORT
int Cvirtual_image::save_as_jpeg(Cvirtual_file& f) const
{
	return 1; // jpeg_file_write(f, m_image, m_palet, m_cx, m_cy);
}

int Cvirtual_image::save_as_jpeg(string fname) const
{
	return jpeg_file_write(fname, m_image, m_palet, m_cx, m_cy);
}
#endif

void Cvirtual_image::save_as_pcx(Cvirtual_file& f) const
{
	pcx_file_write(f, m_image, m_palet, m_cx, m_cy);
}

int Cvirtual_image::save_as_pcx(string fname) const
{
	return pcx_file_write(fname, m_image, m_palet, m_cx, m_cy);
}

#ifdef PNG_SUPPORT
int Cvirtual_image::save_as_png(Cvirtual_file& f) const
{
	return 1; // png_file_write(f, m_image, m_palet, m_cx, m_cy);
}

int Cvirtual_image::save_as_png(string fname) const
{
	return png_file_write(fname, m_image, m_palet, m_cx, m_cy);
}
#endif

void Cvirtual_image::swap_rb()
{
	int count = m_cx * m_cy;
	t_palet_entry* r = reinterpret_cast<t_palet_entry*>(m_image);
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
	byte* image = new byte[cb_image()];
	flip_frame(m_image, image, cx(), cy(), cb_pixel());
	delete[] m_image;
	m_image = image;
}

void Cvirtual_image::decrease_color_depth(const t_palet_entry* palet)
{
	assert(mcb_pixel == 3);
	m_palet = new t_palet;
	memcpy(m_palet, palet, sizeof(t_palet));
	int count = m_cx * m_cy;
	byte* image = new byte[count];
	const t_palet_entry* r = reinterpret_cast<t_palet_entry*>(m_image);
	byte* w = image;
	while (count--)
	{
		*w++ = find_color(r->r, r->g, r->b, palet);
		r++;
	}
	delete[] m_image;
	m_image = image;
	mcb_pixel = 1;
}

void Cvirtual_image::increase_color_depth()
{
	assert(mcb_pixel == 1);
	int count = m_cx * m_cy;
	t_palet_entry* image = new t_palet_entry[count];
	const byte* r = m_image;
	t_palet_entry* w = image;
	while (count--)
	{
		*w++ = m_palet[*r++];
	}
	delete[] m_palet;
	m_palet = NULL;
	delete[] m_image;
	m_image = reinterpret_cast<byte*>(image);
	mcb_pixel = 3;
}

void Cvirtual_image::increase_palet_depth()
{
	assert(m_palet);
	for (int i = 0; i < 256; i++)
	{
		m_palet[i].r = (m_palet[i].r & 63) * 255 / 63;
		m_palet[i].g = (m_palet[i].g & 63) * 255 / 63;
		m_palet[i].b = (m_palet[i].b & 63) * 255 / 63;
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
	return get_clipboard(*this);
}

int Cvirtual_image::get_clipboard(Cvirtual_image& image)
{
	int error = 0;
#if 0
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
						image.load(d, cx, cy, cb_pixel, palet);
						delete[] d;
					}
					else
						image.load(r, cx, cy, cb_pixel, palet);
					image.flip();
					if (cb_pixel == 3)
						image.swap_rb();
					delete palet;
				}
				GlobalUnlock(h_mem);
			}
		}
		CloseClipboard();
	}
#endif
	return error;
}

int Cvirtual_image::set_clipboard() const
{
	int error = 0;
	int cb_line = cx() * cb_pixel();
	void* h_mem = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + (cb_line + 3 & ~3) * cy());
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
					palet->rgbBlue = m_palet[i].b;
					palet->rgbGreen = m_palet[i].g;
					palet->rgbRed = m_palet[i].r;
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
	return set_clipboard(*this);
}

int Cvirtual_image::set_clipboard(const Cvirtual_image& image)
{
	int error = 0;
#if 0
	int cb_line = image.cx() * image.cb_pixel();
	void* h_mem = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + (cb_line + 3 & ~3) * image.cy());
	if (!h_mem)
		error = 0x100;
	else
	{
		byte* mem = reinterpret_cast<byte*>(GlobalLock(h_mem));
		if (!mem)
			error = 0x101;
		else
		{
			// image.flip();
			/*
			if (image.cb_pixel() == 3)
				image.swap_rb();
			*/
			BITMAPINFOHEADER* header = reinterpret_cast<BITMAPINFOHEADER*>(mem);
			ZeroMemory(header, sizeof(BITMAPINFOHEADER));
			header->biSize = sizeof(BITMAPINFOHEADER);
			header->biWidth = image.cx();
			header->biHeight = image.cy();
			header->biPlanes = 1;
			header->biBitCount = image.cb_pixel() << 3;
			header->biCompression = BI_RGB;
			RGBQUAD* palet = reinterpret_cast<RGBQUAD*>(mem + sizeof(BITMAPINFOHEADER));
			if (image.cb_pixel() == 1)
			{
				for (int i = 0; i < 256; i++)
				{
					palet->rgbBlue = image.palet()[i].b;
					palet->rgbGreen = image.palet()[i].g;
					palet->rgbRed = image.palet()[i].r;
					palet->rgbReserved = 0;
					palet++;
				}
			}
			const byte* r = image.image() + image.cb_image();
			byte* w = reinterpret_cast<byte*>(palet);
			for (int y = 0; y < image.cy(); y++)
			{
				r -= cb_line;
				if (image.cb_pixel() == 3)
				{
					for (int x = 0; x < image.cx(); x++)
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
			// memcpy(palet, image.image(), image.cb_image());
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
#endif
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