#pragma once

#include <memory>
#include <string>
#include <windows.h>

template<class T>
class Cwin_handle_base
{
public:
	Cwin_handle_base() = default;

	explicit Cwin_handle_base(T h) : m_source(h == INVALID_HANDLE_VALUE ? NULL : h, CloseHandle)
	{
	}

	void clear()
	{
		m_source.reset();
	}

	operator T() const
	{
		return static_cast<T>(m_source.get());
	}
private:
	std::shared_ptr<void> m_source;
};

typedef Cwin_handle_base<HANDLE> Cwin_handle;

int create_process(const std::string& exe_name, const std::string& _cmd_line = "", bool wait = false);
