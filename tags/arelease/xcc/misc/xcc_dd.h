// xcc_dd.h: interface for the xcc_dd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCC_DD_H__0899A263_E9E3_11D2_B601_F7D8079B9126__INCLUDED_)
#define AFX_XCC_DD_H__0899A263_E9E3_11D2_B601_F7D8079B9126__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>
#include "ddraw.h"
#include "vartypes.h"

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
	virtual ~Cxcc_dd();

	const LPDIRECTDRAW get_p() const
	{
		return pdd;
	}

#pragma warning(disable: 4800)
	
	bool is_available() const
	{
		return pdd;
	}
};

#endif // !defined(AFX_XCC_DD_H__0899A263_E9E3_11D2_B601_F7D8079B9126__INCLUDED_)
