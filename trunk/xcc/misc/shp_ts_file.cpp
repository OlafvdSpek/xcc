#include "stdafx.h"
#include "image_file.h"
#include "shp_decode.h"
#include "shp_ts_file.h"
#include "string_conversion.h"
#include "xcc_log.h"

int get_ofs(int x, int y, int cx, int cy)
{
	return x + cx * y;
}

int Cshp_ts_file::extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet _palet, bool combine_shadows) const
{
	t_palet palet;
	convert_palet_18_to_24(_palet, palet);
	int error = 0;
	const int global_cx = get_cx();
	const int global_cy = get_cy();
	const int c_images = get_c_images();
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
				error = image_file_write(t, ft, w_start, palet, global_cx, global_cy);
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
			error = image_file_write(t, ft, s, palet, global_cx, global_cy);
			if (error)
				break;
		}
		delete[] s;
		delete[] image;
	}
	return error;
}

int Cshp_ts_file::extract_as_pcx(Cvirtual_image& d, const t_palet _palet, bool combine_shadows) const
{
	t_palet palet;
	convert_palet_18_to_24(_palet, palet);
	int error = 0;
	const int global_cx = get_cx();
	const int global_cy = get_cy();
	int c_images = get_c_images();
	if (combine_shadows && c_images & 1)
		error = 0x100;
	else
	{
		if (combine_shadows)
			c_images >>= 1;
		int cy_s = c_images * global_cy;
		byte* image = new byte[global_cx * global_cy];
		byte* s = new byte[global_cx * cy_s];
		memset(s, 0, global_cx * cy_s);
		if (combine_shadows)
		{
			c_images <<= 1;
			bool shadow = false;
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
				if (!shadow && i == c_images >> 1)
					shadow = true;
				byte* w = s + get_x(i) + global_cx * (global_cy * i + get_y(i));
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
			}
		}
		else
		{
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
				byte* w = s + get_x(i) + global_cx * (global_cy * i + get_y(i));
				for (int y = 0; y < cy; y++)
				{
					memcpy(w, r, cx);
					r += cx;
					w += global_cx;
				}
			}
		}
		d.load(s, global_cx, cy_s, 1, palet);
		delete[] s;
		delete[] image;
	}
	return error;
}

int Cshp_ts_file::extract_as_pcx_single(Cvirtual_image& d, const t_palet _palet, bool combine_shadows) const
{
	t_palet palet;
	convert_palet_18_to_24(_palet, palet);
	int error = 0;
	const int global_cx = get_cx();
	const int global_cy = get_cy();
	int c_images = get_c_images();
	if (c_images & 1)
		combine_shadows = false;
	if (combine_shadows)
		c_images >>= 1;
	const int cblocks_x = min(c_images, 1024 / global_cx);
	const int cblocks_y = (c_images + cblocks_x - 1) / cblocks_x;
	int cx_s = cblocks_x * global_cx;
	int cy_s = cblocks_y * global_cy;
	byte* image = new byte[global_cx * global_cy];
	byte* s = new byte[cx_s * cy_s];
	memset(s, 0, cx_s * cy_s);
	if (combine_shadows)
	{
		c_images <<= 1;
		bool shadow = false;
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
			if (!shadow && i == c_images >> 1)
				shadow = true;
			int j = i % (c_images >> 1);
			// byte* w = s + j % cblocks_x * global_cx + get_x(i) + cx_s * (j / cblocks_x * global_cx + get_y(i));
			byte* w = s + get_ofs(j % cblocks_x * global_cx + get_x(i), j / cblocks_x * global_cy + get_y(i), cx_s, cy_s);
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
				w += cx_s;
			}
		}
	}
	else
	{
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
			// byte* w = s + i % cblocks_x * global_cx + get_x(i) + cx_s * (i / cblocks_x * global_cy + get_y(i));
			byte* w = s + get_ofs(i % cblocks_x * global_cx + get_x(i), i / cblocks_x * global_cy + get_y(i), cx_s, cy_s);
			for (int y = 0; y < cy; y++)
			{
				memcpy(w, r, cx);
				r += cx;
				w += cx_s;
			}
		}
	}
	d.load(s, cx_s, cy_s, 1, palet);
	delete[] s;
	delete[] image;
	return error;
}

int Cshp_ts_file::extract_as_pcx_single(const Cfname& name, t_file_type ft, const t_palet palet, bool combine_shadows) const
{
	Cvirtual_image image;
	int error = extract_as_pcx_single(image, palet, combine_shadows);
	if (!error)
		error = image.save(name, ft);
	return error;
}

