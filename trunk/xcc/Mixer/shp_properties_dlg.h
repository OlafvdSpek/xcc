#pragma once

#include "resource.h"

class Cshp_properties_dlg : public CDialog
{
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

	//{{AFX_DATA(Cshp_properties_dlg)
	enum { IDD = IDD_SHP_PROPERTIES };
	int		m_cy;
	int		m_cx;
	int		m_c_frames;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(Cshp_properties_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(Cshp_properties_dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
