#if !defined(AFX_ENERGY_STATUS_DLG_H__D43F6761_2994_11D3_B602_0000C006A2C2__INCLUDED_)
#define AFX_ENERGY_STATUS_DLG_H__D43F6761_2994_11D3_B602_0000C006A2C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "xcc_level.h"

// energy_status_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cenergy_status_dlg dialog

class Cenergy_status_dlg : public CDialog
{
// Construction
public:
	Cenergy_status_dlg(const Cxcc_level& level);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cenergy_status_dlg)
	enum { IDD = IDD_ENERGY_STATUS_DLG };
	//}}AFX_DATA
	long m_power_in[c_side_id];
	long m_power_out[c_side_id];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cenergy_status_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cenergy_status_dlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	const Cxcc_level& m_level;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENERGY_STATUS_DLG_H__D43F6761_2994_11D3_B602_0000C006A2C2__INCLUDED_)
