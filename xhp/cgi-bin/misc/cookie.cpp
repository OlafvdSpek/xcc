// cookie.cpp: implementation of the Ccookie class.
//
//////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4786)

#include "cgi.h"
#include "cookie.h"
#include "string_conversion.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ccookie::Ccookie()
{
}

Ccookie::Ccookie(const Cmulti_line& l)
{
	*this = l;
}

Ccookie::operator=(Cmulti_line v)
{
	while (!v.empty())
	{
		string name;
		string value;
		split_key(v.get_next_line(';'), name, value);
		trim(name);
		trim(value);
		m_read_keys[uri_decode(name)] = uri_decode(value);
	}
}

string Ccookie::get_value(const string& name) const
{
	t_keys::const_iterator i = m_read_keys.find(name);
	return i == m_read_keys.end() ? "" : i->second;
}

int Ccookie::get_value_int(const string& name) const
{
	return atoi(get_value(name).c_str());
}

bool Ccookie::has_value(const string& name) const
{
	t_keys::const_iterator i = m_read_keys.find(name);
	return i != m_read_keys.end();
}

void Ccookie::set_value(const string& name, int value)
{
	set_value(name, n(value));
}

void Ccookie::set_value(const string& name, const string& value)
{
	m_write_keys[name] = value;
}

void Ccookie::set_session_value(const string& name, int value)
{
	set_session_value(name, n(value));
}

void Ccookie::set_session_value(const string& name, const string& value)
{
	m_write_session_keys[name] = value;
}

ostream& operator<<(ostream& os, const Ccookie& v)
{
	Ccookie::t_keys::const_iterator i;
	for (i = v.m_write_keys.begin(); i != v.m_write_keys.end(); i++)
		os << "Set-cookie: " << uri_encode(i->first) + '=' + uri_encode(i->second) + "; expires=Sunday, 31-Dec-2000 12:00:00 GMT; path=/" << endl;
	for (i = v.m_write_session_keys.begin(); i != v.m_write_session_keys.end(); i++)
		os << "Set-cookie: " << uri_encode(i->first) + '=' + uri_encode(i->second) << endl;
	return os;
}