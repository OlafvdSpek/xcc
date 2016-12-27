#pragma once

class Cdd_window : public CWnd
{
public:
	Cdd_window();

	//{{AFX_VIRTUAL(Cdd_window)
	//}}AFX_VIRTUAL
public:
	bool stop_req() const;
	void destroy();
	bool create();
	virtual ~Cdd_window();
protected:
	//{{AFX_MSG(Cdd_window)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnClose();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_stop_req;
};
