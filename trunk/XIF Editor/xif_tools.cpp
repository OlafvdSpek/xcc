#include "stdafx.h"
#include "xif_tools.h"

int str2id(const char* r)
{
	if (strlen(r) > 8)
		return -1;
	int id = 0;
	for (; *r; r++)
	{
		int c = toupper(*r);
		if (c >= '0' && c <= '9')
			c -= '0';
		else if (c >= 'A' && c <= 'F')
			c -= 'A' - 10;
		else
			return -1;
		id <<= 4;
		id |= c;
	}
	return id < 0 ? -1 : id;
}

int str2hex(const char* r)
{
	if (strlen(r) > 8)
		return -1;
	int id = 0;
	for (; *r; r++)
	{
		int c = toupper(*r);
		if (c >= '0' && c <= '9')
			c -= '0';
		else if (c >= 'A' && c <= 'F')
			c -= 'A' - 10;
		else
			return -1;
		id <<= 4;
		id |= c;
	}
	return id;
}