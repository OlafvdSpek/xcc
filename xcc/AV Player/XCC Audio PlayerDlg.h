#pragma once

#include <windows.h>
#include "aud_file.h"
#include "dd_window.h"
#include "id_log.h"
#include "ListCtrlEx.h"
#include "mix_file.h"
#include "string_conversion.h"
#include "vqa_file.h"
#include "vqa_play.h"
#include "wav_file.h"
#include "xcc_dirs.h"
#include "xcc_dds.h"
#include "xcc_dsb.h"
#include "XCC Audio Player.h"

class CXCCAudioPlayerDlg : public ETSLayoutDialog
{
public:
	int compare(int id_a, int id_b) const;
	bool has_scores();
	bool is_score(int id);
	void shuffle_aud();
	void sort_list(int i, bool reverse);
	bool valid_index();
	int play_aud(int id);
	int play_aud(Caud_file& audf);
	int play_vqa(int id);
	int play_vqa(Cvqa_file& f);
	int play_wav(int id);
	int play_wav(Cwav_file& wavf);
	int OpenMix(const string &fname);
	CXCCAudioPlayerDlg(CWnd* pParent = NULL);	// standard constructor
	~CXCCAudioPlayerDlg();

	//{{AFX_DATA(CXCCAudioPlayerDlg)
	enum { IDD = IDD_XCCAUDIOPLAYER_DIALOG };
	CButton	m_extract_raw_button;
	CButton	m_extractbutton;
	CButton	m_playbutton;
	CButton	m_shufflebutton;
	CListCtrlEx	m_list;
	CString	m_statusbar;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CXCCAudioPlayerDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

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
	int current_id;
	
	//{{AFX_MSG(CXCCAudioPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExtract();
	afx_msg void OnOpenmix();
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
	afx_msg void OnGetdispinfoList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	struct t_index_entry
	{
		string name;
		t_file_type type;
		int length;
		int size;
		string description;
	};

	map<int, t_index_entry> m_index;
	int m_sort_column;
	bool m_sort_reverse;
};
