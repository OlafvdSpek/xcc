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
#include "riff_structures.h"

class Criff_file : public Ccc_file
{
public:
	virtual int process();
	virtual int process_chunk(const t_riff_header& header);

	bool is_valid()
	{
		m_validating = true;
		int error = process();
		m_validating = false;
		return !error;
	}

	Criff_file():
	    Ccc_file(false)
	{
		m_validating = false;
	}
protected:
	bool m_validating;
};
