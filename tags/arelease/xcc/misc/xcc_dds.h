// xcc_dds.h: interface for the Cxcc_dds class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCC_DDS_H__0899A264_E9E3_11D2_B601_F7D8079B9126__INCLUDED_)
#define AFX_XCC_DDS_H__0899A264_E9E3_11D2_B601_F7D8079B9126__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

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

#pragma warning(disable: 4800)

	bool is_available() const
	{
		return pdds;
	}
};

#endif // !defined(AFX_XCC_DDS_H__0899A264_E9E3_11D2_B601_F7D8079B9126__INCLUDED_)
