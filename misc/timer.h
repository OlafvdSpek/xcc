// timer.h: interface for the Ctimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMER_H__C7E00F21_FB49_11D2_B601_FCBB2383226E__INCLUDED_)
#define AFX_TIMER_H__C7E00F21_FB49_11D2_B601_FCBB2383226E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "assert.h"
#include "windows.h"

class Ctimer  
{
public:
	void start();
	void operator+=(LONGLONG v);
	LONGLONG read() const;
	Ctimer();
	~Ctimer();

	bool passed() const
	{
		return read() > 0;
	}
private:
	LARGE_INTEGER start_time;
	static LARGE_INTEGER frequency;
};

#endif // !defined(AFX_TIMER_H__C7E00F21_FB49_11D2_B601_FCBB2383226E__INCLUDED_)
