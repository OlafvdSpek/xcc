// xstring.h: interface for the xstring class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XSTRING_H__551DB641_F2A2_11D2_B601_960A254CD56F__INCLUDED_)
#define AFX_XSTRING_H__551DB641_F2A2_11D2_B601_960A254CD56F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>

class xstring: public std::string
{
public:
	xstring();
	xstring(const std::string &s);
	xstring& ltrim();
	xstring& rtrim();
	xstring& tolower();

	xstring& trim()
	{
		ltrim();
		rtrim();
		return *this;
	}
};

#endif // !defined(AFX_XSTRING_H__551DB641_F2A2_11D2_B601_960A254CD56F__INCLUDED_)
