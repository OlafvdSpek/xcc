// xcc_ds.h: interface for the Cxcc_ds class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCC_DS_H__7DF96684_E083_11D2_B750_83F8E2CE1F65__INCLUDED_)
#define AFX_XCC_DS_H__7DF96684_E083_11D2_B750_83F8E2CE1F65__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

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

#pragma warning (disable: 4800)

	bool is_available() const
	{
		return pds;
	}
};

#endif // !defined(AFX_XCC_DS_H__7DF96684_E083_11D2_B750_83F8E2CE1F65__INCLUDED_)