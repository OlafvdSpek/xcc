#if !defined(AFX_DD_WINDOW_H__39697643_F4B0_11D2_B601_F14DBED8140A__INCLUDED_)
#define AFX_DD_WINDOW_H__39697643_F4B0_11D2_B601_F14DBED8140A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// dd_window.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cdd_window window

class Cdd_window : public CWnd
{
// Construction
public:
	Cdd_window();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdd_window)
	//}}AFX_VIRTUAL

// Implementation
public:
	bool stop_req() const;
	void destroy();
	bool create();
	virtual ~Cdd_window();
private:
	bool m_stop_req;

	// Generated message map functions
protected:
	//{{AFX_MSG(Cdd_window)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnClose();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DD_WINDOW_H__39697643_F4B0_11D2_B601_F14DBED8140A__INCLUDED_)
