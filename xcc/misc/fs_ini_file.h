// IniFile.h: Schnittstelle für die Klasse CIniFile.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__96455620_6528_11D3_99E0_DB2A1EF71411__INCLUDED_)
#define AFX_INIFILE_H__96455620_6528_11D3_99E0_DB2A1EF71411__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <map>
#include <fstream>
#include <string>

using namespace std;

class CIniFileSection
{
public:
	int FindName(string sval);
	int FindValue(string sval);
	const string* GetValueName(unsigned int Index);
	string* GetValue(unsigned int index);
	map<string, string> values;
	CIniFileSection();
	~CIniFileSection();
};

class CIniFile  
{
public:
	// bool SaveFile(const char* Filename);
	// const string* GetSectionName(unsigned int Index);
	CIniFileSection* GetSection(unsigned int index);
	int InsertFile(const char* filename, const char* Section);
	void Clear();
	int LoadFile(const char* filename);
	map<string, CIniFileSection> sections;
	CIniFile();
	~CIniFile();
private:
	// char m_filename[MAX_PATH];
};

#endif // !defined(AFX_INIFILE_H__96455620_6528_11D3_99E0_DB2A1EF71411__INCLUDED_)
