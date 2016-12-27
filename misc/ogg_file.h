#pragma once

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "virtual_audio.h"

#pragma comment(lib, "libogg_static.lib")
#pragma comment(lib, "libvorbis_static.lib")
#pragma comment(lib, "libvorbisfile_static.lib")

class Cogg_file: public Ccc_file_sh<t_ogg_header>
{
public:
	bool is_valid() const
	{
		return !(get_size() < sizeof(t_ogg_header) || memcmp(header().id, ogg_id, 4));
	}

	int decode(Cvirtual_audio& audio);
	int get_c_channels();
	int get_c_samples();
	int get_samplerate();
};
