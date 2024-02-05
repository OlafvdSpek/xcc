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

#include "stdafx.h"
#include "XSTE.h"

#include "mix_file.h"
#include "xcc_dirs.h"

Ccsf_file& CXSTE::csf_f()
{
	return m_csf_f;
}

int CXSTE::open(t_game game)
{
	int error = m_f.open_edit(xcc_dirs::get_dir(game) + xcc_dirs::get_csf_fname(game));
	if (!error)
	{
		if (!m_f.size())
		{
			Cmix_file language;
			error = language.open(xcc_dirs::get_language_mix(game));
			if (!error)
			{
				Ccsf_file f;
				error = f.open(xcc_dirs::get_csf_fname(game), language);
				if (!error)
					error = m_f.write(f);
			}
		}
		if (!error)
			error = m_csf_f.open(m_f.h());
		if (error)
			m_f.close();
	}
	return error;
}

int CXSTE::write()
{
	m_f.seek(0);
	Cvirtual_binary d = m_csf_f.write();
	int error = m_f.write(d);
	if (!error)
		error = m_f.set_eof();
	return error;
}
