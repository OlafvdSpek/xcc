// virtual_image.h: interface for the Cvirtual_image class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUAL_IMAGE_H__6FC64BA7_CF65_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_VIRTUAL_IMAGE_H__6FC64BA7_CF65_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "palet.h"

class Cvirtual_image  
{
public:
	void decrease_color_depth(const t_palet_entry* palet);
	void increase_color_depth();
	void flip();
	void load(const void* image, int cx, int cy, int cb_pixel, const t_palet_entry* palet);
	int save_as_pcx(string fname) const;
	int save_as_png(string fname) const;
	void swap_rb();
	Cvirtual_image();
	~Cvirtual_image();

	const byte* image() const
	{
		return m_image;
	}

	byte* image_edit()
	{
		return m_image;
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
		return m_palet;
	}

	int cb_image() const
	{
		return m_cx * m_cy * mcb_pixel;
	}
private:
	byte* m_image;
	int m_cx;
	int m_cy;
	int mcb_pixel;
	t_palet_entry* m_palet;
};

#endif // !defined(AFX_VIRTUAL_IMAGE_H__6FC64BA7_CF65_11D4_A95D_0050042229FC__INCLUDED_)
