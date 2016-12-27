#pragma once

namespace xcc_log
{
	void attach_file(const string& name);
	void indent(int x);
	void write_line(const string& s, int x = 0);
}