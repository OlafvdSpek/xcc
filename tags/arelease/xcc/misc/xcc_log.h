#pragma once

#include <string>

using namespace std;

namespace xcc_log
{
	void attach_file(const string& name);
	void attach(void* log_window);
	void write_line(const string& s);
}