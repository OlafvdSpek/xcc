// virtual_image.cpp: implementation of the Cvirtual_image class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "image_file.h"
#include "jpeg_file.h"
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

Cvirtual_image::~Cvirtual_image()
{
	delete m_palet;
	delete[] m_image;
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