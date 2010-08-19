#pragma once

struct t_house_data
{
	const char* name;
};

class Chouse
{
public:
	string name() const
	{
		return m_name;
	};

	void load(t_house_data d);
	Chouse();
	Chouse(const map<string, string>&);
private:
	string m_name;
};
