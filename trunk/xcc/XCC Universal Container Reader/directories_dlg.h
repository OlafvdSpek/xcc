#if !defined(AFX_DIRECTORIES_DLG_H__035034B7_9C78_48E0_AB45_57A24A5D62C0__INCLUDED_)
#define AFX_DIRECTORIES_DLG_H__035034B7_9C78_48E0_AB45_57A24A5D62C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// directories_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cdirectories_dlg dialog

class Cdirectories_dlg : public ETSLayoutDialog
{
// Construction
public:
	Cdirectories_dlg(const Cucr_library& library, CWnd* pParent = NULL);   // standard constructor

	const Cucr_library& library() const
	{
		return m_library;
	}

// Dialog Data
	//{{AFX_DATA(Cdirectories_dlg)
	enum { IDD = IDD_DIRECTORIES };
	CButton	m_delete_button;
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdirectories_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cdirectories_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDelete();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cucr_library m_library;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTORIES_DLG_H__035034B7_9C78_48E0_AB45_57A24A5D62C0__INCLUDED_)
