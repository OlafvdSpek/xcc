#include "stdafx.h"
#include "xcc_dd.h"

Cxcc_dd::Cxcc_dd()
{
	pdd = 0;
}

Cxcc_dd::~Cxcc_dd()
{
}

long Cxcc_dd::create(HWND ihWnd)
{
	m_hWnd = ihWnd;
	if (DD_OK != DirectDrawCreate(0, &pdd, 0)) 
	{
		handle_error("Create failed");
		return 1;
	}
	if (DD_OK != pdd->SetCooperativeLevel(m_hWnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_NOWINDOWCHANGES))
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