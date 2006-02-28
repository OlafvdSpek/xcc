#if !defined(AFX_DLG_SHP_VIEWER_H__D99E8B49_1425_11D6_B606_A7F956E6466D__INCLUDED_)
#define AFX_DLG_SHP_VIEWER_H__D99E8B49_1425_11D6_B606_A7F956E6466D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "video_decoder.h"
#include "virtual_image.h"

class Cdlg_shp_viewer: public ETSLayoutDialog
{
// Construction
public:
	void show_frame();
	Cvirtual_image decode_image(int i) const;
	void write(Cvideo_decoder* decoder);
	Cdlg_shp_viewer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cdlg_shp_viewer)
	enum { IDD = IDD_SHP_VIEWER };
	CSliderCtrl	m_slider;
	CStatic	m_image;
	int		m_index;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdlg_shp_viewer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cdlg_shp_viewer)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPlay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cvideo_decoder* m_decoder;
	int m_frame;
	int m_last_access;
	t_palet m_palet;
	int m_timer_id;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DLG_SHP_VIEWER_H__D99E8B49_1425_11D6_B606_A7F956E6466D__INCLUDED_)
