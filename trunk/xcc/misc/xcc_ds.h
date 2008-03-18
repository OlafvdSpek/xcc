#pragma once

#include <string>
#include "vartypes.h"

#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>
#include <dsound.h>

using namespace std;

class Cxcc_ds
{
private:
	LPDIRECTSOUND pds;
	HWND m_hWnd;
public:
	long create(HWND ihWnd);
	void handle_error(const string &s) const;
	Cxcc_ds();
	virtual ~Cxcc_ds();

	const LPDIRECTSOUND get_p() const
	{
		return pds;
	}

	bool is_available() const
	{
		return pds;
	}
};
