// cookie.h: interface for the Ccookie class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COOKIE_H__8AD9C520_EC76_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_COOKIE_H__8AD9C520_EC76_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <string>
#include "multi_line.h"

using namespace std;

class Ccookie
{
public:
	string get_value(const string& name) const;
	int get_value_int(const string& name) const;
	bool has_value(const string& name) const;
	void set_value(const string& name, int value);
	void set_value(const string& name, const string& value);
	void set_session_value(const string& name, int value);
	void set_session_value(const string& name, const string& value);
	Ccookie();
	Ccookie(const Cmulti_line& l);
	operator=(Cmulti_line l);
	friend ostream& operator<<(ostream& os, const Ccookie& v);
private:
	typedef map<string, string> t_keys;
	t_keys m_read_keys;
	t_keys m_write_keys;
	t_keys m_write_session_keys;
};

ostream& operator<<(ostream& os, const Ccookie& v);

#endif // !defined(AFX_COOKIE_H__8AD9C520_EC76_11D3_B605_0000B4936994__INCLUDED_)
