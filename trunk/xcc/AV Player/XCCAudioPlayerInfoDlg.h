#pragma once

#include "resource.h"

class CXCCAudioPlayerInfoDlg : public CDialog
{
public:
	CXCCAudioPlayerInfoDlg(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CXCCAudioPlayerInfoDlg)
	enum { IDD = IDD_INFO };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CXCCAudioPlayerInfoDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCAudioPlayerInfoDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
