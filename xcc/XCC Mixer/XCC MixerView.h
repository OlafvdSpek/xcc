// XCC MixerView.h : interface of the CXCCMixerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCCMIXERVIEW_H__9452141E_D8CC_11D3_9F8E_0000F81AF9BE__INCLUDED_)
#define AFX_XCCMIXERVIEW_H__9452141E_D8CC_11D3_9F8E_0000F81AF9BE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <map>
#include <mix_file.h>
#include <stack>
#include "fname.h"

struct t_index_entry
{
	string description;
	t_file_type ft;
	string name;
	int size;
};

typedef map<int, t_index_entry, less<int> > t_index;

typedef vector<int> t_index_selected;

typedef stack<Cmix_file*> t_location;

class CXCCMixerView : public CListView
{
protected: // create from serialization only
	CXCCMixerView();
	DECLARE_DYNCREATE(CXCCMixerView)
public:
	bool can_accept() const;
	bool can_copy();
	bool can_copy_as(t_file_type ft);
	bool can_delete();
	void clear_list();
	void close_all_locations();
	void close_location(int reload);
	int copy(int i, Cfname fname) const;
	void copy_as(t_file_type ft) const;
	int copy_as_aud(int i, Cfname fname) const;
	int copy_as_avi(int i, Cfname fname) const;
	int copy_as_cps(int i, Cfname fname) const;
	int copy_as_csv(int i, Cfname fname) const;
	int copy_as_html(int i, Cfname fname) const;
	int copy_as_hva(int i, Cfname fname) const;
	int copy_as_map_ts_preview(int i, Cfname fname) const;
	int copy_as_pal(int i, Cfname fname) const;
	int copy_as_pal_jasc(int i, Cfname fname) const;
	int copy_as_pcx(int i, Cfname fname, t_file_type ft) const;
	int copy_as_shp(int i, Cfname fname) const;
	int copy_as_shp_ts(int i, Cfname fname) const;
	int copy_as_text(int i, Cfname fname) const;
	int copy_as_tmp_ts(int i, Cfname fname) const;
	int copy_as_vxl(int i, Cfname fname) const;
	int copy_as_wav(int i, Cfname fname) const;
	int copy_as_xif(int i, Cfname fname) const;
	int get_current_id() const;
	int get_current_index() const;
	const t_paletentry* get_default_palet() const;
	string get_dir() const;
	int get_id(int i) const;
	int compare(int a, int b) const;
	int open_f_id(Ccc_file& f, int id) const;
	int open_f_index(Ccc_file& f, int i) const;
	void open_location_dir(const string& name);
	void open_location_mix(const string& name);
	void open_location_mix(int id);
	void set_other_panes(CXCCFileView* file_view_pane, CXCCMixerView* other_pane);
	void sort_list(int i);
	void update_list();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCMixerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	t_game get_game();
	virtual ~CXCCMixerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CXCCMixerView)
	afx_msg void OnFileOpen();
	afx_msg void OnFileClose();
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateFileClose(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPopupExtract();
	afx_msg void OnUpdatePopupExtract(CCmdUI* pCmdUI);
	afx_msg void OnFileFound(dword ID);
	afx_msg void OnPopupCopy();
	afx_msg void OnUpdatePopupCopy(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsAUD();
	afx_msg void OnUpdatePopupCopyAsAUD(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsAVI();
	afx_msg void OnUpdatePopupCopyAsAVI(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsCPS();
	afx_msg void OnUpdatePopupCopyAsCPS(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsPCX();
	afx_msg void OnUpdatePopupCopyAsPCX(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsSHP();
	afx_msg void OnUpdatePopupCopyAsSHP(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsWAV();
	afx_msg void OnUpdatePopupCopyAsWAV(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsWSA();
	afx_msg void OnUpdatePopupCopyAsWSA(CCmdUI* pCmdUI);
	afx_msg void OnPopupDelete();
	afx_msg void OnUpdatePopupDelete(CCmdUI* pCmdUI);
	afx_msg void OnPopupOpen();
	afx_msg void OnUpdatePopupOpen(CCmdUI* pCmdUI);
	afx_msg void OnPopupOpenForEdit();
	afx_msg void OnUpdatePopupOpenForEdit(CCmdUI* pCmdUI);
	afx_msg void OnPopupOpenWithFinalsun();
	afx_msg void OnUpdatePopupOpenWithFinalsun(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsVXL();
	afx_msg void OnUpdatePopupCopyAsVXL(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsXIF();
	afx_msg void OnUpdatePopupCopyAsXIF(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsCSV();
	afx_msg void OnUpdatePopupCopyAsCSV(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsHVA();
	afx_msg void OnUpdatePopupCopyAsHVA(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsPAL();
	afx_msg void OnUpdatePopupCopyAsPAL(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsShHP_TS();
	afx_msg void OnUpdatePopupCopyAsSHP_TS(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsTMP_TS();
	afx_msg void OnUpdatePopupCopyAsTMP_TS(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsPAL_JASC();
	afx_msg void OnUpdatePopupCopyAsPAL_JASC(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsText();
	afx_msg void OnUpdatePopupCopyAsText(CCmdUI* pCmdUI);
	afx_msg void OnPopupPlay();
	afx_msg void OnUpdatePopupPlay(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsMapTsPreview();
	afx_msg void OnUpdatePopupCopyAsMapTsPreview(CCmdUI* pCmdUI);
	afx_msg void OnPopupRefresh();
	afx_msg void OnUpdatePopupRefresh(CCmdUI* pCmdUI);
	afx_msg void OnPopupResize();
	afx_msg void OnUpdatePopupResize(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsHTML();
	afx_msg void OnUpdatePopupCopyAsHTML(CCmdUI* pCmdUI);
	afx_msg void OnPopupImportIntoTS();
	afx_msg void OnUpdatePopupImportIntoTS(CCmdUI* pCmdUI);
	afx_msg void OnPopupImportIntoRa2();
	afx_msg void OnUpdatePopupImportIntoRa2(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyAsPNG();
	afx_msg void OnUpdatePopupCopyAsPNG(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	string m_dir;
	t_index m_index;
	t_index_selected m_index_selected;
	t_location	m_location;
	Cmix_file*	m_mix_f;
	CXCCFileView* m_file_view_pane;
	CXCCMixerView* m_other_pane;
	t_game m_game;
	t_palet m_palet;
	bool m_palet_loaded;
	int m_sort_column;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMIXERVIEW_H__9452141E_D8CC_11D3_9F8E_0000F81AF9BE__INCLUDED_)
