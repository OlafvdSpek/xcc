#if !defined(AFX_FORMATS_DLG_H__832E9F3F_1620_4672_ACE1_B6D0DF3D0A6C__INCLUDED_)
#define AFX_FORMATS_DLG_H__832E9F3F_1620_4672_ACE1_B6D0DF3D0A6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// formats_dlg.h : header file
//

#include "resource.h"
#include "string_conversion.h"
#include "ucr_formats.h"

/////////////////////////////////////////////////////////////////////////////
// Cformats_dlg dialog

class Cformats_dlg : public ETSLayoutDialog
{
// Construction
public:
	Cformats_dlg(const Cucr_formats& formats, CWnd* pParent = NULL);   // standard constructor

	const Cucr_format& format() const
	{
		return m_formats.list()[m_format];
	}

	void hint_extension(const char* v)
	{
		m_extension = to_lower(v);
	}
// Dialog Data
	//{{AFX_DATA(Cformats_dlg)
	enum { IDD = IDD_FORMATS };
	CButton	m_ok_button;
	CListCtrlEx	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cformats_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cformats_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	string m_extension;
	int m_format;
	const Cucr_formats& m_formats;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATS_DLG_H__832E9F3F_1620_4672_ACE1_B6D0DF3D0A6C__INCLUDED_)
