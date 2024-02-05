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

#include "mix_file.h"
#include "xcc_level.h"

class Cxcc_mixs  
{
public:
	static int open();
	static Cmix_file& conquer();
	static Cmix_file& general();
	static Cmix_file& theater(t_theater_id);
	static string theater_fname(t_theater_id);
	static string theater_fext(t_theater_id);
};
