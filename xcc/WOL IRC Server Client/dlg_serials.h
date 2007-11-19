#pragma once

#include "resource.h"

class Cdlg_serials: public ETSLayoutDialog
{
	DECLARE_DYNAMIC(Cdlg_serials)
public:
	Cdlg_serials(CWnd* pParent = NULL);

	enum { IDD = IDD_SERIALS };
protected:
	void add_game(const string& reg_key, int game, int gsku);
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CString	m_edit;
};
