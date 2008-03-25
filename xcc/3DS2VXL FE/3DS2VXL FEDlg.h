#pragma once

#include <string>

using namespace std;

class CMy3DS2VXLFEDlg : public CDialog
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void update_buttons();
	CMy3DS2VXLFEDlg(CWnd* pParent = NULL);	// standard constructor

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
	BOOL	m_flip_z;
	BOOL	m_swap_yz;
	BOOL	m_swap_zx;
	BOOL	m_materials;
	int		m_resolution;
	BOOL	m_enable_viewer;
	float	m_scale;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CMy3DS2VXLFEDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;

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
