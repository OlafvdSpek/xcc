/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "cc_file.h"
#include "cc_structures.h"
#include "mp3_frame_header.h"

enum t_mpeg_version {mpv_2_5, mpv_reserved, mpv_2, mpv_1};
enum t_mpeg_channel_mode {mpcm_stereo, mpcm_joint_stereo, mpcm_dual_channel, mpcm_single_channel};

const char* mpv_name[];
const char* mpcm_name[];

class Cmp3_file : public Ccc_file  
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