void shp_split_frames(Cvirtual_image& image, int cblocks_x, int cblocks_y)
{
	int cx = image.cx() / cblocks_x;
	int cy = image.cy() / cblocks_y;
	int cx_d = image.cx() / cblocks_x;
	int cy_d = image.cy() * cblocks_x;
	byte* d = new byte[cx_d * cy_d];
	byte* w = d;
	const byte* r_line = image.image();
	for (int yb = 0; yb < cblocks_y; yb++)
	{
		for (int xb = 0; xb < cblocks_x; xb++)
		{
			const byte* r = r_line + cx * xb;
			for (int y = 0; y < cy; y++)
			{
				memcpy(w, r, cx);
				r += image.cx();
				w += cx_d;
			}
		}
		r_line += image.cx() * cy;
	}
	image.load(d, cx_d, cy_d, image.cb_pixel(), image.palet());
	delete[] d;
}

void shp_split_shadows(Cvirtual_image& image)
{
	int cx = image.cx();
	int cy = image.cy();
	int count = cx * cy;
	byte* d = new byte[count << 1];
	memcpy(d, image.image(), count); 
	byte* r = d;
	byte* w = d + count;
	while (count--)
	{
		byte& v = *r++;
		if (v == 4)
		{
			v = 0;
			*w++ = 1;
		}
		else
			*w++ = 0;
	}
	image.load(d, cx, cy << 1, image.cb_pixel(), image.palet());
	delete[] d;
}

/*
void shp_xor_decode_frames(Cvirtual_image& image, int c_frames)
{
	int cx = image.cx();
	int cy = image.cy() / c_frames;
	int count = cx * cy * (c_frames - 1);
	const byte* r = image.image();
	byte* w = image.image_edit() + cx * cy;
	while (count--)
	{
		*w++ ^= *r++;
	}
}

void shp_xor_encode_frames(Cvirtual_image& image, int c_frames)
{
	int cx = image.cx();
	int cy = image.cy() / c_frames;
	int count = cx * cy * c_frames;
	byte* w = image.image_edit() + count;
	count -= cx * cy;
	const byte* r = image.image() + count;
	while (count--)
	{
		*--w ^= *--r;
	}
}
*/

static int get_left_margin(const byte* r, int cx)
{
	int c = 0;
	while (!*r++ && cx--)
		c++;
	return c;
}

static int get_right_margin(const byte* r, int cx)
{
	int c = 0;
	r += cx;
	while (!*--r && cx--)
		c++;
	return c;
}

static int encode4_line(const byte* r, byte* d, int cx)
{
	const byte* s_end = r + cx;
	byte* w = d;
	while (r < s_end)
	{
		int v = *w++ = *r++;
		if (!v)
		{
			int c = get_run_length(r - 1, s_end) - 1;
			if (c > 0xff)
				c = 0xff;
			r += c;
			*w++ = c;
		}
	}
	return w - d;
}

static int decode4_line(const byte* s, byte* d, int cx)
{
	const byte* r = s;
	byte* w = d;
	while (cx--)
	{
		int v = *w++ = *r++;
		if (!v)
		{
			int c = *r++;
			memset(w, 0, c);
			cx -= c;
			w += c;
		}
	}
	return r - s;
}

static int encode4(const byte* s, byte* d, int cx, int cy)
{
	const byte* s_end = s + cx * cy;
	const byte* r = s;
	byte* w = d;
	for (int y = 0; y < cy; y++)
	{
		int lm = min(get_left_margin(r, cx), 0xff);
		int rm = min(get_right_margin(r, cx - lm), 0xff);
		*w++ = lm;
		*w++ = rm;
		w += encode4_line(r + lm, w, cx - lm - rm);
		r += cx;
	}
	return w - d;
}

static int decode4(const byte* s, byte* d, int cx, int cy)
{
	const byte* r = s;
	byte* w = d;
	for (int y = 0; y < cy; y++)
	{
		int lm = *r++;
		int rm = *r++;
		memset(w, 0, lm);
		w += lm;
		r += decode4_line(r, w, cx - lm - rm);
		w += cx - lm - rm;
		memset(w, 0, rm);
		w += rm;
	}
	return r - s;
}

struct t_shp4_header
{
	unsigned __int16 cx;
	unsigned __int16 cy;
	unsigned __int16 c_frames;
};

struct t_shp4_frame_header
{
	unsigned __int8 lm;
	unsigned __int8 rm;
	unsigned __int8 tm;
	unsigned __int8 bm;
};

