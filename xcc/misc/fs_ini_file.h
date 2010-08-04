#pragma once

class CIniFileSection
{
public:
	int FindName(string sval);
	int FindValue(string sval);
	const string* GetValueName(unsigned int Index);
	string* GetValue(unsigned int index);
	map<string, string> values;
};

class CIniFile  
{
public:
	CIniFileSection* GetSection(unsigned int index);
	int InsertFile(const char* filename, const char* Section);
	void Clear();
	int LoadFile(const char* filename);
	map<string, CIniFileSection> sections;
};
