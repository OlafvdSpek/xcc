#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
	char b[MAX_PATH];
	if (GetModuleFileName(NULL, b, MAX_PATH)
		&& strcpy(strrchr(b, '\\') + 1, "game.exe"), CreateProcess(b, NULL, NULL, NULL, false, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi))
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	return 0;
}