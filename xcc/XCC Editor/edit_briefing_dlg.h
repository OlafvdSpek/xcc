#if !defined(AFX_EDIT_BRIEFING_DLG_H__B10BDBA1_3152_11D3_B602_0000C006A2C2__INCLUDED_)
#define AFX_EDIT_BRIEFING_DLG_H__B10BDBA1_3152_11D3_B602_0000C006A2C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "xcc_level.h"

// edit_briefing_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cedit_briefing_dlg dialog

class Cedit_briefing_dlg : public CDialog
{
// Construction
public:
	Cedit_briefing_dlg(Cxcc_level& level);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cedit_briefing_dlg)
	enum { IDD = IDD_EDIT_BRIEFING_DLG };
	//}}AFX_DATA
	CString	m_edit;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cedit_briefing_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cedit_briefing_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_briefing_data& m_briefing_data;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_BRIEFING_DLG_H__B10BDBA1_3152_11D3_B602_0000C006A2C2__INCLUDED_)