int shp_encode4(const Cshp_ts_file& f, byte* d)
{
	const int global_cx = f.get_cx();
	const int global_cy = f.get_cy();
	const int c_frames = f.get_c_images();

	byte* w = d;
	t_shp4_header& header = *reinterpret_cast<t_shp4_header*>(w);
	header.cx = global_cx;
	header.cy = global_cy;
	header.c_frames = c_frames;
	w += sizeof(t_shp4_header);

	for (int i = 0; i < c_frames; i++)
	{
		const t_shp_ts_image_header& image_header = *f.get_image_header(i);

		const int cx = image_header.cx;
		const int cy = image_header.cy;

		t_shp4_frame_header& frame_header = *reinterpret_cast<t_shp4_frame_header*>(w);
		if (image_header.cx || image_header.cy)
		{
			frame_header.lm = image_header.x;
			frame_header.tm = image_header.y;
		}
		else
		{
			frame_header.lm = min(global_cx, 0xff);
			frame_header.tm = min(global_cy, 0xff);
		}
		frame_header.rm = global_cx - frame_header.lm - cx;
		frame_header.bm = global_cy - frame_header.tm - cy;
		assert(global_cx - frame_header.lm - cx < 0x100);
		assert(global_cy - frame_header.tm - cy < 0x100);
		w += sizeof(t_shp4_frame_header);

		const byte* r;
		byte* image;

		if (f.is_compressed(i))
		{
			image = new byte[cx * cy];
			decode3(f.get_image(i), image, cx, cy);
			r = image;
		}
		else
		{
			image = NULL;
			r = f.get_image(i);
		}

		w += encode4(r, w, cx, cy);

		delete[] image;
	}
	return w - d;
}

/*
int shp_decode4(const byte* s, byte* d)
{
	bool enable_compression = true;
	const byte* r = s;
	byte* w = d;
	const t_shp4_header& s_header = *reinterpret_cast<const t_shp4_header*>(r);
	const int global_cx = s_header.cx;
	const int global_cy = s_header.cy;
	const int c_frames = s_header.c_frames;
	r += sizeof(t_shp4_header);
	t_shp_ts_header& header = *reinterpret_cast<t_shp_ts_header*>(w);
	header.zero = 0;
	header.cx = global_cx;
	header.cy = global_cy;
	header.c_images = c_frames;
	w += sizeof(t_shp_ts_header);
	byte* w1 = d + sizeof(t_shp_ts_header) + c_frames * sizeof(t_shp_ts_image_header);
	byte* t = new byte[global_cx * global_cy];
	byte* u = new byte[(global_cx + 1) * global_cy * 2];
	for (int i = 0; i < c_frames; i++)
	{
		const t_shp4_frame_header& frame_header = *reinterpret_cast<const t_shp4_frame_header*>(r);
		int x = frame_header.lm;
		int y = frame_header.tm;
		int cx = global_cx - x - frame_header.rm;
		int cy = global_cy - y - frame_header.bm;
		r += sizeof(t_shp4_frame_header);
		t_shp_ts_image_header& image_header = *reinterpret_cast<t_shp_ts_image_header*>(w);
		image_header.x = x;
		image_header.y = y;
		image_header.cx = cx;
		image_header.cy = cy;
		image_header.compression = 0;
		image_header.unknown = 0;
		image_header.zero = 0;
		image_header.offset = w1 - d;
		w += sizeof(t_shp_ts_image_header);
		if (cy)
		{
			r += decode4(r, t, cx, cy);
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
		// w1 = d + (w1 - d + 7 & ~7);
	}
	delete[] u;
	delete[] t;
	return w1 - d;
}
*/

void shp_decode4(const byte* s, Cvirtual_file& f)
{
	bool enable_compression = true;
	const byte* r = s;
	const t_shp4_header& s_header = *reinterpret_cast<const t_shp4_header*>(r);
	const int global_cx = s_header.cx;
	const int global_cy = s_header.cy;
	const int c_frames = s_header.c_frames;
	r += sizeof(t_shp4_header);
	byte* d = new byte[Cshp_ts_file::get_max_size(global_cx, global_cy, c_frames)];
	byte* w = d;
	t_shp_ts_header& header = *reinterpret_cast<t_shp_ts_header*>(w);
	header.zero = 0;
	header.cx = global_cx;
	header.cy = global_cy;
	header.c_images = c_frames;
	w += sizeof(t_shp_ts_header);
	byte* w1 = d + sizeof(t_shp_ts_header) + c_frames * sizeof(t_shp_ts_image_header);
	byte* t = new byte[global_cx * global_cy];
	byte* u = new byte[(global_cx + 1) * global_cy * 2];
	for (int i = 0; i < c_frames; i++)
	{
		const t_shp4_frame_header& frame_header = *reinterpret_cast<const t_shp4_frame_header*>(r);
		int x = frame_header.lm;
		int y = frame_header.tm;
		int cx = global_cx - x - frame_header.rm;
		int cy = global_cy - y - frame_header.bm;
		r += sizeof(t_shp4_frame_header);
		t_shp_ts_image_header& image_header = *reinterpret_cast<t_shp_ts_image_header*>(w);
		image_header.x = x;
		image_header.y = y;
		image_header.cx = cx;
		image_header.cy = cy;
		image_header.compression = 0;
		image_header.unknown = 0;
		image_header.zero = 0;
		image_header.offset = w1 - d;
		w += sizeof(t_shp_ts_image_header);
		if (cy)
		{
			r += decode4(r, t, cx, cy);
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
		w1 = d + (w1 - d + 7 & ~7);
	}
	delete[] u;
	delete[] t;
	int cb_d = w1 - d;
	f.write(d, cb_d);
	delete[] d;
}
