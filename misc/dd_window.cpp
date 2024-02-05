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
#include "dd_window.h"

Cdd_window::Cdd_window()
{
	m_stop_req = false;
}

Cdd_window::~Cdd_window()
{
}


BEGIN_MESSAGE_MAP(Cdd_window, CWnd)
	//{{AFX_MSG_MAP(Cdd_window)
	ON_WM_SETCURSOR()
	ON_WM_CLOSE()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


bool Cdd_window::create()
{
	return !CreateEx(0, AfxRegisterWndClass(0, 0, (HBRUSH)GetStockObject(BLACK_BRUSH), 0),
		"DD Window", WS_POPUP | WS_VISIBLE, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
		*AfxGetMainWnd(), 0, 0);
}

BOOL Cdd_window::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	SetCursor(0);	
	return true;
}

void Cdd_window::destroy()
{
	DestroyWindow();
}

void Cdd_window::OnClose() 
{
}

void Cdd_window::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
	case 0x1b:
		m_stop_req = true;
		break;
	}
	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

bool Cdd_window::stop_req() const
{
	return m_stop_req;
}
