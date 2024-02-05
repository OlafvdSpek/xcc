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

#include "xcc_ds.h"

class Cxcc_dsb  
{
public:
	void destroy();
	bool is_available();	
	int lock(int pos, int size, void** p1, DWORD* s1, void** p2, DWORD* s2);
	int unlock(void* p1, int s1, void* p2, int s2);
	int set_samplerate(int samplerate);
	int set_pos(int pos);
	int stop();
	int play(int flags);
	int create(Cxcc_ds &ds, int size, int c_channels, int samplerate, int cbits_sample, int flags);
	void handle_error(const string &s) const;
	const LPDIRECTSOUNDBUFFER get_p() const;
private:
	Cxcc_ds* pds;
	LPDIRECTSOUNDBUFFER pdsb = NULL;
};
