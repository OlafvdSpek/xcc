#include "stdafx.h"
#include "log_window.h"

Clog_window::Clog_window()
{
}

Clog_window::~Clog_window()
{
}


BEGIN_MESSAGE_MAP(Clog_window, CWnd)
	//{{AFX_MSG_MAP(Clog_window)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

bool Clog_window::create()
{
	CRect p(0, 0, 320, 240);
	SystemParametersInfo(SPI_GETWORKAREA, 0, &p, 0);
	if (!CreateEx(0, AfxRegisterWndClass(0, 0, 0, 0),
		"Log Window", WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE, p, AfxGetMainWnd(), 0, 0))
		return 1;
	GetClientRect(p);
	if (!m_edit.Create(ES_MULTILINE | ES_READONLY | WS_VISIBLE | WS_VSCROLL, p, this, 0))
		return 1;
	m_timer.start();
	if (m_edit_font.CreateFont(-11, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New"))
		m_edit.SetFont(&m_edit_font);
	return 0;
}

void Clog_window::write_line(const string& s)
{
	m_log_text += nwp(11, m_timer.read()) + '\t' + s + "\r\n";
	m_edit.SetWindowText(m_log_text.c_str());
}
