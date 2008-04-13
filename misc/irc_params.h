#pragma once

#include <vector>

class Circ_params
{
public:
	void clear();
	string read() const;
	static string strip(const string&);
	void write(const string& v);
	const string& prefix() const;
	string prefix_nick() const;
	string prefix_user() const;
	string prefix_host() const;
	const string& p(int i) const;
	bool p_equal(int i, const string& v) const;
	int p_int(int i) const;
	void p(int i, const string& v);
	void p(int i, int v);

	int count() const
	{
		return m_params.size();
	}
private:
	typedef vector<string> t_params;

	string m_prefix;
	t_params m_params;
};
