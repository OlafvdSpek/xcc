#pragma once

#include "resource.h"
#include "xcc_level.h"

class Cedit_briefing_dlg : public CDialog
{
public:
	Cedit_briefing_dlg(Cxcc_level& level);   // standard constructor

	//{{AFX_DATA(Cedit_briefing_dlg)
	enum { IDD = IDD_EDIT_BRIEFING_DLG };
	//}}AFX_DATA
	CString	m_edit;
	//{{AFX_VIRTUAL(Cedit_briefing_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Cedit_briefing_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_briefing_data& m_briefing_data;
};
