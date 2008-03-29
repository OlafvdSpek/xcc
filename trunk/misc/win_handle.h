#pragma once

#include <boost/shared_ptr.hpp>
#include <string>
#include <windows.h>

class Cwin_handle
{
public:
	Cwin_handle()
	{
	}

	Cwin_handle(HANDLE h): m_source(h == INVALID_HANDLE_VALUE ? NULL : h, CloseHandle)
	{
	}

	void clear()
	{
		m_source.reset();
	}

	operator HANDLE() const
	{
		return m_source.get();
	}
private:
	boost::shared_ptr<void> m_source;
};

int create_process(const std::string& exe_name, const std::string& _cmd_line = "", bool wait = false);
