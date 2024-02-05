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

#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>
#include <dsound.h>

class Cxcc_ds
{
public:
	int create(HWND ihWnd);
	void handle_error(const string&) const;

	const LPDIRECTSOUND get_p() const
	{
		return ds_;
	}

	bool is_available() const
	{
		return ds_;
	}
private:
	LPDIRECTSOUND ds_ = NULL;
	HWND m_hWnd;
};
