#include "stdafx.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include "xcc_dirs.h"
#include "xcc_log.h"

using namespace std;

static CRITICAL_SECTION g_lock;
bool g_lock_inited = false;
static ofstream log_f;
static time_t log_t = time(NULL);
static int log_x = 0;

#ifdef __AFX_H__
#include "log_window.h"

static Clog_window* log_window = NULL;

void xcc_log::attach(void* log_window)
{
	log_window = static_cast<Clog_window*>(log_window);
}
#endif

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
#ifdef __AFX_H__
	if (log_window)
		log_window->write_line(s);
#endif
	unlock();
}