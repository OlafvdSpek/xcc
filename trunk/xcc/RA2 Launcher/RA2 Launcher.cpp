#include <windows.h>

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
	char b[MAX_PATH];
	if (GetModuleFileName(NULL, b, MAX_PATH))
		return 1;
	strcpy(strrchr(b, '\\') + 1, "game.exe");
	CreateProcess(b, NULL, NULL, NULL, false, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);
	return 0;
}