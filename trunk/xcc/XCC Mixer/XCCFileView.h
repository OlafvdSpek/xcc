// XCCFileView.h : header file
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCCFILEVIEW_H__9031C262_D8D9_11D3_9F8F_0000F81AF9BE__INCLUDED_)
#define AFX_XCCFILEVIEW_H__9031C262_D8D9_11D3_9F8F_0000F81AF9BE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <cc_file.h>
#include <mix_file.h>
#include <palet.h>
#include <vector>

struct t_text_cache_entry
{
	CRect text_extent;
	string t;
};

typedef vector<t_text_cache_entry> t_text_cache;

class CXCCFileView : public CScrollView
{
protected:
	CXCCFileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CXCCFileView)

// Attributes
public:

// Operations
public:
	BOOL OnIdle(LONG lCount);
	void close_f();
	const t_paletentry* get_default_palet();
	void load_color_table(const t_palet palet, bool convert_palet);
	void draw_image8(const byte* s, int cx_s, int cy_s, CDC* pDC, int x_d, int y_d);
	void draw_image24(const byte* s, int cx_s, int cy_s, CDC* pDC, int x_d, int y_d);
	void draw_info(string n, string d);
	void set_game(t_game game);
	void open_f(int id, Cmix_file& mix_f, t_game game, t_palet palet);
	void open_f(const string& name);
	void post_open(Ccc_file& f);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCFileView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CXCCFileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// Generated message map functions
	//{{AFX_MSG(CXCCFileView)
	afx_msg void OnDisable(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int				m_cb_data;
	CRect			m_clip_rect;
	dword			m_color_table[256];
	int				m_cx_dib;
	CDC*			m_dc;
	t_game			m_game;
	HBITMAP			mh_dib;
	dword*			mp_dib;
	CFont			m_font;
	t_file_type		m_ft;
	byte*			m_data;
	int				m_id;
	bool			m_is_open;
	t_paletentry*	m_palet;
	int				m_size;
	t_text_cache	m_text_cache;
	bool			m_text_cache_valid;
	int				m_x;
	int				m_y;
	int				m_y_inc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCFILEVIEW_H__9031C262_D8D9_11D3_9F8F_0000F81AF9BE__INCLUDED_)
