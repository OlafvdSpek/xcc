#pragma once

#include <string>
#include <vector>

class Circ_params
{
public:
	void clear();
	std::string read() const;
	static std::string strip(const std::string&);
	void write(const std::string& v);
	const std::string& prefix() const;
	std::string prefix_nick() const;
	std::string prefix_user() const;
	std::string prefix_host() const;
	const std::string& p(int i) const;
	bool p_equal(int i, const std::string& v) const;
	int p_int(int i) const;
	void p(int i, const std::string& v);
	void p(int i, int v);

	int count() const
	{
		return m_params.size();
	}
private:
	std::string m_prefix;
	std::vector<std::string> m_params;
};
