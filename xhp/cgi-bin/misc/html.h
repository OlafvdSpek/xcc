// html.h: interface for the Chtml class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTML_H__A9DC65D0_E86C_11D3_B0C6_0000F809802D__INCLUDED_)
#define AFX_HTML_H__A9DC65D0_E86C_11D3_B0C6_0000F809802D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>

using namespace std;

class Chtml  
{
public:
	Chtml();
	Chtml(const char* v);
	Chtml(const string& v);
	bool is_multi_line() const;
	Chtml operator+=(const Chtml& v);
	operator string() const;

	friend Chtml operator+(const Chtml& a, const Chtml& b);
private:
	string m_v;
};

Chtml fix_br(const string& v);
Chtml fix_endl(const string& v);
Chtml indent(const string& v);
// Chtml tag_ss();
// Chtml tag_sm(const string& tag, const Chtml& v);
Chtml tag_da(const string& tag, const Chtml& v, const string& elements = "");
Chtml tag_ds(const string& tag, const Chtml& v, const string& elements = "");
Chtml tag_dm(const string& tag, const Chtml& v, const string& elements = "");
Chtml a(const Chtml& v, const string& elements);
Chtml br(const Chtml& v = "");
Chtml center(const Chtml& v);
Chtml font(const Chtml& v, const string& elements);
Chtml form(const Chtml& v, const string& elements);
Chtml frameset(const Chtml& v, const string& elements);
Chtml head(const Chtml& v);
Chtml head_xcc();
Chtml head_xcc(const string& t);
Chtml html(const Chtml& v);
Chtml body(const Chtml& v);
Chtml hr();
Chtml p(const Chtml& v, const string& elements = "");
Chtml php(const Chtml& v);
Chtml pre(const Chtml& v, const string& elements = "");
Chtml table(const Chtml& v, const string& elements = "");
Chtml html_div(const Chtml& v, const string& elements = "");
Chtml html_span(const Chtml& v, const string& elements = "");
Chtml html_thead(const Chtml& v, const string& elements = "");
Chtml html_tbody(const Chtml& v, const string& elements = "");
Chtml html_tfoot(const Chtml& v, const string& elements = "");
Chtml html_ul(const Chtml& v, const string& elements = "");
Chtml td(const Chtml& v, const string& elements = "");
Chtml th(const Chtml& v, const string& elements = "");
Chtml tr(const Chtml& v);
Chtml textarea(const Chtml& v, const string& elements);
Chtml title(const Chtml& v);
Chtml html_option(const Chtml& v, const string& elements);
Chtml html_select(const Chtml& v, const string& elements);

Chtml operator+(const Chtml& a, const Chtml& b);

ostream& operator<<(ostream& os, const Chtml& v);

#endif // !defined(AFX_HTML_H__A9DC65D0_E86C_11D3_B0C6_0000F809802D__INCLUDED_)
