#pragma once

#include "resource.h"

class CResizeDlg : public CDialog
{
public:
	void update_relative();
	void update_absolut();
	CResizeDlg(CWnd* pParent = NULL);   // standard constructor
	void set_size(int cx, int cy);

	int get_cx() const
	{
		return m_cx;
	}

	int get_cy() const
	{
		return m_cy;
	}
	//{{AFX_DATA(CResizeDlg)
	enum { IDD = IDD_RESIZE };
	int		m_cx;
	int		m_cy;
	BOOL	m_maintain_aspect_ratio;
	int	m_relative_cx;
	int	m_relative_cy;
	BOOL	m_fix_shadows;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CResizeDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CResizeDlg)
	afx_msg void OnUpdateCX();
	afx_msg void OnUpdateCY();
	afx_msg void OnUpdateRelativeCx();
	afx_msg void OnUpdateRelativeCy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	float m_aspect_ratio;
	int m_original_cx;
	int m_original_cy;
};
