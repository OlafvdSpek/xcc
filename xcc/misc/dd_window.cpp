// dd_window.cpp : implementation file
//

#include "stdafx.h"
#include "dd_window.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cdd_window

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


/////////////////////////////////////////////////////////////////////////////
// Cdd_window message handlers

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
