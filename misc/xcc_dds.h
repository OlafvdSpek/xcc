#pragma once

#include "xcc_dd.h"

class Cxcc_dds  
{
public:
	int create(Cxcc_dd&, int cx, int cy);
	void handle_error(const string&) const;
	Cxcc_dds();

	const LPDIRECTDRAWSURFACE get_p() const
	{
		return dds_;
	}

	bool is_available() const
	{
		return dds_;
	}
private:
	Cxcc_dd* dd_;
	LPDIRECTDRAWSURFACE dds_ = NULL;
};
