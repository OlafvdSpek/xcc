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

#include <vartypes.h>

class Cima_adpcm_wav_encode  
{
public:
	void load(const short* s, int cb_s, int c_channels);

	~Cima_adpcm_wav_encode()
	{
		delete[] m_data;
	}

	int cb_data() const
	{
		return mcb_data;
	}

	int c_samples() const
	{
		return mc_samples;
	}

	const byte* data() const
	{
		return m_data;
	}
private:
	byte* m_data {};
	int mcb_data;
	int mc_samples;
};
