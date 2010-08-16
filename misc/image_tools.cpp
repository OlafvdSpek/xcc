#include "stdafx.h"
#include <math.h>
#include "image_tools.h"

static int get_pixel(const byte* s, int x, int y, int cx, int c_planes)
{
	return s[c_planes * (x + cx * y)];
}

static int get_color_bicubic_x(const byte* s, float x_l, float x_r, int y, int cx, int cy, int c_planes)
{
	double d;
	double fx_l = modf(x_l, &d);
	int ix_l = d;
	double fx_r = modf(x_r, &d);
	int ix_r = d;
	double rs = (1 - fx_l) * get_pixel(s, ix_l, y, cx, c_planes);
	double rc = 1 - fx_l;
	for (int x = ix_l + 1; x < ix_r; x++)
	{
		rs += get_pixel(s, ix_l, y, cx, c_planes);
		rc += 1;
	}
	rs += fx_r * get_pixel(s, ix_r, y, cx, c_planes);
	rc += fx_r;
	return rs / rc;
}

static int get_color_bicubic(const byte* s, float x_l, float x_r, float y_t, float y_b, int cx, int cy, int c_planes)
{
	double d;
	double fy_t = modf(y_t, &d);
	int iy_t = d;
	double fy_b = modf(y_b, &d);
	int iy_b = d;
	double rs = (1 - fy_t) * get_color_bicubic_x(s, x_l, x_r, iy_t, cx, cy, c_planes);
	double rc = 1 - fy_t;
	for (int y = iy_t + 1; y < iy_b; y++)
	{
		rs += get_color_bicubic_x(s, x_l, x_r, y, cx, cy, c_planes);
		rc += 1;
	}
	if (iy_b < cy)
	{
		rs += fy_b * get_color_bicubic_x(s, x_l, x_r, iy_b, cx, cy, c_planes);
		rc += fy_b;
	}
	return rs / rc;
}

void resize_image_down(const byte* s, byte* d, int cx, int cy, int c_planes, int cx_d, int cy_d)
{
	byte* w = d;
	float x_scale = static_cast<float>(cx_d) / cx;
	float y_scale = static_cast<float>(cy_d) / cy;
	for (int y = 0; y < cy_d; y++)
	{
		for (int x = 0; x < cx_d; x++)
		{
			float x_l = static_cast<float>(x * cx) / cx_d;
			float y_t = static_cast<float>(y * cy) / cy_d;
			float x_r = x_l + 1 / x_scale;
			float y_b = y_t + 1 / y_scale;
			for (int p = 0; p < c_planes; p++)
				*w++ = get_color_bicubic(s + p, x_l, x_r, y_t, y_b, cx, cy, c_planes);
		}
	}
}

static int get_color_bilinear_x(const byte* s, float x, float y, int cx, int cy, int c_planes)
{
	double d;
	double fx = modf(x, &d);
	int ix = d;
	double fy = modf(y, &d);
	int iy = d;
	const byte* r = s + c_planes * (ix + cx * iy);
	int tl = r[0];
	int tr = r[c_planes];
	return (1 - fy) * ((1 - fx) * tl + fx * tr);
}

static int get_color_bilinear_y(const byte* s, float x, float y, int cx, int cy, int c_planes)
{
	double d;
	double fx = modf(x, &d);
	int ix = d;
	double fy = modf(y, &d);
	int iy = d;
	const byte* r = s + c_planes * (ix + cx * iy);
	int tl = r[0];
	int bl = r[cx * c_planes];
	return (1 - fy) * (1 - fx) * tl +  fy * (1 - fx) * bl;
}

static int get_color_bilinear(const byte* s, float x, float y, int cx, int cy, int c_planes)
{
	double d;
	double fx = modf(x, &d);
	int ix = d;
	double fy = modf(y, &d);
	int iy = d;
	const byte* r = s + c_planes * (ix + cx * iy);
	int tl = r[0];
	int tr = r[c_planes];
	if (iy + 1 < cy)
	{
		r += cx * c_planes;
		int bl = r[0];
		int br = r[c_planes];
		return (1 - fy) * ((1 - fx) * tl + fx * tr) +  fy * ((1 - fx) * bl + fx * br);
	}
	return (1 - fy) * ((1 - fx) * tl + fx * tr);
}

