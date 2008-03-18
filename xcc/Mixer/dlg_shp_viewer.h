#pragma once

#include "resource.h"
#include "video_decoder.h"
#include "virtual_image.h"

class Cdlg_shp_viewer: public ETSLayoutDialog
{
public:
	void show_frame();
	Cvirtual_image decode_image(int i) const;
	void write(Cvideo_decoder* decoder);
	Cdlg_shp_viewer(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(Cdlg_shp_viewer)
	enum { IDD = IDD_SHP_VIEWER };
	CSliderCtrl	m_slider;
	CStatic	m_image;
	int		m_index;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(Cdlg_shp_viewer)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

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
