#if !defined(AFX_MIXOPTIONS_H__A14B9B2E_F2B7_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_MIXOPTIONS_H__A14B9B2E_F2B7_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mix_file.h"

// MIXOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMIXOptions dialog

class CMIXOptions : public CDialog
{
// Construction
public:
	void get(t_game& game, bool& encrypted, bool& checksum);
	void set(t_game game, bool encrypted, bool checksum);
	CMIXOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMIXOptions)
	enum { IDD = IDD_OPTIONS };
	BOOL	m_check_checksum;
	BOOL	m_check_encrypted;
	int		m_combo_game;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMIXOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMIXOptions)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIXOPTIONS_H__A14B9B2E_F2B7_11D3_B605_0000B4936994__INCLUDED_)
