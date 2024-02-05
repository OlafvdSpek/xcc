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

#include "cc_structures.h"
#include "file32.h"
#include "palet.h"
#include "virtual_file.h"

class Cpcx_file_write : public Cfile32  
{
public:
	void set_size(int cx, int cy, int c_planes);
	int write_header();
	int write_image(const void* data, int size);
	int write_palet(const t_palet palet);
private:
	int m_cx;
	int m_cy;
	int mc_planes;
};

Cvirtual_binary pcx_file_write(const byte* image, const t_palet_entry* palet, int cx, int cy);
void pcx_file_write(Cvirtual_file& f, const byte* image, const t_palet_entry* palet, int cx, int cy);
int pcx_file_write(const string& name, const byte* image, const t_palet_entry* palet, int cx, int cy);
