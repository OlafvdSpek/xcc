// html_template.h: interface for the Chtml_template class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTML_TEMPLATE_H__FA584987_2EA1_11D5_B606_0000B4936994__INCLUDED_)
#define AFX_HTML_TEMPLATE_H__FA584987_2EA1_11D5_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include "virtual_binary.h"

class Chtml_template  
{
public:
	string apply(Chtml_template v);
	string apply(Cvirtual_binary v);
	void r(string name, int value);
	void r(string name, string value);
	operator string() const;
	Chtml_template operator =(Cvirtual_binary v);
	Chtml_template();
	Chtml_template(Cvirtual_binary v);
private:
	typedef map<string, string> t_map;

	t_map m_map;
	Cvirtual_binary m_value;
};

class Ctemplate_write
{
public:
	void clear();
	int import_line(string s);
	Cvirtual_binary value();
	Ctemplate_write();
	
	string name() const
	{
		return m_name;
	}

	bool repeat_line() const
	{
		return m_repeat_line;
	}	
private:
	void open_literal();
	void close_literal();
	
	Cvirtual_binary m_d;
	char* m_w;
	bool m_literal_open;
	bool m_repeat_line;
	string m_name;
};


#endif // !defined(AFX_HTML_TEMPLATE_H__FA584987_2EA1_11D5_B606_0000B4936994__INCLUDED_)
