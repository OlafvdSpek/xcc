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

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "xif_key.h"

class Cxif_file : public Ccc_file_sh<t_xif_header_old>
{
public:
	bool is_valid() const
	{
		const t_xif_header_old& h = header();
		return !(sizeof(t_xif_header_old) > size() ||
			h.id != file_id ||
			h.version != file_version_old && h.version != file_version_new && h.version != file_version_fast);
	}

	int decode(Cxif_key& key)
	{
		return key.load_key(data(), size());
	}
};
