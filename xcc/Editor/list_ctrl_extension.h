#pragma once

#include <string>

using namespace std;

class Clist_ctrl_extension : public CListCtrl
{
public:
	//{{AFX_VIRTUAL(Clist_ctrl_extension)
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
public:
	int get_focused_item() const;
	void add_column(const string& text, int index, int format = LVCFMT_LEFT);
	void add_item(const string& text, int index, int user_parameter = 0);
	void set_item(const string& text, int index, int subindex);
	void autosize_columns();
	void set_fixed_width_font();
protected:
	//{{AFX_MSG(Clist_ctrl_extension)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CFont m_font;
};
