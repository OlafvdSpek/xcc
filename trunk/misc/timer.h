#pragma once

#include <cassert>
#include <windows.h>

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
