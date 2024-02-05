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
#include "image_file.h"
#include "palet.h"

class Ccps_file : public Cimage_file<t_cps_header>
{
public:
	void decode(void*) const;
	bool is_valid() const;
	Cvirtual_image vimage() const;

	int cb_pixel() const
	{
		return 1;
	}

	int cx() const override
	{
		return 320;
	}

	int cy() const override
	{
		return 200;
	}

	const byte* get_image() const
	{
		return data() + sizeof(t_cps_header) + header().palet_size;
	}

	const t_palet_entry* palet() const
	{
		return header().palet_size ? reinterpret_cast<const t_palet_entry*>(data() + sizeof(t_cps_header)) : NULL;
	}
};

Cvirtual_binary cps_file_write(const byte* s, const t_palet_entry* palet);
