#if !defined(AFX_SEARCHFILEDLG_H__0D799940_7EAA_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_SEARCHFILEDLG_H__0D799940_7EAA_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SearchFileDlg.h : header file
//

#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CSearchFileDlg dialog

class CSearchFileDlg : public CDialog
{
// Construction
public:
	CSearchFileDlg(CWnd* pParent = NULL);   // standard constructor

	string get_filename() const
	{
		return m_filename;
	}

// Dialog Data
	//{{AFX_DATA(CSearchFileDlg)
	enum { IDD = IDD_SEARCH_FILE };
	CString	m_filename;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchFileDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHFILEDLG_H__0D799940_7EAA_11D4_B606_0000B4936994__INCLUDED_)
