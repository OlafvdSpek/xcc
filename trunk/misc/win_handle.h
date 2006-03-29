#if !defined(AFX_WIN_HANDLE_H__41721B20_C315_4530_8F96_26D33893FC30__INCLUDED_)
#define AFX_WIN_HANDLE_H__41721B20_C315_4530_8F96_26D33893FC30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <boost/shared_ptr.hpp>
#include <string>
#include <windows.h>

using namespace boost;
using namespace std;

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
	shared_ptr<void> m_source;
};

int create_process(const string& exe_name, const string& _cmd_line = "", bool wait = false);

#endif // !defined(AFX_WIN_HANDLE_H__41721B20_C315_4530_8F96_26D33893FC30__INCLUDED_)
