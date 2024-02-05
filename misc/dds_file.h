/*
    XCC Utilities and Library
    Copyright (C) 2002  Olaf van der Spek  <olafvdspek@gmail.com>

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

#include <ddraw.h>
#include "cc_file_small.h"
#include "virtual_image.h"

class Cdds_file : public Ccc_file_small
{
public:
	Cvirtual_binary decode() const;
	Cvirtual_image vimage() const;

	bool is_valid() const
	{
		return get_size() >= 4 && *reinterpret_cast<const __int32*>(data()) == ' SDD';
	}

	const DDSURFACEDESC2& ddsd() const
	{
		return *reinterpret_cast<const DDSURFACEDESC2*>(data() + 4);
	}

	int cx() const
	{
		return ddsd().dwWidth;
	}

	int cy() const
	{
		return ddsd().dwHeight;
	}

	const byte* image() const
	{
		return reinterpret_cast<const byte*>(&ddsd() + 1);
	}	
};
