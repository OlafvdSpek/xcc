#pragma once

#include <string>
#include "string_conversion.h"
#include "timer.h"

using namespace std;

class Clog_window : public CWnd
{
public:
	Clog_window();

	//{{AFX_VIRTUAL(Clog_window)
	//}}AFX_VIRTUAL

	void write_line(const string& s);
	bool create();
	virtual ~Clog_window();
protected:
	//{{AFX_MSG(Clog_window)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CEdit m_edit;
	CFont m_edit_font;
	string m_log_text;
	Ctimer m_timer;
};
