// XCC Mixer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XCC Mixer.h"

#include "MainFrm.h"
#include "XCC MixerDoc.h"
#include "XCC MixerView.h"

#include <id_log.h>
#include "fs_ini_file.h"
#include "mix_cache.h"
#include "mix_sfl.h"
#include "xcc_dirs.h"
#include "xcc_log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerApp

BEGIN_MESSAGE_MAP(CXCCMixerApp, CWinApp)
	//{{AFX_MSG_MAP(CXCCMixerApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerApp construction

CXCCMixerApp::CXCCMixerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXCCMixerApp object

CXCCMixerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerApp initialization

BOOL CXCCMixerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	SetRegistryKey("XCC");

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	Cmix_file::enable_ft_support();
	xcc_dirs::load_from_registry();
	xcc_log::attach_file("XCC Mixer log.txt");
	if (mix_database::load())
	{
		xcc_dirs::reset_data_dir();
		mix_database::load();
	}
	mix_cache::load();
	mix_sfl::load();
	find_fs_exe();
	find_fa_exe();
	find_se_exe();
	string xcc_path = GetModuleFileName().get_path();
	m_xcc_av_player_exe = xcc_path + "XCC AV Player.exe";
	m_xcc_editor_exe = xcc_path + "XCC Editor.exe";
	m_xcc_mix_editor_exe = xcc_path + "XCC Mix Editor.exe";
	m_xcc_mixer_exe = xcc_path + "XCC Mixer.exe";
	m_dune2_exe = xcc_dirs::get_exe(game_dune2);
	m_td_dos_exe = xcc_dirs::get_td_primary_dir() + "c&c.com";
	m_td_win_exe = xcc_dirs::get_exe(game_td);
	m_ra_dos_exe = xcc_dirs::get_ra_dir() + "ra.exe";
	m_ra_win_exe = xcc_dirs::get_exe(game_ra);
	m_dune2000_exe = xcc_dirs::get_exe(game_dune2000);
	m_ts_exe = xcc_dirs::get_exe(game_ts);
	m_ra2_exe = xcc_dirs::get_exe(game_ra2);

	// Register document templates

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CXCCMixerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CXCCMixerView));
	AddDocTemplate(pDocTemplate);

	EnableShellOpen();
	RegisterShellFileTypes();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerApp commands

int CXCCMixerApp::ExitInstance() 
{
	mix_cache::save();
	xcc_dirs::save_to_registry();
	return CWinApp::ExitInstance();
}

void CXCCMixerApp::find_fs_exe()
{
	CIniFile f;
	char win_dir[256];
	if (!GetWindowsDirectory(win_dir, 256))
		return;
	if (f.LoadFile((static_cast<string>(win_dir) + "\\finalsun.ini").c_str()))
		return;
	m_fs_exe = f.sections["FinalSun"].values["Path"] + "finalsun.exe";
}

void CXCCMixerApp::find_fa_exe()
{
	CIniFile f;
	char win_dir[256];
	if (!GetWindowsDirectory(win_dir, 256))
		return;
	if (f.LoadFile((static_cast<string>(win_dir) + "\\finalalert.ini").c_str()))
		return;
	m_fa_exe = f.sections["FinalAlert"].values["Path"] + "finalalert.exe";
}

void CXCCMixerApp::find_se_exe()
{
	HKEY kh_base;
	HKEY kh_cps;
	char s[256];
	dword size;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software", 0, KEY_QUERY_VALUE, &kh_base) &&
		ERROR_SUCCESS == RegOpenKeyEx(kh_base, "Childs Play Software", 0, KEY_QUERY_VALUE, &kh_cps))
	{
		if (ERROR_SUCCESS == RegOpenKeyEx(kh_cps, "SunEdit2K", 0, KEY_QUERY_VALUE, &kh_base) &&
			ERROR_SUCCESS == RegQueryValueEx(kh_base, "AppPath", 0, 0, (byte*)s, &(size = 256)))
		{
			m_se_exe = s;
			m_se_exe += "se2k.exe";
		}
		if (ERROR_SUCCESS == RegOpenKeyEx(kh_cps, "SunEdit 2K ModMan", 0, KEY_QUERY_VALUE, &kh_base) &&
			ERROR_SUCCESS == RegQueryValueEx(kh_base, "AppPath", 0, 0, (byte*)s, &(size = 256)))
		{
			m_semm_exe = s;
			m_semm_exe += "se2kmm.exe";
		}
	}
}

