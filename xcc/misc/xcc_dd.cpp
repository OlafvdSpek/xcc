#include "stdafx.h"
#include "xcc_dd.h"

Cxcc_dd::Cxcc_dd()
{
	pdd = NULL;
}

long Cxcc_dd::create(HWND ihWnd)
{
	typedef HRESULT (WINAPI* LPDIRECTDRAWCREATE)(GUID*, LPDIRECTDRAW*, IUnknown*);

	m_hWnd = ihWnd;
	HMODULE dd_dll = LoadLibrary("ddraw.dll");
	LPDIRECTDRAWCREATE pDDCreate = reinterpret_cast<LPDIRECTDRAWCREATE>(GetProcAddress(dd_dll, "DirectDrawCreate"));
	if (!pDDCreate || pDDCreate(0, &pdd, 0)) 
	{
		handle_error("Create failed");
		return 1;
	}
	if (pdd->SetCooperativeLevel(m_hWnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_NOWINDOWCHANGES))
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