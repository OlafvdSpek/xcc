// XCC RA2 Radar CustomizerDlg.h : header file
//

#if !defined(AFX_XCCRA2RADARCUSTOMIZERDLG_H__5043C085_05B3_11D5_A95E_0050042229FC__INCLUDED_)
#define AFX_XCCRA2RADARCUSTOMIZERDLG_H__5043C085_05B3_11D5_A95E_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_structures.h"
#include "virtual_image.h"

/////////////////////////////////////////////////////////////////////////////
// CXCCRA2RadarCustomizerDlg dialog

class CXCCRA2RadarCustomizerDlg : public CDialog
{
// Construction
public:
	Cvirtual_image scale_image(Cvirtual_image image, Cvirtual_image mask, Cvirtual_binary& d);
	void update_previews();
	static HBITMAP create_bitmap(Cvirtual_image image);
	static void load_image(int id, Cvirtual_image& image);
	int customize_radar(t_game game, int theater);
	CXCCRA2RadarCustomizerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCRA2RadarCustomizerDlg)
	enum { IDD = IDD_XCCRA2RADARCUSTOMIZER_DIALOG };
	CStatic	m_urban_preview_control;
	CStatic	m_temperate_preview_control;
	CStatic	m_snow_preview_control;
	int		m_blue;
	int		m_green;
	int		m_red;
	BOOL	m_reset;
	BOOL	m_temperate;
	BOOL	m_urban;
	BOOL	m_relative;
	BOOL	m_ra2;
	BOOL	m_ts;
	BOOL	m_snow;
	BOOL	m_lock;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCRA2RadarCustomizerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXCCRA2RadarCustomizerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnChangeBlue();
	afx_msg void OnChangeGreen();
	afx_msg void OnChangeRed();
	afx_msg void OnRelative();
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cvirtual_image m_snow_preview;
	Cvirtual_image m_snow_preview_mask;
	Cvirtual_image m_temperate_preview;
	Cvirtual_image m_temperate_preview_mask;
	Cvirtual_image m_urban_preview;
	Cvirtual_image m_urban_preview_mask;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCRA2RADARCUSTOMIZERDLG_H__5043C085_05B3_11D5_A95E_0050042229FC__INCLUDED_)
