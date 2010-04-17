#pragma once

#include <string>
#include <vector>

class Circ_params
{
public:
	void clear();
	std::string read() const;
	void write(const std::string& v);
	const std::string& prefix() const;
	std::string prefix_nick() const;
	std::string prefix_user() const;
	std::string prefix_host() const;
	const std::string& operator[](size_t i) const;
	int p_int(int i) const;
	void p(int i, const std::string& v);
	void p(int i, int v);

	int count() const
	{
		return m_params.size();
	}
private:
	const std::string& p(size_t i) const;

	std::string m_prefix;
	std::vector<std::string> m_params;
};
