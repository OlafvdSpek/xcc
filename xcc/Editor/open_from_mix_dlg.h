#if !defined(AFX_OPEN_FROM_MIX_DLG_H__76B51963_088C_11D3_B601_E0474AC10154__INCLUDED_)
#define AFX_OPEN_FROM_MIX_DLG_H__76B51963_088C_11D3_B601_E0474AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <map>
#include "id_log.h"
#include "list_ctrl_extension.h"
#include "mix_file.h"
#include "resource.h"
#include "string_conversion.h"
#include "cc_file.h"
#include "xcc_level.h"
#include "xcc_mixs.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Copen_from_mix_dlg dialog

struct t_index_info
{
	string description;
	t_theater_id theater;
};

typedef map<string, t_index_info> t_index;

class Copen_from_mix_dlg: public ETSLayoutDialog
{
// Construction
public:
	void get_selected_f(Cvirtual_binary& bin_d, Cvirtual_binary& ini_d);
	Copen_from_mix_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Copen_from_mix_dlg)
	enum { IDD = IDD_OPEN_FROM_MIX_DLG };
	CButton	m_ok_button;
	Clist_ctrl_extension	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Copen_from_mix_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Copen_from_mix_dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cmix_file& mix;
	int c_files;
	t_index index;
	string selected_fname;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPEN_FROM_MIX_DLG_H__76B51963_088C_11D3_B601_E0474AC10154__INCLUDED_)
