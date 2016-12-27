#pragma once

#include "cc_structures.h"
#include "resource.h"

class Cproperties_dlg : public CDialog
{
public:
	void get(t_tmp_image_header& header);
	void set(const t_tmp_image_header& header);
	Cproperties_dlg(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(Cproperties_dlg)
	enum { IDD = IDD_PROPERTIES };
	int		m_height;
	int		m_terrain_type;
	int		m_x;
	int		m_x_extra;
	int		m_y;
	int		m_y_extra;
	int		m_ramp_type;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(Cproperties_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Cproperties_dlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
