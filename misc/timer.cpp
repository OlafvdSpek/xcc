/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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