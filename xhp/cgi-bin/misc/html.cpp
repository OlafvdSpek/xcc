// html.cpp: implementation of the Chtml class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "html.h"
#include "string_conversion.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Chtml::Chtml()
{
}

Chtml::Chtml(const char* v)
{
	m_v = v;
}

Chtml::Chtml(const string& v)
{
	m_v = v;
}

Chtml::operator string() const
{
	return m_v;
}

Chtml Chtml::operator+=(const Chtml& v)
{
	if (v.is_multi_line())
		m_v = fix_endl(m_v);
	m_v += v.m_v;
	return *this;
}

bool Chtml::is_multi_line() const
{
	return m_v.find('\n') != string::npos;
}

Chtml fix_br(const string& v)
{
	string r;
	int i = 0;
	while (i < v.length())
	{
		char c = v[i++];
		switch (c)
		{
		case '\r':
			break;
		case '\n':
			r += "<br>\n";
			break;
		default:
			r += c;
		}
	}
	return r;
};

Chtml fix_endl(const string& v)
{
#ifdef NDEBUG
	return v;
#else
	return v.length() && v[v.length() - 1] == '\n' ? v : v + '\n';
#endif
};

Chtml indent(const string& v)
{
#ifdef NDEBUG
	return v;
#else
	string r;
	bool ta = false;
	int i = 0;
	while (i < v.length())
	{
		int p = v.find('\n', i);
		string line;
		if (p == string::npos)
		{
			line = v.substr(i) + '\n';
			p = v.length();
		}
		else
			line = v.substr(i, p - i + 1);
		if (!ta)
			r += '\t';
		r += line;
		i = p + 1;
		if (line.find("</pre>") != string::npos || line.find("</textarea>") != string::npos)
			ta = false;
		else if (line.find("<pre") != string::npos || line.find("<textarea") != string::npos)
			ta = true;
	}
	return r;
#endif
}

Chtml tag_da(const string& name, const Chtml& v, const string& elements)
{
#ifdef NDEBUG
	return tag_ds(name, v, elements);
#else
	if (v.is_multi_line())
		return tag_dm(name, v, elements);
	else
		return tag_ds(name, v, elements);
#endif
}

Chtml tag_ds(const string& name, const Chtml& v, const string& elements)
{
	return "<" + name + (elements.empty() ? "" : " " + elements) + ">" + static_cast<string>(v) + "</" + name + ">";
}

Chtml tag_dm(const string& name, const Chtml& v, const string& elements)
{
#ifdef NDEBUG
	return tag_ds(name, v, elements);
#else
	return "<" + name + (elements.empty() ? "" : " " + elements) + ">\n" + static_cast<string>(indent(v)) + "</" + name + ">\n";
#endif
}

Chtml html(const Chtml& v)
{
	return tag_dm("html", v);
}

Chtml body(const Chtml& v, const string& elements)
{
	return tag_dm("body", v, elements);
}

Chtml head(const Chtml& v)
{
	return tag_dm("head", v);
}

Chtml head_xcc()
{
	return tag_dm("head", 
		"<base href=http://xcc.tiberian.com/>\n" 
		"<link rel=stylesheet href=/xcc.css>\n");
}

Chtml head_xcc(const string& t)
{
	return tag_dm("head", 
		"<base href=http://xcc.tiberian.com/>\n" 
		"<link rel=stylesheet href=/xcc.css>\n" +
		title(t));
}

Chtml a(const Chtml& v, const string& elements)
{
	return tag_da("a", v, elements);
}

Chtml br(const Chtml& v)
{
	return static_cast<string>(v) + "<br>\n";
}

Chtml center(const Chtml& v)
{
	return tag_da("center", v);
}

Chtml html_div(const Chtml& v, const string& elements)
{
	return tag_dm("div", v, elements);
}

Chtml font(const Chtml& v, const string& elements)
{
	return tag_da("font", v, elements);
}

Chtml form(const Chtml& v, const string& elements)
{
	return tag_dm("form", v, elements);
}

Chtml frameset(const Chtml& v, const string& elements)
{
	return tag_dm("frameset", v, elements);
}

Chtml hr()
{
	return "<hr>\n";
}

Chtml p(const Chtml& v, const string& elements)
{
	return (elements.empty() ? "<p>\n" : "<p " + elements + ">\n") + indent(v);
}

Chtml php(const Chtml& v)
{
	return "<?php\n" + indent(v) + "?>\n";
}

Chtml pre(const Chtml& v, const string& elements)
{
	return tag_ds("pre", v, elements);
}

Chtml table(const Chtml& v, const string& elements)
{
	return tag_dm("table", v, elements);
}

Chtml html_thead(const Chtml& v, const string& elements)
{
	return tag_dm("thead", v, elements);
}

Chtml html_tbody(const Chtml& v, const string& elements)
{
	return tag_dm("tbody", v, elements);
}

Chtml html_tfoot(const Chtml& v, const string& elements)
{
	return tag_dm("tfoot", v, elements);
}

Chtml td(const Chtml& v, const string& elements)
{
	return tag_da("td", v, elements);
}

Chtml th(const Chtml& v, const string& elements)
{
	return tag_da("th", v, elements);
}

Chtml textarea(const Chtml& v, const string& elements)
{
	return tag_ds("textarea", v, elements);
}

Chtml title(const Chtml& v)
{
	return tag_da("title", v);
}

Chtml tr(const Chtml& v)
{
	return tag_dm("tr", v);
}

Chtml html_option(const Chtml& v, const string& elements)
{
	return tag_da("option", v, elements);
}

Chtml html_select(const Chtml& v, const string& elements)
{
	return tag_da("select", v, elements);
}

Chtml html_span(const Chtml& v, const string& elements)
{
	return tag_da("span", v, elements);
}

Chtml html_ul(const Chtml& v, const string& elements)
{
	return tag_dm("ul", v, elements);
}

Chtml operator+(const Chtml& a, const Chtml& b)
{
	return (b.is_multi_line() ? fix_endl(a.m_v).m_v : a.m_v) + b.m_v;
}

ostream& operator<<(ostream& os, const Chtml& v)
{
	return os << static_cast<string>(v);
}

