#pragma once

#include "../game spy/game_state.h"
#include "map_ts_encoder.h"

class CXCCGameSpyPlayerView : public CView
{
protected: // create from serialization only
	CXCCGameSpyPlayerView();
	DECLARE_DYNCREATE(CXCCGameSpyPlayerView)

public:
	CXCCGameSpyPlayerDoc* GetDocument();

public:

	//{{AFX_VIRTUAL(CXCCGameSpyPlayerView)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

public:
	const Cgame_state& get_game_state(int i);
	void read_map(string name);
	void clear_terrain_map();
	COLORREF player_color(int id, int v) const;
	void transform(int x1, int y1, int& x2, int& y2);
	void shot_time(int v);
	void rewind();
	void move_front(int i = 1);
	void move_back(int i = 1);
	void read_log();
	virtual ~CXCCGameSpyPlayerView();

protected:

protected:
	//{{AFX_MSG(CXCCGameSpyPlayerView)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnViewNonHumanObjects();
	afx_msg void OnUpdateViewNonHumanObjects(CCmdUI* pCmdUI);
	afx_msg void OnViewObjectSummary();
	afx_msg void OnUpdateViewObjectSummary(CCmdUI* pCmdUI);
	afx_msg void OnViewTerrain();
	afx_msg void OnUpdateViewTerrain(CCmdUI* pCmdUI);
	afx_msg void OnViewNames();
	afx_msg void OnUpdateViewNames(CCmdUI* pCmdUI);
	afx_msg void OnViewHistory();
	afx_msg void OnUpdateViewHistory(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	typedef vector<Cgame_state> t_game_state_cache;

	Cvirtual_binary m_terrain_colormap;
	CRect m_map_limits;
	Cobject_types m_object_types;
	CDC m_mem_dc;
	CDC m_terrain_dc;
	CSize m_mem_dc_size;
	bool m_mem_dc_valid;
	bool m_terrain_dc_valid;
	HBITMAP mh_dib;
	HBITMAP mh_terrain_dib;
	bool m_center_map;
	t_iso_map_pack_entry4 m_terrain_map[512][512];
	int m_shot_time;
	bool m_auto_forward;
	bool m_show_history;
	bool m_show_names;
	bool m_show_terrain;
	bool m_view_non_human_objects;
	bool m_view_object_summary;
	int m_min_z;
	int m_max_z;

	Cgame_state m_game_state;
	t_game_state_cache m_game_state_cache;
	int m_game_state_i;
	int m_replay_time;
};

inline CXCCGameSpyPlayerDoc* CXCCGameSpyPlayerView::GetDocument()
   { return (CXCCGameSpyPlayerDoc*)m_pDocument; }
