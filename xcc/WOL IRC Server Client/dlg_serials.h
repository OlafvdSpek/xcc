#pragma once

#include "resource.h"

class Cdlg_serials: public ETSLayoutDialog
{
	DECLARE_DYNAMIC(Cdlg_serials)
public:
	Cdlg_serials(CWnd* pParent = NULL);

	enum { IDD = IDD_SERIALS };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
