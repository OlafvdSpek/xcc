#pragma once

class Chouse
{
public:
	const string& name() const
	{
		return name_;
	};

	Chouse() = default;
	Chouse(const map<string, string>&);
private:
	string name_;
};
