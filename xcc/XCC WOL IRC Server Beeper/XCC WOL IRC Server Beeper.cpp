#include "stdafx.h"
#include "socket.h"

string read_string(const char*& s, const char* s_end)
{
	if (s + 1 > s_end)
		return "";
	int l = *s++ & 0xff;
	if (s + l > s_end)
		return "";
	s += l;
	return string(s - l, l);
}

void recv(Csocket& s)
{
	const int cb_b = 2 << 10;
	char b[cb_b];
	int r = s.recv(b, cb_b);
	if (r == SOCKET_ERROR || !r)
		return;
	Beep(500, 100);
	switch (b[0])
	{
	case 0:
		{
			HWND hWnd = FindWindow(NULL, "Red Alert 2");
			if (!hWnd)
				break;
			ShowWindow(hWnd, SW_SHOWMAXIMIZED);
			SetForegroundWindow(hWnd);
		}
		break;
	case 1:
		{
			const char* s = b + 1;
			const char* s_end = b + r;
			string sender = read_string(s, s_end);
			string message = read_string(s, s_end);
			if (!sender.empty() && !message.empty())
				cout << sender << ": " << message;
		}
		break;
	}
}

int main(int argc, char* argv[])
{
#ifdef WIN32
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 0), &wsadata))
		return cerr << "Unable to start WSA" << endl, 0;
#endif
	Csocket s;
	s.open(SOCK_DGRAM);
	s.connect(Csocket::get_host("localhost"), htons(4005));
	fd_set fd_read_set;
	int stime = 0;
	while (1)
	{
		if (time(NULL) - stime > 60)
		{
			char d;
			s.send(&d, 1);
			stime = time(NULL);
		}
		FD_ZERO(&fd_read_set);
		FD_SET(s, &fd_read_set);
		TIMEVAL tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		select(s + 1, &fd_read_set, NULL, NULL, &tv);
		if (FD_ISSET(s, &fd_read_set))
			recv(s);
	}
#ifdef WIN32
	WSACleanup();
	Sleep(15000);
#endif
	return 0;
}
