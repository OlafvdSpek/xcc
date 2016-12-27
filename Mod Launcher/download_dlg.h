#pragma once

#include "resource.h"

class Cdownload_dlg : public CDialog
{
public:
	void set_size(int size);
	void set(string source, string destination, int total_size);
	Cdownload_dlg(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(Cdownload_dlg)
	enum { IDD = IDD_DOWNLOAD_UPDATE };
	CProgressCtrl	m_progress;
	CString	m_destination;
	CString	m_source;
	CString	m_size;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(Cdownload_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(Cdownload_dlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_total_size;
};
