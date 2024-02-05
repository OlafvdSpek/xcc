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

class Cima_adpcm_wav_decode  
{
public:
	Cima_adpcm_wav_decode();
	void load(const byte* s, int cb_s, int c_channels, int chunk_size);
	~Cima_adpcm_wav_decode();
	
	int cb_data() const
	{
		return mcb_data;
	}

	int c_samples() const
	{
		return mc_samples;
	}

	const short* data() const
	{
		return m_data;
	}
private:
	short* m_data;
	int mcb_data;
	int mc_samples;
};
