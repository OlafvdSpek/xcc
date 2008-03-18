#pragma once

#include "xcc_dd.h"

class Cxcc_dds  
{
private:
	Cxcc_dd* pdd;
	LPDIRECTDRAWSURFACE pdds;
public:
	long create(Cxcc_dd &dd, long cx, long cy);
	void handle_error(const string &s) const;
	Cxcc_dds();
	virtual ~Cxcc_dds();

	const LPDIRECTDRAWSURFACE get_p() const
	{
		return pdds;
	}

	bool is_available() const
	{
		return pdds;
	}
};
