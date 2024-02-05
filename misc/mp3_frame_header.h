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

class Cmp3_frame_header  
{
public:
	Cmp3_frame_header();
	Cmp3_frame_header(int v);

	int bitrate() const
	{
		return m_bitrate;
	}

	int channel_mode() const
	{
		return m_channel_mode;
	}

	bool copyright() const
	{
		return m_copyright;
	}

	bool crc() const
	{
		return m_crc;
	}

	int emphasis() const
	{
		return m_emphasis;
	}

	int layer() const
	{
		return m_layer;
	}

	int mode_extension() const
	{
		return m_mode_extension;
	}

	bool original() const
	{
		return m_original;
	}

	bool padding() const
	{
		return m_padding;
	}

	int samplerate() const
	{
		return m_samplerate;
	}

	bool valid() const
	{
		return m_valid;
	}

	int version() const
	{
		return m_version;
	}
private:
	int m_bitrate;
	int m_channel_mode;
	bool m_copyright;
	bool m_crc;
	int m_emphasis;
	int m_layer;
	int m_mode_extension;
	bool m_original;
	bool m_padding;
	int m_samplerate;
	bool m_valid;
	int	m_version;
};
