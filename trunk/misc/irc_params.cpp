#include "irc_params.h"

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <string_conversion.h>

using namespace boost;
using namespace std;

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
	BOOST_FOREACH(auto& i, m_params)
	{
		if (&i != &m_params.front())
			r += ' ';
		assert(!done);
		if (i.find(' ') != string::npos)
		{
			r += ':';
			done = true;
		}
		r += i;
	}
	return r;
}

Circ_params::Circ_params(const string& v)
{
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

const string& Circ_params::operator[](size_t i) const
{
	static string z;
	return i < m_params.size() ? m_params[i] : z;
}

int Circ_params::p_int(int i) const
{
	return atoi((*this)[i].c_str());
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
