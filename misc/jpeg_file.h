#pragma once

#include <string>
#include "cc_file_sh.h"
#include "cc_structures.h"
#include "palet.h"
#include "virtual_image.h"

using namespace std;

#pragma comment(lib, "libjpeg.lib")

class Cjpeg_file: public Ccc_file_sh<t_jpeg_header>
{
public:
	int decode(Cvirtual_image& d) const;

	bool is_valid() const
	{
		return !(get_size() < sizeof(t_jpeg_header) || memcmp(header().id, jpeg_id, 4));
	}
};

int jpeg_file_write(Cvirtual_file& f, const byte* image, const t_palet_entry* palet, int cx, int cy, int q = -1);
int jpeg_file_write(const string& name, const byte* image, const t_palet_entry* palet, int cx, int cy, int q = -1);
