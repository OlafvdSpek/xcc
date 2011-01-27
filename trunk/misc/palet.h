#pragma once

#pragma pack(push, 1)

struct t_palet_entry
{
	byte r, g, b;
};

struct t_palet24rgb_entry
{
	byte r, g, b;
};

struct t_palet24bgr_entry
{
	byte b, g, r;
};

union t_palet32entry
{
	struct
	{
		byte r, g, b, a;
	};
	unsigned __int32 v;
};

union t_palet32bgr_entry
{
	struct
	{
		byte b, g, r, a;
	};
	unsigned __int32 v;
};

typedef t_palet_entry t_palet[256];

void apply_rp(byte* d, int cb_d, const byte* rp);
void convert_image_8_to_24(const byte* s, byte* d, int cx, int cy, const t_palet palet);
void convert_image_24_to_8(const byte* s, byte* d, int cx, int cy, const byte* rp);
void convert_image_24_to_8(const byte* s, byte* d, int cx, int cy, const t_palet palet);
void convert_palet_18_to_24(const t_palet s, t_palet d);
void convert_palet_18_to_24(t_palet palet);
void convert_palet_24_to_18(const t_palet s, t_palet d);
void convert_palet_24_to_18(t_palet palet);
void create_downsample_table(const t_palet palet, byte* rp);
void create_rp(const t_palet s1, const t_palet s2, byte* d);
void downsample_image(const t_palet32entry* s, byte* d, int cx, int cy, const byte* rp);
void downsample_image(const t_palet32entry* s, byte* d, int cx, int cy, const t_palet palet);
void upsample_image(const byte* s, t_palet32entry* d, int cx, int cy, const t_palet palet);
int find_color(int r, int g, int b, const t_palet p);
int find_color_t(int r, int g, int b, const t_palet p);

#pragma pack(pop)
