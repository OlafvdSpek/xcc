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
#include "xcc_dd.h"

int Cxcc_dd::create(HWND ihWnd)
{
	typedef HRESULT (WINAPI* LPDIRECTDRAWCREATE)(GUID*, LPDIRECTDRAW*, IUnknown*);

	m_hWnd = ihWnd;
	HMODULE dd_dll = LoadLibrary("ddraw.dll");
	LPDIRECTDRAWCREATE pDDCreate = reinterpret_cast<LPDIRECTDRAWCREATE>(GetProcAddress(dd_dll, "DirectDrawCreate"));
	if (!pDDCreate || pDDCreate(0, &dd_, 0)) 
	{
		handle_error("Create failed");
		return 1;
	}
	if (dd_->SetCooperativeLevel(m_hWnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_NOWINDOWCHANGES))
	{
		handle_error("SetCooperativeLevel failed");
		return 1;
	}
	return 0;
}

void Cxcc_dd::handle_error(const string &s)
{
	MessageBox(m_hWnd, s.c_str(), "DirectDraw error", MB_ICONERROR | MB_OK);
}