// XCC Audio PlayerDlg.h : header file
//

#if !defined(AFX_XCCAUDIOPLAYERDLG_H__D87F6A0E_DFB1_11D2_B750_ADF86D0B2966__INCLUDED_)
#define AFX_XCCAUDIOPLAYERDLG_H__D87F6A0E_DFB1_11D2_B750_ADF86D0B2966__INCLUDED_

#include <string>
#include "aud_file.h"
#include "dd_window.h"
#include "id_log.h"
#include "mix_file.h"
#include "string_conversion.h"
#include "vqa_file.h"
#include "vqa_play.h"
#include "wav_file.h"
#include "xcc_dirs.h"
#include "xcc_dds.h"
#include "xcc_dsb.h"
#include "XCC Audio Player.h"
#include "windows.h"


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

struct mixdata_entry
{
	dword id;
	t_file_type type;
};

/////////////////////////////////////////////////////////////////////////////
// CXCCAudioPlayerDlg dialog

class CXCCAudioPlayerDlg : public ETSLayoutDialog
{
// Construction
public:
	int compare(int id_a, int id_b) const;
	bool has_scores();
	bool is_score(int i);
	void release_memory();
	void shuffle_aud();
	void sort_list(int i, bool reverse);
	bool valid_index();
	mixdata_entry* mixdata; 
	int play_aud(dword id);
	int play_aud(Caud_file& audf);
	int play_vqa(dword id);
	int play_vqa(Cvqa_file& f);
	int play_wav(dword id);
	int play_wav(Cwav_file& wavf);
	long add_column(const string &text, dword index, dword size, dword format = LVCFMT_LEFT, dword subindex = -1);
	long add_item(const string &text, dword index, dword subindex, long param = -1);
	long OpenMix(const string &fname);
	CXCCAudioPlayerDlg(CWnd* pParent = NULL);	// standard constructor
	~CXCCAudioPlayerDlg();

// Dialog Data
	//{{AFX_DATA(CXCCAudioPlayerDlg)
	enum { IDD = IDD_XCCAUDIOPLAYER_DIALOG };
	CButton	m_extract_raw_button;
	CButton	m_extractbutton;
	CButton	m_playbutton;
	CButton	m_shufflebutton;
	CListCtrl	m_list;
	CString	m_statusbar;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCAudioPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_listfont;
	HICON m_hIcon;
	t_game game;
	Cmix_file mixf;
	Cxcc_dd dd;
	Cxcc_ds ds;
	Cxcc_dsb dsb;
	bool audio_output;
	int m_c_files;
	bool m_shuffle;
	bool video_output;
	aud_decode decode;
	long current_index;
	
	// Generated message map functions
	//{{AFX_MSG(CXCCAudioPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExtract();
	afx_msg void OnOpenmix();
	afx_msg void OnSetdirectories();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnInfo();
	afx_msg void OnOpenMovies();
	afx_msg void OnOpenSounds();
	afx_msg void OnOpenScores();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShuffle();
	afx_msg void OnExctractRaw();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOpenaud();
	afx_msg void OnOpenvqa();
	afx_msg void OnOpenTheme();
	afx_msg void OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_sort_column;
	bool m_sort_reverse;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCAUDIOPLAYERDLG_H__D87F6A0E_DFB1_11D2_B750_ADF86D0B2966__INCLUDED_)