void resize_image_up(const byte* s, byte* d, int cx, int cy, int c_planes, int cx_d, int cy_d)
{
	byte* w = d;
	for (int y = 0; y < cy_d - 1; y++)
	{
		for (int x = 0; x < cx_d; x++)
		{
			for (int p = 0; p < c_planes; p++)
				*w++ = get_color_bilinear(s + p, static_cast<float>(x * (cx - 1)) / (cx_d - 1), static_cast<float>(y * (cy - 1)) / (cy_d - 1), cx, cy, c_planes);
		}
	}
	for (int x = 0; x < cx_d; x++)
	{
		for (int p = 0; p < c_planes; p++)
			*w++ = get_color_bilinear_x(s + p, static_cast<float>(x * (cx - 1)) / (cx_d - 1), cy - 1, cx, cy, c_planes);
	}
}

static t_palet32entry get_pixel(const t_palet32entry* s, int x, int y, int cx)
{
	return s[x + cx * y];
}

static t_palet32entry get_color_bicubic_x(const t_palet32entry* s, float x_l, float x_r, int y, int cx, int cy)
{
	double d;
	double fx_l = modf(x_l, &d);
	int ix_l = d;
	double fx_r = modf(x_r, &d);
	int ix_r = d;
	double rs = (1 - fx_l) * get_pixel(s, ix_l, y, cx).r;
	double gs = (1 - fx_l) * get_pixel(s, ix_l, y, cx).g;
	double bs = (1 - fx_l) * get_pixel(s, ix_l, y, cx).b;
	double as = (1 - fx_l) * get_pixel(s, ix_l, y, cx).a;
	double rc = 1 - fx_l;
	for (int x = ix_l + 1; x < ix_r; x++)
	{
		rs += get_pixel(s, ix_l, y, cx).r;
		gs += get_pixel(s, ix_l, y, cx).g;
		bs += get_pixel(s, ix_l, y, cx).b;
		as += get_pixel(s, ix_l, y, cx).a;
		rc += 1;
	}
	rs += fx_r * get_pixel(s, ix_r, y, cx).r;
	gs += fx_r * get_pixel(s, ix_r, y, cx).g;
	bs += fx_r * get_pixel(s, ix_r, y, cx).b;
	as += fx_r * get_pixel(s, ix_r, y, cx).a;
	rc += fx_r;
	t_palet32entry e;
	e.r = rs / rc;
	e.g = gs / rc;
	e.b = bs / rc;
	e.a = as / rc;
	return e;
}

static t_palet32entry get_color_bicubic(const t_palet32entry* s, float x_l, float x_r, float y_t, float y_b, int cx, int cy)
{
	double d;
	double fy_t = modf(y_t, &d);
	int iy_t = d;
	double fy_b = modf(y_b, &d);
	int iy_b = d;
	double rs = (1 - fy_t) * get_color_bicubic_x(s, x_l, x_r, iy_t, cx, cy).r;
	double gs = (1 - fy_t) * get_color_bicubic_x(s, x_l, x_r, iy_t, cx, cy).g;
	double bs = (1 - fy_t) * get_color_bicubic_x(s, x_l, x_r, iy_t, cx, cy).b;
	double as = (1 - fy_t) * get_color_bicubic_x(s, x_l, x_r, iy_t, cx, cy).a;
	double rc = 1 - fy_t;
	for (int y = iy_t + 1; y < iy_b; y++)
	{
		rs += get_color_bicubic_x(s, x_l, x_r, y, cx, cy).r;
		gs += get_color_bicubic_x(s, x_l, x_r, y, cx, cy).g;
		bs += get_color_bicubic_x(s, x_l, x_r, y, cx, cy).b;
		as += get_color_bicubic_x(s, x_l, x_r, y, cx, cy).a;
		rc += 1;
	}
	if (iy_b < cy)
	{
		rs += fy_b * get_color_bicubic_x(s, x_l, x_r, iy_b, cx, cy).r;
		gs += fy_b * get_color_bicubic_x(s, x_l, x_r, iy_b, cx, cy).g;
		bs += fy_b * get_color_bicubic_x(s, x_l, x_r, iy_b, cx, cy).b;
		as += fy_b * get_color_bicubic_x(s, x_l, x_r, iy_b, cx, cy).a;
		rc += fy_b;
	}
	t_palet32entry e;
	e.r = rs / rc;
	e.g = gs / rc;
	e.b = bs / rc;
	e.a = as / rc;
	return e;
}

