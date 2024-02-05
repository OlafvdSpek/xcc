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
#include "xcc_ds.h"

int Cxcc_ds::create(HWND ihWnd)
{
	m_hWnd = ihWnd;
	if (DirectSoundCreate(0, &ds_, 0)) 
	{
		handle_error("Create failed");
		return 1;
	}
	if (ds_->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL))
	{
		handle_error("SetCooperativeLevel failed");
		return 1;
	}
	return 0;
}

void Cxcc_ds::handle_error(const string& s) const
{
	MessageBox(m_hWnd, s.c_str(), "DirectSound error", MB_ICONERROR | MB_OK);
}