#pragma once

class Chouse
{
public:
	string name() const
	{
		return m_name;
	};

	Chouse();
	Chouse(const map<string, string>&);
private:
	string m_name;
};
