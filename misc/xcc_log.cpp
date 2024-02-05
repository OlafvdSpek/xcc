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
#include "xcc_log.h"

#include <ctime>
#include <fstream>
#include <iomanip>
#include "xcc_dirs.h"

static CRITICAL_SECTION g_lock;
bool g_lock_inited = false;
static ofstream log_f;
static time_t log_t = time(NULL);
static int log_x = 0;

void xcc_log::attach_file(const string& name)
{
	if (xcc_dirs::enable_log())
		log_f.open((xcc_dirs::get_data_dir() + name).c_str());
}

static void lock()
{
	if (!g_lock_inited)
	{
		InitializeCriticalSection(&g_lock);
		g_lock_inited = true;
	}
	EnterCriticalSection(&g_lock);
}

static void unlock()
{
	LeaveCriticalSection(&g_lock);
}

void xcc_log::indent(int x)
{
	lock();
	log_x += x;
	unlock();
}

void xcc_log::write_line(const string& s, int x)
{
	lock();
	if (x < 0)
		log_x += x;
	if (log_f.is_open())
	{
		log_f << setw(4) << time(NULL) - log_t << ' ' << string(log_x << 2, ' ') << s << endl;
		log_f.flush();
	}
	if (x > 0)
		log_x += x;
	unlock();
}