#include "stdafx.h"
#include <memory>
#include <pcx_decode.h>

void pcx_decode(const byte* s, byte* d, const t_pcx_header& header)
{
	const int cx = header.xmax - header.ymin  + 1;
	const int cy = header.ymax - header.ymin + 1;
	const int cb_line = header.cb_line;
	byte* t	= new byte[cb_line * cy * header.c_planes];
	byte* w = t;
	int count = cb_line * cy * header.c_planes;
	while (count)
	{
		int v = *s++;
		if (v < 0xc0)
		{
			*w++ = v;
			count--;
		}
		else
		{
			int c_write = v & 0x3f;
			v = *s++;
			memset(w, v, c_write);
			w += c_write;
			count -= c_write;
		}
	}
	if (header.c_planes == 1)
	{
		const byte* r = t;
		w = d;
		for (int y = 0; y < cy; y++) 
		{
			memcpy(w, r, cx);
			r += cb_line;
			w += cx;
		}
	}
	else
	{
		const byte* read_r = t;
		const byte* read_g = t + cb_line;
		const byte* read_b = t + 2 * cb_line;
		w = d;
		for (int y = 0; y < cy; y++) 
		{
			for (int x = 0; x < cx; x++) 
			{
				*w++ = *read_r++;
				*w++ = *read_g++;
				*w++ = *read_b++;
			}
			read_r += 3 * cb_line - cx;
			read_g += 3 * cb_line - cx;
			read_b += 3 * cb_line - cx;
		}
	}
	delete[] t;
}

static void write_v(byte v, int count, byte*& d)
{
	while (count)
	{
		if (count == 1 && v < 0xc0)
		{
			*d++ = v;
			count = 0;
		}
		else
		{
			const int c_write = count > 63 ? 63 : count;
			*d++ = 0xc0 | c_write;
			*d++ = v;
			count -= c_write;
		}
	}
}

int pcx_encode(const byte* s, byte* d, int _cx, int cy, int c_planes)
{
	byte* t = const_cast<byte*>(s);
	if (c_planes == 3)
	{
		t = new byte[3 * _cx * cy];
		const byte* r = s;
		byte* write_r = t;
		byte* write_g = t + _cx;
		byte* write_b = t + 2 * _cx;
		for (int y = 0; y < cy; y++) 
		{
			for (int x = 0; x < _cx; x++) 
			{
				*write_r++ = *r++;
				*write_g++ = *r++;
				*write_b++ = *r++;
			}
			write_r += 2 * _cx;
			write_g += 2 * _cx;
			write_b += 2 * _cx;
		}
		cy *= 3;
	}
	_cx--;
	const byte* r = t;
	byte* w = d;
	while (cy--)
	{
		int count = 1;
		int cx = _cx;
		byte last = *r++;
		while (cx--)
		{
			byte v = *r++;
			if (last == v)
				count++;
			else
			{
				write_v(last, count, w);
				count = 1;
				last = v;
			}
		}
		write_v(last, count, w);
	}
	if (c_planes == 3)
		delete[] t;
	return w - d;
}