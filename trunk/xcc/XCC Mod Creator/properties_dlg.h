#if !defined(AFX_PROPERTIES_DLG_H__5FD7A260_22E9_11D6_B861_0000B4936994__INCLUDED_)
#define AFX_PROPERTIES_DLG_H__5FD7A260_22E9_11D6_B861_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// properties_dlg.h : header file
//

#include "resource.h"
#include "xcc_mod.h"

/////////////////////////////////////////////////////////////////////////////
// Cproperties_dlg dialog

class Cproperties_dlg : public CDialog
{
// Construction
public:
	void mod(const Cxcc_mod& mod);
	void properties(Cxcc_mod::t_file_properties properties);
	Cproperties_dlg(CWnd* pParent = NULL);   // standard constructor

	const Cxcc_mod& mod() const
	{
		return *m_mod;
	}

	string mode() const
	{
		return m_mode_value;		
	}

	string module() const
	{
		return m_module_value;		
	}
// Dialog Data
	//{{AFX_DATA(Cproperties_dlg)
	enum { IDD = IDD_PROPERTIES };
	CComboBox	m_module;
	CComboBox	m_mode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cproperties_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cproperties_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	const Cxcc_mod* m_mod;
	Cxcc_mod::t_file_properties m_properties;
	string m_mode_value;
	string m_module_value;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIES_DLG_H__5FD7A260_22E9_11D6_B861_0000B4936994__INCLUDED_)
