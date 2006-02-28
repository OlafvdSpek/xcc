#include "stdafx.h"
#include "irc_params.h"

#include <boost/algorithm/string.hpp>
#include "string_conversion.h"

using namespace boost;

void Circ_params::clear()
{
	m_prefix.erase();
	m_params.clear();
}

string Circ_params::read() const
{
	string r;
	if (!m_prefix.empty())
		r = ':' + m_prefix + ' ';
	bool done = false;
	for (t_params::const_iterator i = m_params.begin(); i != m_params.end(); i++)
	{
		if (i != m_params.begin())
			r += ' ';
		assert(!done);
		if (i->find(' ') != string::npos)
		{
			r += ':';
			done = true;
		}
		r += *i;
	}
	return r;
}

void Circ_params::write(const string& v)
{
	clear();
	if (v.empty())
		return;
	int i = 0;
	if (v[0] == ':')
	{
		int j = v.find(' ', 1);
		if (j == string::npos)
			return;
		m_prefix = v.substr(1, j - 1);
		i = j + 1;
	}
	int k = v.find(':', i);
	if (k == string::npos)
		k = v.length();
	while (i < k)
	{
		int j = v.find(' ', i);
		if (j == string::npos)
			j = v.length();
		j = min(j, k);
		string param = v.substr(i, j - i);
		m_params.push_back(param);
		i = j + 1;
	}
	if (k < v.length())
	{
		string param = v.substr(k + 1);
		m_params.push_back(param);
	}
}

const string& Circ_params::prefix() const
{
	return m_prefix;
}

string Circ_params::prefix_nick() const
{
	int i = m_prefix.find('!');
	return i == string::npos ? "" : m_prefix.substr(0, i);
}

string Circ_params::prefix_user() const
{
	int i = m_prefix.find('!');
	int j = m_prefix.find('@');
	if (j == string::npos)
		return "";
	if (i == string::npos)
		i = 0;
	else
		i++;
	return m_prefix.substr(i, j - i);
}

string Circ_params::prefix_host() const
{
	int i = m_prefix.find('@');
	return i == string::npos ? m_prefix : m_prefix.substr(i + 1);
}

const string& Circ_params::p(int i) const
{
	static string z;
	return i < m_params.size() ? m_params[i] : z;
}

bool Circ_params::p_equal(int i, const string& v) const
{
	return iequals(p(i), v);
}

int Circ_params::p_int(int i) const
{
	return atoi(p(i).c_str());
}

void Circ_params::p(int i, const string& v)
{
	while (i >= m_params.size())
		m_params.push_back("");
	m_params[i] = v;
}

void Circ_params::p(int i, int v)
{
	p(i, n(v));
}

string Circ_params::strip(const string& s)
{
	string d;
	d.reserve(s.length());
	for (const char* r = s.c_str(); *r; r++)
	{
		switch (*r)
		{
		case '\n':
		case '\r':
			break;
		default:
			d += *r;
		}
	}
	return d;
}
