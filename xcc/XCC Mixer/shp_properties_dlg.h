#if !defined(AFX_SHP_PROPERTIES_DLG_H__C6F3F600_D0FC_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_SHP_PROPERTIES_DLG_H__C6F3F600_D0FC_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// shp_properties_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cshp_properties_dlg dialog

class Cshp_properties_dlg : public CDialog
{
// Construction
public:
	void set_size(int cx, int cy, int c_frames);
	Cshp_properties_dlg(CWnd* pParent = NULL);   // standard constructor

	int get_cx() const
	{
		return m_cx;
	}

	int get_cy() const
	{
		return m_cy;
	}

	int get_c_frames() const
	{
		return m_c_frames;
	}

// Dialog Data
	//{{AFX_DATA(Cshp_properties_dlg)
	enum { IDD = IDD_SHP_PROPERTIES };
	int		m_cy;
	int		m_cx;
	int		m_c_frames;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cshp_properties_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cshp_properties_dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHP_PROPERTIES_DLG_H__C6F3F600_D0FC_11D4_A95D_0050042229FC__INCLUDED_)
