#if !defined(AFX_MIX_CACHE_H__B168BFC0_F1D0_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_MIX_CACHE_H__B168BFC0_F1D0_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace mix_cache
{
	int load();
	int save();
	const void* get_data(int crc);
	void set_data(int crc, const void* data, int size);
};

#endif // !defined(AFX_MIX_CACHE_H__B168BFC0_F1D0_11D3_B605_0000B4936994__INCLUDED_)
