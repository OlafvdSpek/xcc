#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

using namespace std;

class CXCCMixerApp : public CWinApp
{
public:
	void find_fs_exe();
	void find_fa_exe();
	string get_fs_exe() const;
	string get_fa_exe() const;
	bool is_fs_available() const;
	bool is_fa_available() const;

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
};
