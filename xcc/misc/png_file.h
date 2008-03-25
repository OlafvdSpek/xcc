#pragma once

#include <string>
#include "cc_file_sh.h"
#include "cc_structures.h"
#include "palet.h"
#include "virtual_image.h"

using namespace std;

#pragma comment(lib, "libpng.lib")

class Cpng_file: public Ccc_file_sh<t_png_header>
{
public:
	int decode(Cvirtual_image& d) const;

	bool is_valid() const
	{
		return !(get_size() < sizeof(t_png_header) || memcmp(get_header(), png_id, sizeof(t_png_header)));
	}
};

int png_file_write(Cvirtual_file& f, const byte* image, const t_palet_entry* palet, int cx, int cy);
int png_file_write(const string& name, const byte* image, const t_palet_entry* palet, int cx, int cy);
