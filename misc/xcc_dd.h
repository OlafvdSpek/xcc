#pragma once

#include <ddraw.h>

using namespace std;

class Cxcc_dd  
{
public:
	int create(HWND);
	void handle_error(const string&);

	const LPDIRECTDRAW get_p() const
	{
		return dd_;
	}

	bool is_available() const
	{
		return dd_;
	}
private:
	LPDIRECTDRAW dd_ = NULL;
	HWND m_hWnd;
};
