#pragma once

#include <ddraw.h>

class Cddpf_conversion
{
public:
	int get_color(int a, int r, int g, int b);
	int get_color(int r, int g, int b);
	int get_color(int v);
	void set_pf(const DDPIXELFORMAT& pf);
private:
	int a_shift, r_shift, g_shift, b_shift;
	int a_size, r_size, g_size, b_size;
};