// timer.cpp: implementation of the Ctimer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "timer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

LARGE_INTEGER Ctimer::frequency;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ctimer::Ctimer()
{
	QueryPerformanceFrequency(&frequency);
}

Ctimer::~Ctimer()
{
}

void Ctimer::start()
{
	QueryPerformanceCounter(&start_time);
}

LONGLONG Ctimer::read() const
{
	assert(frequency.QuadPart);
	LARGE_INTEGER current_time;
	QueryPerformanceCounter(&current_time);
	return static_cast<LONGLONG>(static_cast<double>(current_time.QuadPart - start_time.QuadPart) / static_cast<double>(frequency.QuadPart) * 1000000 + 0.5);
}

void Ctimer::operator +=(LONGLONG v)
{
	start_time.QuadPart += static_cast<LONGLONG>(static_cast<double>(v) / 1000000 * frequency.QuadPart + 0.5);
}