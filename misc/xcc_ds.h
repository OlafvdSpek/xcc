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
