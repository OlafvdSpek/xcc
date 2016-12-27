#pragma once

#include "resource.h"
#include "xcc_level.h"

class Cenergy_status_dlg : public CDialog
{
public:
	Cenergy_status_dlg(const Cxcc_level& level);   // standard constructor

	//{{AFX_DATA(Cenergy_status_dlg)
	enum { IDD = IDD_ENERGY_STATUS_DLG };
	//}}AFX_DATA
	long m_power_in[c_side_id];
	long m_power_out[c_side_id];

	//{{AFX_VIRTUAL(Cenergy_status_dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Cenergy_status_dlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	const Cxcc_level& m_level;
};