string CXCCMixerApp::get_fs_exe() const
{
	return m_fs_exe;
}

string CXCCMixerApp::get_fa_exe() const
{
	return m_fa_exe;
}

string CXCCMixerApp::get_se_exe() const
{
	return m_se_exe;
}

string CXCCMixerApp::get_semm_exe() const
{
	return m_semm_exe;
}

string CXCCMixerApp::get_rage_exe() const
{
	return m_rage_exe;
}

string CXCCMixerApp::get_xcc_av_player_exe() const
{
	return m_xcc_av_player_exe;
}

string CXCCMixerApp::get_xcc_editor_exe() const
{
	return m_xcc_editor_exe;
}

string CXCCMixerApp::get_xcc_mix_editor_exe() const
{
	return m_xcc_mix_editor_exe;
}

string CXCCMixerApp::get_xcc_mixer_exe() const
{
	return m_xcc_mixer_exe;
}

string CXCCMixerApp::get_dune2_exe() const
{
	return m_dune2_exe;
}

string CXCCMixerApp::get_td_dos_exe() const
{
	return m_td_dos_exe;
}

string CXCCMixerApp::get_td_win_exe() const
{
	return m_td_win_exe;
}

string CXCCMixerApp::get_ra_dos_exe() const
{
	return m_ra_dos_exe;
}

string CXCCMixerApp::get_ra_win_exe() const
{
	return m_ra_win_exe;
}

string CXCCMixerApp::get_dune2000_exe() const
{
	return m_dune2000_exe;
}

string CXCCMixerApp::get_ts_exe() const
{
	return m_ts_exe;
}

string CXCCMixerApp::get_ra2_exe() const
{
	return m_ra2_exe;
}

bool CXCCMixerApp::is_fs_available() const
{
	return Cfname(m_fs_exe).exists();
}

bool CXCCMixerApp::is_fa_available() const
{
	return Cfname(m_fa_exe).exists();
}

bool CXCCMixerApp::is_se_available() const
{
	return Cfname(m_se_exe).exists();
}

bool CXCCMixerApp::is_semm_available() const
{
	return Cfname(m_semm_exe).exists();
}

bool CXCCMixerApp::is_rage_available() const
{
	return Cfname(m_rage_exe).exists();
}

bool CXCCMixerApp::is_xcc_av_player_available() const
{
	return Cfname(m_xcc_av_player_exe).exists();
}

bool CXCCMixerApp::is_xcc_editor_available() const
{
	return Cfname(m_xcc_editor_exe).exists();
}

bool CXCCMixerApp::is_xcc_mixer_available() const
{
	return Cfname(m_xcc_mixer_exe).exists();
}

bool CXCCMixerApp::is_xcc_mix_editor_available() const
{
	return Cfname(m_xcc_mix_editor_exe).exists();
}

bool CXCCMixerApp::is_dune2_available() const
{
	return Cfname(m_dune2_exe).exists();
}

bool CXCCMixerApp::is_td_dos_available() const
{
	return Cfname(m_td_dos_exe).exists();
}

bool CXCCMixerApp::is_td_win_available() const
{
	return Cfname(m_td_win_exe).exists();
}

bool CXCCMixerApp::is_ra_dos_available() const
{
	return Cfname(m_ra_dos_exe).exists();
}

bool CXCCMixerApp::is_ra_win_available() const
{
	return Cfname(m_ra_win_exe).exists();
}

bool CXCCMixerApp::is_dune2000_available() const
{
	return Cfname(m_dune2000_exe).exists();
}

bool CXCCMixerApp::is_ts_available() const
{
	return Cfname(m_ts_exe).exists();
}

bool CXCCMixerApp::is_ra2_available() const
{
	return Cfname(m_ra2_exe).exists();
}

BOOL CXCCMixerApp::OnIdle(LONG lCount) 
{
	return static_cast<CMainFrame*>(GetMainWnd())->OnIdle(lCount) || CWinApp::OnIdle(lCount);
}
