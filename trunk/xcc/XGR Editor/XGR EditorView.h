// XGR EditorView.h : interface of the CXGREditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XGREDITORVIEW_H__50861FF9_FEDA_43A4_9591_732831C0F504__INCLUDED_)
#define AFX_XGREDITORVIEW_H__50861FF9_FEDA_43A4_9591_732831C0F504__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gr_ini_reader.h"

class CXGREditorView : public CListView
{
protected: // create from serialization only
	CXGREditorView();
	DECLARE_DYNCREATE(CXGREditorView)

// Attributes
public:
	CXGREditorDoc* GetDocument()
	{ 
		return (CXGREditorDoc*)m_pDocument; 
	}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXGREditorView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	void close();
	void open(const Cvirtual_binary& d);
	virtual ~CXGREditorView();

protected:
	void insert_section(int l, const Cgr_ini_reader::Csection& section);

// Generated message map functions
protected:
	//{{AFX_MSG(CXGREditorView)
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	string m_buffer[4];
	int m_buffer_w;
	Cgr_ini_editor m_ini;

	struct t_map_entry
	{
		int l;
		const Cgr_ini_editor::Csection* section;

		t_map_entry()
		{
		}

		t_map_entry(int _l, const Cgr_ini_editor::Csection* _section)
		{
			l = _l;
			section = _section;
		}
	};

	typedef map<int, t_map_entry> t_map;

	t_map m_map;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XGREDITORVIEW_H__50861FF9_FEDA_43A4_9591_732831C0F504__INCLUDED_)
