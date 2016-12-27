#pragma once

#include "cc_file_sh.h"
#include "cc_structures.h"

class Cvoc_file: public Ccc_file_sh<t_voc_header>  
{
public:
	int extract_as_wav(const string& name);

	bool is_valid()
	{
		const t_voc_header& h = header();
		return !(sizeof(t_voc_header) > get_size() ||
			strncmp(h.id, voc_id, strlen(voc_id)) ||
			h.offset + 4 + sizeof(t_voc_sound_data_header) > get_size() ||
			// header.version != 0x1129010a ||
			get_sound_data_header()->compression);
	}

	const t_voc_sound_data_header* get_sound_data_header() const
	{
		return reinterpret_cast<const t_voc_sound_data_header*>(data() + header().offset + 4);
	}

	const byte* get_sound_data() const
	{
		return reinterpret_cast<const byte*>(get_sound_data_header() + 1);
	}

	int get_c_samples() const
	{
		const byte* r = data() + header().offset + 1;
		return (r[0] | r[1] << 8 | r[2] << 16) - sizeof(t_voc_sound_data_header);
	}

	int get_samplerate() const
	{
		return 1000000 / (256 - get_sound_data_header()->samplerate);
	}
};
