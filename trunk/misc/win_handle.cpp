// win_handle.cpp: implementation of the Cwin_handle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "win_handle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cwin_handle::Cwin_handle(const Cwin_handle& v)
{
	m_source = v.m_source ? v.m_source->attach() : NULL;
}

Cwin_handle::Cwin_handle(HANDLE h)
{
	m_source = h && h != INVALID_HANDLE_VALUE ? new Cwin_handle_source(h) : NULL;
}

Cwin_handle::~Cwin_handle()
{
	if (m_source)
		m_source->detach();
}

const Cwin_handle& Cwin_handle::operator=(const Cwin_handle& v)
{
	if (this != &v)
	{
		if (m_source)
			m_source->detach();
		m_source = v.m_source ? v.m_source->attach() : NULL;
	}
	return *this;
}

void Cwin_handle::clear()
{
	if (!m_source)
		return;
	m_source->detach();
	m_source = NULL;
}

int create_process(const string& exe_name, const string& _cmd_line, bool wait)
{
	char cmd_line[256];
	strcpy(cmd_line, ("\"" + exe_name + "\" " + _cmd_line).c_str());
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
	int error = !CreateProcess(exe_name.c_str(), cmd_line, NULL, NULL, false, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);
	if (!error && wait)
		WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return error;
}
