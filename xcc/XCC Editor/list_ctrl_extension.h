#if !defined(AFX_LIST_CTRL_EXTENSION_H__C3C44884_09F3_11D3_B601_00484AC10154__INCLUDED_)
#define AFX_LIST_CTRL_EXTENSION_H__C3C44884_09F3_11D3_B601_00484AC10154__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// list_ctrl_extension.h : header file
//

#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Clist_ctrl_extension window

class Clist_ctrl_extension : public CListCtrl
{
// Construction
public:
	Clist_ctrl_extension();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Clist_ctrl_extension)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	int get_focused_item() const;
	void add_column(const string& text, int index, int format = LVCFMT_LEFT);
	void add_item(const string& text, int index, int user_parameter = 0);
	void set_item(const string& text, int index, int subindex);
	void autosize_columns();
	void set_fixed_width_font();

	// Generated message map functions
protected:
	//{{AFX_MSG(Clist_ctrl_extension)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CFont m_font;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIST_CTRL_EXTENSION_H__C3C44884_09F3_11D3_B601_00484AC10154__INCLUDED_)
