// 3DS2VXL FEDlg.h : header file
//

#if !defined(AFX_3DS2VXLFEDLG_H__C75E5C05_EFC6_11D4_A95E_0050042229FC__INCLUDED_)
#define AFX_3DS2VXLFEDLG_H__C75E5C05_EFC6_11D4_A95E_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CMy3DS2VXLFEDlg dialog

class CMy3DS2VXLFEDlg : public CDialog
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void update_buttons();
	CMy3DS2VXLFEDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy3DS2VXLFEDlg)
	enum { IDD = IDD_MY3DS2VXLFE_DIALOG };
	CButton	m_ok;
	CString	m_destination;
	CString	m_source;
	CString	m_skybox;
	BOOL	m_sgal;
	BOOL	m_sgn;
	BOOL	m_estimate_origin;
	BOOL	m_flip_x;
	BOOL	m_flip_y;
	BOOL	m_swap_xy;
	BOOL	m_textures;
	int		m_size;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DS2VXLFEDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy3DS2VXLFEDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSkyboxBrowse();
	afx_msg void OnSourceBrowse();
	afx_msg void OnDestinationBrowse();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	string m_fname;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DS2VXLFEDLG_H__C75E5C05_EFC6_11D4_A95E_0050042229FC__INCLUDED_)
