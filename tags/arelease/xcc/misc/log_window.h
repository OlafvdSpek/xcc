#if !defined(AFX_LOG_WINDOW_H__A6BA3724_1341_11D3_B601_C0484AC10154__INCLUDED_)
#define AFX_LOG_WINDOW_H__A6BA3724_1341_11D3_B601_C0484AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>
#include "string_conversion.h"
#include "timer.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Clog_window window

class Clog_window : public CWnd
{
// Construction
public:
	Clog_window();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Clog_window)
	//}}AFX_VIRTUAL

// Implementation
public:
	void write_line(const string& s);
	bool create();
	virtual ~Clog_window();

	// Generated message map functions
protected:
	//{{AFX_MSG(Clog_window)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CEdit m_edit;
	CFont m_edit_font;
	string m_log_text;
	Ctimer m_timer;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOG_WINDOW_H__A6BA3724_1341_11D3_B601_C0484AC10154__INCLUDED_)
