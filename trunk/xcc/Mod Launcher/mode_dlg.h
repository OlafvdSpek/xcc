#pragma once

#include "resource.h"
#include "xcc_mod.h"

class Cmode_dlg : public CDialog
{
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

	//{{AFX_DATA(Cmode_dlg)
	enum { IDD = IDD_MODE };
	CComboBox	m_modes;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(Cmode_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(Cmode_dlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	const Cxcc_mod* m_mod;
	string m_mode;
};
