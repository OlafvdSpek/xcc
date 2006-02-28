// ucr_formats.h: interface for the Cucr_formats class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCR_FORMATS_H__37735622_BB25_4E3C_9137_E811538EBB6D__INCLUDED_)
#define AFX_UCR_FORMATS_H__37735622_BB25_4E3C_9137_E811538EBB6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ucr_format.h"
#include "xif_key.h"

class Cucr_formats  
{
public:
	typedef vector<Cucr_format> t_list;

	void add(const Cucr_format& v);
	Cxif_key export() const;
	void import(const Cxif_key& key);
	Cucr_formats();

	const t_list& list() const
	{
		return m_list;
	}
private:
	t_list m_list;
};

#endif // !defined(AFX_UCR_FORMATS_H__37735622_BB25_4E3C_9137_E811538EBB6D__INCLUDED_)
