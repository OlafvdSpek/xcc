#include "stdafx.h"
#include <fstream>
#include "xcc_dirs.h"
#include "xcc_log.h"

using namespace std;

static ofstream log_f;

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

void xcc_log::write_line(const string& s)
{
	if (log_f.is_open())
	{
		log_f << s << endl;
		log_f.flush();
	}
#ifdef __AFX_H__
	if (log_window)
		log_window->write_line(s);
#endif
}