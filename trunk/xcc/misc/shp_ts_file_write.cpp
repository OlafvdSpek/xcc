#include "stdafx.h"
#include "shp_ts_file_write.h"

#include "shp_decode.h"
#include "shp_ts_file.h"

static void copy_image(const byte* s, byte* d, int s_x, int s_y, int s_cx, int d_cx, int d_cy)
{
	const byte* r = s + s_x + s_cx * s_y;
	byte* w = d;
	while (d_cy--)
	{
		memcpy(w, r, d_cx);
		r += s_cx;
		w += d_cx;
	}
}

Cvirtual_binary shp_ts_file_write(const byte* s, int global_cx, int global_cy, int c_images, bool enable_compression)
{
	Cvirtual_binary d;
	const byte* r = s;
	byte* w = d.write_start(Cshp_ts_file::get_max_size(global_cx, global_cy, c_images));
	t_shp_ts_header& header = *reinterpret_cast<t_shp_ts_header*>(w);
	header.zero = 0;
	header.cx = global_cx;
	header.cy = global_cy;
	header.c_images = c_images;
	w += sizeof(t_shp_ts_header);
	byte* w1 = w + c_images * sizeof(t_shp_ts_image_header);
	byte* t = new byte[global_cx * global_cy];
	byte* u = new byte[(global_cx + 1) * global_cy * 2];
	for (int i = 0; i < c_images; i++)
	{
		w1 += d.data() - w1 & 7;
		int x = 0;
		int y = 0;
		int cx = 0;
		int cy = 0;
		const byte* r0 = r;
		const byte* r1 = r + global_cx * global_cy;
		bool empty0, empty1;
		empty0 = empty1 = true;
		for (int yl = 0; yl < global_cy; yl++)
		{
			for (int xl = 0; xl < global_cx; xl++)
			{
				if (empty0 && *r0++)
				{
					empty0 = false;
					y = yl;
				}
				if (empty1 && *--r1)
				{
					empty1 = false;
					cy = global_cy - yl;
				}
			}
		}
		empty0 = empty1 = true;
		for (int xl = 0; xl < global_cx; xl++)
		{
			for (int yl = y; yl < cy; yl++)
			{
				const byte* r0 = r + xl + global_cx * yl;
				const byte* r1 = r + (global_cx - xl - 1) + global_cx * yl;
				if (empty0 && *r0)
				{
					empty0 = false;
					x = xl;
				}
				if (empty1 && *r1)
				{
					empty1 = false;
					cx = global_cx - xl;
				}
			}
		}
		cx -= x;
		cy -= y;
		t_shp_ts_image_header& image_header = *reinterpret_cast<t_shp_ts_image_header*>(w);
		image_header.x = x;
		image_header.y = y;
		image_header.cx = cx;
		image_header.cy = cy;
		image_header.compression = 0;
		image_header.unknown = c_images & 1 || i < c_images / 2 ? 0x70000 : 0;
		image_header.zero = 0;
    image_header.offset = w1 - d.data();
		w += sizeof(t_shp_ts_image_header);
		if (cy)
		{
			copy_image(r, t, x, y, global_cx, cx, cy);
			int cb_u = enable_compression ? encode3(t, u, cx, cy) : INT_MAX;
			if (cb_u < cx * cy)
			{
				image_header.compression = 3;
				memcpy(w1, u, cb_u);
				w1 += cb_u;
			}
			else
			{
				memcpy(w1, t, cx * cy);
				w1 += cx * cy;
			}
		}
		else
			image_header.offset = 0;
		r += global_cx * global_cy;
	}
	delete[] u;
	delete[] t;
	d.size(w1 - d.data());
	return d;
}
