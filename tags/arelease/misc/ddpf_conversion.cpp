#include "stdafx.h"
#include "ddpf_conversion.h"

int get_shift(int v)
{
	if (!v)
		return 0;
	int r = 0;
	while (~v & 1)
	{
		r++;
		v >>= 1;
	}
	return r;
}

int get_size(int v)
{
	int r = 0;
	while (v)
	{
		if (v & 1)
			r++;
		v >>= 1;
	}
	return r;
}

void Cddpf_conversion::set_pf(const DDPIXELFORMAT& pf)
{
	a_shift = get_shift(pf.dwRGBAlphaBitMask);
	r_shift = get_shift(pf.dwRBitMask);
	g_shift = get_shift(pf.dwGBitMask);
	b_shift = get_shift(pf.dwBBitMask);
	a_size = get_size(pf.dwRGBAlphaBitMask);
	r_size = get_size(pf.dwRBitMask);
	g_size = get_size(pf.dwGBitMask);
	b_size = get_size(pf.dwBBitMask);
}

int Cddpf_conversion::get_color(int a, int r, int g, int b)
{
	return a >> (8 - a_size) << a_shift | r >> (8 - r_size) << r_shift | g >> (8 - g_size) << g_shift  | b >> (8 - b_size) << b_shift;
}

int Cddpf_conversion::get_color(int r, int g, int b)
{
	return get_color(0, r, g, b);
}

int Cddpf_conversion::get_color(int v)
{
	return get_color(v >> 24, v >> 16 & 0xff, v >> 8 & 0xff, v & 0xff);
}
