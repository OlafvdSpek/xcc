#if !defined(AFX_DOWNLOAD_DLG_H__E497E681_E7A4_11D4_A95E_0050042229FC__INCLUDED_)
#define AFX_DOWNLOAD_DLG_H__E497E681_E7A4_11D4_A95E_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// download_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cdownload_dlg dialog

class Cdownload_dlg : public CDialog
{
// Construction
public:
	void set_size(int size);
	void set(string source, string destination, int total_size);
	Cdownload_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cdownload_dlg)
	enum { IDD = IDD_DOWNLOAD_UPDATE };
	CProgressCtrl	m_progress;
	CString	m_destination;
	CString	m_source;
	CString	m_size;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdownload_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cdownload_dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_total_size;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOWNLOAD_DLG_H__E497E681_E7A4_11D4_A95E_0050042229FC__INCLUDED_)
