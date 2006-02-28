#if !defined(AFX_RESIZEDLG_H__A96F0741_774D_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_RESIZEDLG_H__A96F0741_774D_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ResizeDlg.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CResizeDlg dialog

class CResizeDlg : public CDialog
{
// Construction
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
// Dialog Data
	//{{AFX_DATA(CResizeDlg)
	enum { IDD = IDD_RESIZE };
	int		m_cx;
	int		m_cy;
	BOOL	m_maintain_aspect_ratio;
	int	m_relative_cx;
	int	m_relative_cy;
	BOOL	m_fix_shadows;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIZEDLG_H__A96F0741_774D_11D4_B606_0000B4936994__INCLUDED_)
