// xif_tools.cpp: implementation of the Cxif_tools class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xif editor.h"
#include "xif_tools.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int str2id(const char* s)
{
	if (strlen(s) > 8)
		return -1;
	int id = 0;
	const char* r = s;
	while (*r)
	{
		id <<= 4;
		int c = toupper(*r);
		if (c >= '0' && c <= '9')
			c -= '0';
		else if (c >= 'A' && c <= 'F')
			c -= 'A' - 0xa;
		else 
			return - 1;
		id |= c;
		r++;
	}
	return id < 0 ? -1 : id;
}

int str2hex(const char* s)
{
	if (strlen(s) > 8)
		return -1;
	int id = 0;
	const char* r = s;
	while (*r)
	{
		id <<= 4;
		int c = toupper(*r);
		if (c >= '0' && c <= '9')
			c -= '0';
		else if (c >= 'A' && c <= 'F')
			c -= 'A' - 0xa;
		else 
			return - 1;
		id |= c;
		r++;
	}
	return id;
}