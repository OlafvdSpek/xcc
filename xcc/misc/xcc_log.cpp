#include "stdafx.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include "xcc_dirs.h"
#include "xcc_log.h"

using namespace std;

static ofstream log_f;
static int log_t = 0;
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
	log_f.open((xcc_dirs::get_data_dir() + name).c_str());
}

void xcc_log::indent(int x)
{
	log_x += x;
}

void xcc_log::write_line(const string& s, int x)
{
	if (!log_t)
		log_t = time(NULL);
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
}