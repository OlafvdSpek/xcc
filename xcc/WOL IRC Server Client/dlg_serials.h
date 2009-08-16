#pragma once

#include "cc_structures.h"
#include "resource.h"

class Cdlg_serials: public CDialog
{
public:
	Cdlg_serials(CWnd* pParent = NULL);

	enum { IDD = IDD_SERIALS };
protected:
	void add_game(const string& reg_key, t_game game, CString& edit);
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	
	CString m_ts;
	CString m_ra2;
	CString m_yr;
	CString m_rg;
};
