// XCC RA2 Radar CustomizerDlg.h : header file
//

#if !defined(AFX_XCCRA2RADARCUSTOMIZERDLG_H__5043C085_05B3_11D5_A95E_0050042229FC__INCLUDED_)
#define AFX_XCCRA2RADARCUSTOMIZERDLG_H__5043C085_05B3_11D5_A95E_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXCCRA2RadarCustomizerDlg dialog

class CXCCRA2RadarCustomizerDlg : public CDialog
{
// Construction
public:
	int customize_radar(int theater);
	CXCCRA2RadarCustomizerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXCCRA2RadarCustomizerDlg)
	enum { IDD = IDD_XCCRA2RADARCUSTOMIZER_DIALOG };
	int		m_blue;
	int		m_green;
	int		m_red;
	BOOL	m_reset;
	BOOL	m_snow;
	BOOL	m_temperate;
	BOOL	m_urban;
	BOOL	m_relative;
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCRA2RADARCUSTOMIZERDLG_H__5043C085_05B3_11D5_A95E_0050042229FC__INCLUDED_)
