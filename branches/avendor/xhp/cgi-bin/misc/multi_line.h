// multi_line.h: interface for the Cmulti_line class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTI_LINE_H__82C084C6_E2A2_11D2_B750_FE15CBEFD064__INCLUDED_)
#define AFX_MULTI_LINE_H__82C084C6_E2A2_11D2_B750_FE15CBEFD064__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>

using namespace std;

class Cmulti_line  
{
	string s;
public:
	Cmulti_line();
	Cmulti_line(const char* is);
	Cmulti_line(const string &is);
	int Cmulti_line::get_next_int(const char separator = ',');
	string get_next_line(const char separator = ',');
	string get_next_line(const string& separator);

	bool empty() const
	{
		return s.empty();
	};
};

#endif // !defined(AFX_MULTI_LINE_H__82C084C6_E2A2_11D2_B750_FE15CBEFD064__INCLUDED_)