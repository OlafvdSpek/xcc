#pragma once

#include <ddraw.h>

using namespace std;

class Cxcc_dd  
{
private:
	LPDIRECTDRAW pdd;
	HWND m_hWnd;
public:
	long create(HWND ihWnd);
	void handle_error(const string &s);
	Cxcc_dd();

	const LPDIRECTDRAW get_p() const
	{
		return pdd;
	}

	bool is_available() const
	{
		return pdd;
	}
};
