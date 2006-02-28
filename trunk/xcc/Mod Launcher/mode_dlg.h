#if !defined(AFX_MODE_DLG_H__EF893481_23A9_11D6_B861_0000B4936994__INCLUDED_)
#define AFX_MODE_DLG_H__EF893481_23A9_11D6_B861_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// mode_dlg.h : header file
//

#include "resource.h"
#include "xcc_mod.h"

/////////////////////////////////////////////////////////////////////////////
// Cmode_dlg dialog

class Cmode_dlg : public CDialog
{
// Construction
public:
	void mod(const Cxcc_mod& mod);
	Cmode_dlg(CWnd* pParent = NULL);   // standard constructor

	const Cxcc_mod& mod() const
	{
		return *m_mod;
	}
	
	string mode() const
	{
		return m_mode;
	}
// Dialog Data
	//{{AFX_DATA(Cmode_dlg)
	enum { IDD = IDD_MODE };
	CComboBox	m_modes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cmode_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cmode_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	const Cxcc_mod* m_mod;
	string m_mode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODE_DLG_H__EF893481_23A9_11D6_B861_0000B4936994__INCLUDED_)
