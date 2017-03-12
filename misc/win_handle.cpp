#include "stdafx.h"
#include "win_handle.h"

int create_process(const std::string& exe_name, const std::string& _cmd_line, bool wait)
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
