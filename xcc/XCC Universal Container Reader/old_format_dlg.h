#if !defined(AFX_FORMAT_DLG_H__A2282221_9D80_4D98_9DFB_2A21715D3D8D__INCLUDED_)
#define AFX_FORMAT_DLG_H__A2282221_9D80_4D98_9DFB_2A21715D3D8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// format_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cformat_dlg dialog

class Cformat_dlg : public ETSLayoutDialog
{
// Construction
public:
	Cformat_dlg(const Cucr_formats& formats, CWnd* pParent = NULL);   // standard constructor

	const Cucr_format& format() const
	{
		return m_formats.list()[m_format];
	}

// Dialog Data
	//{{AFX_DATA(Cformat_dlg)
	enum { IDD = IDD_FORMATS };
	CButton	m_ok_button;
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cformat_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cformat_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_format;
	const Cucr_formats& m_formats;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMAT_DLG_H__A2282221_9D80_4D98_9DFB_2A21715D3D8D__INCLUDED_)
