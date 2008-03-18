#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <string>
#include "resource.h"       // main symbols

using namespace std;

class CXCCMixerApp : public CWinApp
{
public:
	void find_fs_exe();
	void find_fa_exe();
	void find_se_exe();
	string get_fs_exe() const;
	bool is_fs_available() const;
	string get_fa_exe() const;
	bool is_fa_available() const;
	string get_se_exe() const;
	bool is_se_available() const;
	string get_semm_exe() const;
	bool is_semm_available() const;
	string get_rage_exe() const;
	bool is_rage_available() const;
	string get_xcc_av_player_exe() const;
	bool is_xcc_av_player_available() const;
	string get_xcc_editor_exe() const;
	bool is_xcc_editor_available() const;
	string get_xcc_mix_editor_exe() const;
	bool is_xcc_mix_editor_available() const;
	string get_xcc_mixer_exe() const;
	string get_dune2_exe() const;
	string get_td_dos_exe() const;
	string get_td_win_exe() const;
	string get_ra_dos_exe() const;
	string get_ra_win_exe() const;
	string get_dune2000_exe() const;
	string get_ts_exe() const;
	string get_ra2_exe() const;
	bool is_xcc_mixer_available() const;
	bool is_dune2_available() const;
	bool is_td_dos_available() const;
	bool is_td_win_available() const;
	bool is_ra_dos_available() const;
	bool is_ra_win_available() const;
	bool is_dune2000_available() const;
	bool is_ts_available() const;
	bool is_ra2_available() const;

	//{{AFX_VIRTUAL(CXCCMixerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXCCMixerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	string m_fs_exe;
	string m_fa_exe;
	string m_se_exe;
	string m_semm_exe;
	string m_rage_exe;
	string m_xcc_av_player_exe;
	string m_xcc_editor_exe;
	string m_xcc_mix_editor_exe;
	string m_xcc_mixer_exe;

	string m_dune2_exe;
	string m_td_dos_exe;
	string m_td_win_exe;
	string m_ra_dos_exe;
	string m_ra_win_exe;
	string m_dune2000_exe;
	string m_ts_exe;
	string m_ra2_exe;
};