void resize_image_down(const t_palet32entry* s, t_palet32entry* d, int cx, int cy, int cx_d, int cy_d)
{
	t_palet32entry* w = d;
	float x_scale = static_cast<float>(cx_d) / cx;
	float y_scale = static_cast<float>(cy_d) / cy;
	for (int y = 0; y < cy_d; y++)
	{
		for (int x = 0; x < cx_d; x++)
		{
			float x_l = static_cast<float>(x * cx) / cx_d;
			float y_t = static_cast<float>(y * cy) / cy_d;
			float x_r = x_l + 1 / x_scale;
			float y_b = y_t + 1 / y_scale;
			*w++ = get_color_bicubic(s, x_l, x_r, y_t, y_b, cx, cy);
		}
	}
}

static t_palet32entry get_color_bilinear_x(const t_palet32entry* s, float x, float y, int cx, int cy)
{
	double d;
	double fx = modf(x, &d);
	int ix = d;
	double fy = modf(y, &d);
	int iy = d;
	const t_palet32entry* r = s + ix + cx * iy;
	t_palet32entry tl = r[0];
	t_palet32entry tr = r[1];
	t_palet32entry e;
	e.r = (1 - fy) * ((1 - fx) * tl.r + fx * tr.r);
	e.g = (1 - fy) * ((1 - fx) * tl.g + fx * tr.g);
	e.b = (1 - fy) * ((1 - fx) * tl.b + fx * tr.b);
	e.a = (1 - fy) * ((1 - fx) * tl.a + fx * tr.a);
	return e;
}

static t_palet32entry get_color_bilinear(const t_palet32entry* s, float x, float y, int cx, int cy)
{
	double d;
	double fx = modf(x, &d);
	int ix = d;
	double fy = modf(y, &d);
	int iy = d;
	const t_palet32entry* r = s + ix + cx * iy;
	t_palet32entry tl = r[0];
	t_palet32entry tr = r[1];
	r += cx;
	t_palet32entry bl = r[0];
	t_palet32entry br = r[1];
	t_palet32entry e;
	e.r = (1 - fy) * ((1 - fx) * tl.r + fx * tr.r) +  fy * ((1 - fx) * bl.r + fx * br.r);
	e.g = (1 - fy) * ((1 - fx) * tl.g + fx * tr.g) +  fy * ((1 - fx) * bl.g + fx * br.g);
	e.b = (1 - fy) * ((1 - fx) * tl.b + fx * tr.b) +  fy * ((1 - fx) * bl.b + fx * br.b);
	e.a = (1 - fy) * ((1 - fx) * tl.a + fx * tr.a) +  fy * ((1 - fx) * bl.a + fx * br.a);
	return e;
}

void resize_image_up(const t_palet32entry* s, t_palet32entry* d, int cx, int cy, int cx_d, int cy_d)
{
	t_palet32entry* w = d;
	for (int y = 0; y < cy_d - 1; y++)
	{
		for (int x = 0; x < cx_d; x++)
		{
			*w++ = get_color_bilinear(s, static_cast<float>(x * (cx - 1)) / (cx_d - 1), static_cast<float>(y * (cy - 1)) / (cy_d - 1), cx, cy);
		}
	}
	for (int x = 0; x < cx_d; x++)
	{
		*w++ = get_color_bilinear_x(s, static_cast<float>(x * (cx - 1)) / (cx_d - 1), cy - 1, cx, cy);
	}
}
