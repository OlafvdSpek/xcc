#pragma once

#include "resource.h"
#include "xcc_mod.h"

class Cproperties_dlg : public CDialog
{
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
