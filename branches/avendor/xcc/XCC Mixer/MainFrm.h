// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__9452141A_D8CC_11D3_9F8E_0000F81AF9BE__INCLUDED_)
#define AFX_MAINFRM_H__9452141A_D8CC_11D3_9F8E_0000F81AF9BE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ddraw.h>
#include <mmsystem.h>
#include <dsound.h>
#include "cc_structures.h"
#include "mix_file.h"
#include "pal_file.h"
#include "XCCFileView.h"
#include "XCC MixerView.h"

struct t_pal_list_entry
{
	string name;
	t_palet palet;
};

typedef map<int, string> t_mix_list;
typedef map<int, t_pal_list_entry> t_pal_list;

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	void do_mix(Cmix_file& f, const string& mix_name);
	void find_mixs(const string& dir, t_game game);
	void find_paks(const string& dir, t_game game);
	void initialize_lists();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	void close_dd();
	void open_dd();
	LPDIRECTDRAW get_dd();
	void close_ds();
	void open_ds();
	LPDIRECTSOUND get_ds();
	t_game get_game();
	string get_mix_name(int i) const;
	const t_paletentry* get_game_palet(t_game game) const;
	const t_paletentry* get_pal_data() const;
	int get_vxl_mode() const;
	void set_msg(const string& s);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	bool convert_from_td() const
	{
		return m_convert_from_td;
	}

	bool convert_from_ra() const
	{
		return m_convert_from_ra;
	}

	bool remap_team_colors() const
	{
		return m_remap_team_colors;
	}

	bool split_shadows() const
	{
		return m_split_shadows;
	}

	bool use_palet_for_conversion() const
	{
		return m_use_palet_for_conversion;
	}
protected:  // control bar embedded members
	t_game m_game;
	t_palet m_td_palet;
	t_palet m_ra_palet;
	t_palet m_ts_palet;
	int m_palet_i;
	int m_vxl_mode;
	bool m_lists_initialized;
	int m_mix_i[6];
	int m_pal_i[6];
	t_mix_list m_mix_list;
	t_pal_list m_pal_list;
	bool m_convert_from_td;
	bool m_convert_from_ra;
	bool m_remap_team_colors;
	bool m_split_shadows;
	bool m_use_palet_for_conversion;
	CXCCMixerView* m_left_mix_pane;
	CXCCMixerView* m_right_mix_pane;
	CXCCFileView* m_file_info_pane;
	CSplitterWnd m_wndSplitter;
	CStatusBar m_wndStatusBar;
	LPDIRECTDRAW m_dd;
	LPDIRECTSOUND m_ds;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewGameTD();
	afx_msg void OnViewGameRA();
	afx_msg void OnViewGameTS();
	afx_msg void OnUpdateViewGameTD(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewGameRA(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewGameTS(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileFoundUpdate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewPaletUpdate(CCmdUI* pCmdUI);
	afx_msg void OnViewGameAuto();
	afx_msg void OnUpdateViewGameAuto(CCmdUI* pCmdUI);
	afx_msg void OnViewPaletAuto();
	afx_msg void OnUpdateViewPaletAuto(CCmdUI* pCmdUI);
	afx_msg void OnViewPalet(dword ID);
	afx_msg void OnUpdateViewPalet(CCmdUI* pCmdUI);
	afx_msg void OnViewPaletPrev();
	afx_msg void OnViewPaletNext();
	afx_msg void OnViewPaletUseForConversion();
	afx_msg void OnUpdateViewPaletUseForConversion(CCmdUI* pCmdUI);
	afx_msg void OnViewPaletConvertFromTD();
	afx_msg void OnUpdateViewPaletConvertFromTD(CCmdUI* pCmdUI);
	afx_msg void OnViewPaletConvertFromRA();
	afx_msg void OnUpdateViewPaletConvertFromRA(CCmdUI* pCmdUI);
	afx_msg void OnInternetFsSite();
	afx_msg void OnInternetSeSite();
	afx_msg void OnInternetXccSite();
	afx_msg void OnViewVoxelNormal();
	afx_msg void OnUpdateViewVoxelNormal(CCmdUI* pCmdUI);
	afx_msg void OnViewVoxelSurfaceNormals();
	afx_msg void OnUpdateViewVoxelSurfaceNormals(CCmdUI* pCmdUI);
	afx_msg void OnViewVoxelDepthInformation();
	afx_msg void OnUpdateViewVoxelDepthInformation(CCmdUI* pCmdUI);
	afx_msg void OnConversionSplitShadows();
	afx_msg void OnUpdateConversionSplitShadows(CCmdUI* pCmdUI);
	afx_msg void OnConversionRemapTeamColors();
	afx_msg void OnUpdateConversionRemapTeamColors(CCmdUI* pCmdUI);
	afx_msg void OnInternetGeniusSite();
	afx_msg void OnUtilitiesXccAvPlayer();
	afx_msg void OnUpdateUtilitiesXccAvPlayer(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesXccEditor();
	afx_msg void OnUpdateUtilitiesXccEditor(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesXccMixEditor();
	afx_msg void OnUpdateUtilitiesXccMixEditor(CCmdUI* pCmdUI);
	afx_msg void OnViewDirectories();
	afx_msg void OnViewDirectxOptions();
	afx_msg void OnUtilitiesFS();
	afx_msg void OnUpdateUtilitiesFS(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesSEMM();
	afx_msg void OnUpdateUtilitiesSEMM(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesSE();
	afx_msg void OnUpdateUtilitiesSE(CCmdUI* pCmdUI);
	afx_msg void OnLaunchDune2();
	afx_msg void OnLaunchTD();
	afx_msg void OnLaunchRA();
	afx_msg void OnLaunchDune2000();
	afx_msg void OnLaunchRA2();
	afx_msg void OnLaunchTS();
	afx_msg void OnUpdateLaunchDune2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLaunchDune2000(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLaunchRA(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLaunchRA2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLaunchTD(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLaunchTS(CCmdUI* pCmdUI);
	afx_msg void OnLaunchXccThemeWriter();
	afx_msg void OnUpdateLaunchXccThemeWriter(CCmdUI* pCmdUI);
	afx_msg void OnFileSearch();
	afx_msg void OnFileCreateSFL();
	afx_msg void OnLaunchXOE_RA2();
	afx_msg void OnUpdateLaunchXOE_RA2(CCmdUI* pCmdUI);
	afx_msg void OnLaunchXOE_TS();
	afx_msg void OnUpdateLaunchXOE_TS(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__9452141A_D8CC_11D3_9F8E_0000F81AF9BE__INCLUDED_)
