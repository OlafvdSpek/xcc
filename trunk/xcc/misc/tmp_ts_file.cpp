// tmp_ts_file.cpp: implementation of the Ctmp_ts_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pcx_decode.h"
#include "pcx_file_write.h"
#include "tmp_ts_file.h"

void Ctmp_ts_file::get_rect(int& x, int& y, int& cx, int& cy) const
{
	x = INT_MAX;
	y = INT_MAX;
	cx = INT_MIN;
	cy = INT_MIN;	
	int bigy = INT_MIN;
	int bigyval = 0;
	for (int i = 0; i < get_c_tiles(); i++)
	{
		if (get_index()[i])
		{
			int height = get_height() - get_height(i);
			int x_t = get_x(i);
			int y_t = get_y(i) + (height * (get_cy() / 2));
			int x2_t = x_t + get_cx();
			int y2_t = y_t + get_cy();
			if (has_extra_graphics(i))
			{
				int y_t_extra = get_y_extra(i) + (height * (get_cy() / 2));
				int y2_t_extra = y_t_extra + get_cy_extra(i);
				if (y_t_extra < y)
					y = y_t_extra;
				if (y2_t_extra > cy)
					cy = y2_t_extra;
			}
			if (x_t < x)
				x = x_t;
			if (x2_t > cx)
				cx = x2_t;
			if (y_t < y)
				y = y_t;
			if (y2_t > cy)
				cy = y2_t;
			if (bigy < get_y(i))
			{
				bigy = get_y(i);
				bigyval = get_y(i) + get_cy() + (get_height(i) * (get_cy() / 2));
				if (has_extra_graphics(i))
					bigyval -= get_y_extra(i);
			}
		}
	}
	cx -= x;
	cy -= y;
	if (cy < bigyval)
		cy = bigyval;
}

void Ctmp_ts_file::draw(byte* d) const
{
	int global_x, global_y, global_cx, global_cy;
	get_rect(global_x, global_y, global_cx, global_cy);
	memset(d, 0, global_cx * global_cy);
	for (int i = 0; i < get_c_tiles(); i++)
	{
		if (get_index()[i])
		{
			int height = get_height() - get_height(i);
			const byte* r = get_image(i);
			byte* w_line = d + get_x(i) - global_x + global_cx * (get_y(i) - global_y + (height * (get_cy() / 2)));
			int x = get_cx() / 2;
			int cx = 0;
			for (int y = 0; y < get_cy() / 2; y++)
			{
				cx += 4;
				x -= 2;
				memcpy(w_line + x, r, cx);
				r += cx;
				w_line += global_cx;
			}
			for (; y < get_cy(); y++)
			{
				cx -= 4;
				x += 2;
				memcpy(w_line + x, r, cx);
				r += cx;
				w_line += global_cx;
			}
			if (has_extra_graphics(i))
			{
				r += get_cx() * get_cy() / 2;
				w_line = d + get_x_extra(i) - global_x + global_cx * (get_y_extra(i) - global_y + (height * (get_cy() / 2)));
				int cx = get_cx_extra(i);
				int cy = get_cy_extra(i);
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
}

int Ctmp_ts_file::extract_as_pcx(const string& name, const t_palet _palet) const
{
	t_palet palet;
	memcpy(palet, _palet, sizeof(t_palet));
	convert_palet_18_to_24(palet);
	int global_x, global_y, global_cx, global_cy;
	get_rect(global_x, global_y, global_cx, global_cy);
	byte* image = new byte[global_cx * global_cy];
	draw(image);
	byte* d = new byte[global_cx * global_cy * 2];
	int cb_d = pcx_encode(image, d, global_cx, global_cy, 1);
	Cpcx_file_write f;
	int error = f.open_write(name);
	if (!error)
	{
		f.set_size(global_cx, global_cy, 1);
		error = f.write_header();
		if (!error)
			error = f.write_image(d, cb_d);
		if (!error)
			error = f.write_palet(palet);
		f.close();
	}
	delete[] d;
	delete[] image;
	return error;
}

int encode_tile(const byte* s, byte* d)
{
	const byte* r = s;
	byte* w = d;
	int x = 24;
	int cx = 0;
	for (int y = 0; y < 12; y++)
	{
		cx += 4;
		x -= 2;
		memcpy(w, r + x, cx);
		r += 48;
		w += cx;
	}
	for (; y < 23; y++)
	{
		cx -= 4;
		x += 2;
		memcpy(w, r + x, cx);
		r += 48;
		w += cx;
	}
	return w - d;
}

int tmp_ts_file_write(const byte* s, byte* d, int cx, int cy)
{
	if (cx != 48 || cy != 24)
		return 0;
	for (int x = 0; x < cx; x++)
	{
		if (s[x])
			break;
	}
	if (x % 24 != 22)
		return 0;
	x -= 22;
	int cblocks_x = 1; // (cx - x - 24 + 23) / 24;
	int cblocks_y = 1; // (x + 24 + 23) / 24;
	int c_tiles = cblocks_x * cblocks_y;
	byte* w = d;
	t_tmp_ts_header& header = *reinterpret_cast<t_tmp_ts_header*>(w);
	header.cblocks_x = cblocks_x;
	header.cblocks_y = cblocks_y;
	header.cx = 48;
	header.cy = 24;
	w += sizeof(t_tmp_ts_header);
	int* index = reinterpret_cast<int*>(w);
	w += 4 * c_tiles;
	for (int y = 0; y < cblocks_y; y++)
	{
		for (int x = 0; x < cblocks_x; x++)
		{
			*index++ = w - d;
			t_tmp_image_header& image_header = *reinterpret_cast<t_tmp_image_header*>(w);
			image_header.x = 24 * x - 24 * y;
			image_header.y = 12 * x + 12 * y;
			/*
			image_header.x_extra = 0;
			image_header.y_extra = 0;
			image_header.cx_extra = 0;
			image_header.cy_extra = 0;
			*/
			image_header.flags &= ~1;
			image_header.height = 0;
			image_header.terraintype = 0xf;
			image_header.direction = 0;
			image_header.unknown2 = 0;
			w += sizeof(t_tmp_image_header);
			encode_tile(s, w);
			w += 576;
			memset(w, 0, 576);
			w += 576;
		}
	}
	return w - d;
}