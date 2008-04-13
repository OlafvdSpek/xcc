#include "stdafx.h"
#include "timer.h"

LARGE_INTEGER Ctimer::frequency;

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