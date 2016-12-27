#pragma once

#include "cc_file.h"
#include "cc_structures.h"
#include "mp3_frame_header.h"

enum t_mpeg_version {mpv_2_5, mpv_reserved, mpv_2, mpv_1};
enum t_mpeg_channel_mode {mpcm_stereo, mpcm_joint_stereo, mpcm_dual_channel, mpcm_single_channel};

const char* mpv_name[];
const char* mpcm_name[];

class Cmp3_file: public Ccc_file  
{
public:
	Cmp3_file():
	    Ccc_file(false)
	{
	}

	bool is_valid()
	{
		if (4 > get_size())
			return false;
		return m_header.valid();
	}

	const Cmp3_frame_header& header() const
	{
		return m_header;
	}

    int post_open()
	{
		int v;
		int error = read(&v, 4);
		m_header = reverse(v);
		return error;
	}
private:
	Cmp3_frame_header m_header;
};
