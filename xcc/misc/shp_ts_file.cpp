#include "stdafx.h"
#include "pcx_decode.h"
#include "pcx_file_write.h"
#include "png_file.h"
#include "shp_decode.h"
#include "shp_ts_file.h"
#include "string_conversion.h"
#include "xcc_log.h"

int Cshp_ts_file::extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet _palet, bool combine_shadows) const
{
	t_palet palet;
	memcpy(palet, _palet, sizeof(t_palet));
	convert_palet_18_to_24(palet);
	int error = 0;
	const int global_cx = get_cx();
	const int global_cy = get_cy();
	const int c_images = get_c_images();
	/*
	if (cx != 60 || cy != 48 || c_images != 1)
		return 1;
	*/
	if (combine_shadows && ~c_images & 1)
	{
		bool shadow = false;
		byte* image = new byte[global_cx * global_cy];
		byte* d = new byte[global_cx * global_cy * c_images >> 1];
		byte* w = d;
		for (int i = 0; i < c_images; i++)
		{
			const int cx = get_cx(i);
			const int cy = get_cy(i);
			const byte* r;
			if (is_compressed(i))
			{
				decode3(get_image(i), image, cx, cy);
				r = image;
			}
			else
				r = get_image(i);
			if (!shadow)
			{
				if (i == c_images >> 1)
				{
					shadow = true;
					w = d;
				}
				else
					memset(w, 0, global_cx * global_cy);
			}
			byte* w_start = w;
			w += get_x(i) + global_cx * get_y(i);
			for (int y = 0; y < cy; y++)
			{
				if (shadow)
				{
					for (int x = 0; x < cx; x++)
					{
						if (*r++)
							w[x] = 4;
					}
				}
				else
				{
					memcpy(w, r, cx);
					r += cx;
				}
				w += global_cx;
			}
			if (shadow)
			{
				Cfname t = name;
				t.set_title(name.get_ftitle() + " " + nwzl(4, i - (c_images >> 1)));
				error = ft == ft_png ? png_file_write(t, w_start, palet, global_cx, global_cy) : pcx_file_write(t, w_start, palet, global_cx, global_cy);
				if (error)
					break;
			}
			w = w_start + global_cx * global_cy;
		}
		delete[] d;
		delete[] image;
	}
	else
	{
		byte* image = new byte[global_cx * global_cy];
		byte* s = new byte[global_cx * global_cy];
		for (int i = 0; i < c_images; i++)
		{
			const int cx = get_cx(i);
			const int cy = get_cy(i);
			const byte* r;
			if (is_compressed(i))
			{
				decode3(get_image(i), image, cx, cy);
				r = image;
			}
			else
				r = get_image(i);
			memset(s, 0, global_cx * global_cy);
			byte* w = s + get_x(i) + global_cx * get_y(i);
			for (int y = 0; y < cy; y++)
			{
				memcpy(w, r, cx);
				r += cx;
				w += global_cx;
			}
			// xcc_log::write_line("<tr><td>" + name.get_ftitle() + "</td><td><img src=" + name.get_fname() + "></td></tr>");
			Cfname t = name;
			t.set_title(name.get_ftitle() + " " + nwzl(4, i));
			error = ft == ft_png ? png_file_write(t, s, palet, global_cx, global_cy) : pcx_file_write(t, s, palet, global_cx, global_cy);
			if (error)
				break;
		}
		delete[] s;
		delete[] image;
	}
	return error;
}

int Cshp_ts_file::extract_as_pcx_single(Cvirtual_image& d, const t_palet _palet, bool combine_shadows) const
{
	t_palet palet;
	memcpy(palet, _palet, sizeof(t_palet));
	convert_palet_18_to_24(palet);
	int error = 0;
	const int global_cx = get_cx();
	const int global_cy = get_cy();
	const int c_images = get_c_images();
	const int cblocks_x = 1024 / global_cx;
	const int cblocks_y = (c_images + cblocks_x - 1)/ cblocks_x;
	int cx_s = cblocks_x * global_cx;
	int cy_s = cblocks_y * global_cy;
	if (combine_shadows && ~c_images & 1)
	{
	}
	else
	{
		byte* image = new byte[global_cx * global_cy];
		byte* s = new byte[cx_s * cy_s];
		memset(s, 0, cx_s * cy_s);
		for (int i = 0; i < c_images; i++)
		{
			const int cx = get_cx(i);
			const int cy = get_cy(i);
			const byte* r;
			if (is_compressed(i))
			{
				decode3(get_image(i), image, cx, cy);
				r = image;
			}
			else
				r = get_image(i);
			byte* w = s + i % cblocks_x * global_cx + get_x(i) + cx_s * (i / cblocks_x * global_cx + get_y(i));
			for (int y = 0; y < cy; y++)
			{
				memcpy(w, r, cx);
				r += cx;
				w += cx_s;
			}
		}
		d.load(s, cx_s, cy_s, 1, palet);
		delete[] s;
		delete[] image;
	}
	return error;
}

int Cshp_ts_file::extract_as_pcx_single(const Cfname& name, t_file_type ft, const t_palet _palet, bool combine_shadows) const
{
	t_palet palet;
	memcpy(palet, _palet, sizeof(t_palet));
	convert_palet_18_to_24(palet);
	int error = 0;
	const int global_cx = get_cx();
	const int global_cy = get_cy();
	const int c_images = get_c_images();
	const int cblocks_x = 1024 / global_cx;
	const int cblocks_y = (c_images + cblocks_x - 1)/ cblocks_x;
	int cx_s = cblocks_x * global_cx;
	int cy_s = cblocks_y * global_cy;
	if (combine_shadows && ~c_images & 1)
	{
	}
	else
	{
		byte* image = new byte[global_cx * global_cy];
		byte* s = new byte[cx_s * cy_s];
		memset(s, 0, cx_s * cy_s);
		for (int i = 0; i < c_images; i++)
		{
			const int cx = get_cx(i);
			const int cy = get_cy(i);
			const byte* r;
			if (is_compressed(i))
			{
				decode3(get_image(i), image, cx, cy);
				r = image;
			}
			else
				r = get_image(i);
			byte* w = s + i % cblocks_x * global_cx + get_x(i) + cx_s * (i / cblocks_x * global_cx + get_y(i));
			for (int y = 0; y < cy; y++)
			{
				memcpy(w, r, cx);
				r += cx;
				w += cx_s;
			}
		}
		error = ft == ft_png_single ? png_file_write(name, s, palet, cx_s, cy_s) : pcx_file_write(name, s, palet, cx_s, cy_s);
		delete[] s;
		delete[] image;
	}
	return error;
}
