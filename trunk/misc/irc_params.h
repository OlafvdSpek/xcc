#pragma once

#include <string>
#include <vector>

class Circ_params
{
public:
	Circ_params(const std::string&);
	void clear();
	std::string read() const;
	const std::string& prefix() const;
	std::string prefix_nick() const;
	std::string prefix_user() const;
	std::string prefix_host() const;
	const std::string& operator[](size_t) const;
	int p_int(int i) const;
	void p(int i, const std::string&);
	void p(int i, int v);

	Circ_params() = default;

	int count() const
	{
		return m_params.size();
	}
private:
	std::string m_prefix;
	std::vector<std::string> m_params;
};
