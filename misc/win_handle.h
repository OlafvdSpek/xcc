// win_handle.h: interface for the Cwin_handle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIN_HANDLE_H__41721B20_C315_4530_8F96_26D33893FC30__INCLUDED_)
#define AFX_WIN_HANDLE_H__41721B20_C315_4530_8F96_26D33893FC30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <windows.h>

using namespace std;

class Cwin_handle_source
{
public:
	Cwin_handle_source(HANDLE h)
	{
		m_h = h;
		mc_references = 1;
	}

	Cwin_handle_source* attach()
	{
		mc_references++;
		return this;
	}

	void detach()
	{
		if (!--mc_references)
		{
			CloseHandle(h());
			delete this;
		}
	}

	HANDLE h() const
	{
		return m_h;
	}
private:
	HANDLE m_h;
	int mc_references;
};

class Cwin_handle  
{
public:
	void clear();
	const Cwin_handle& operator=(const Cwin_handle& v);
	Cwin_handle(const Cwin_handle& v);
	Cwin_handle(HANDLE h);
	~Cwin_handle();

	operator HANDLE() const
	{
		return m_source ? m_source->h() : NULL;
	}

	Cwin_handle()
	{
		m_source = NULL;
	}
private:
	Cwin_handle_source* m_source;
};

int create_process(const string& exe_name, const string& _cmd_line = "", bool wait = false);

#endif // !defined(AFX_WIN_HANDLE_H__41721B20_C315_4530_8F96_26D33893FC30__INCLUDED_)
