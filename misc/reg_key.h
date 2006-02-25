#if !defined(AFX_REG_KEY_H__1B4143AA_5A7E_4DB9_9B06_58D6B9D32CBD__INCLUDED_)
#define AFX_REG_KEY_H__1B4143AA_5A7E_4DB9_9B06_58D6B9D32CBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "windows.h"

class Creg_key
{
public:
	Creg_key();
	Creg_key(HKEY, const string& name, REGSAM sam_desired);
	Creg_key(const Creg_key&, const string& name, REGSAM sam_desired);
	~Creg_key();
	LONG create(HKEY key, const string& name);
	LONG open(HKEY, const string& name, REGSAM sam_desired);
	LONG open(const Creg_key&, const string& name, REGSAM sam_desired);
	LONG close();
	LONG query_value(const string& name, string& value);
	string query_value(const string& name);
	LONG set_value(const string& name, const string& value);
private:
	Creg_key(const Creg_key&);
	HKEY m_h;
};

#endif // !defined(AFX_REG_KEY_H__1B4143AA_5A7E_4DB9_9B06_58D6B9D32CBD__INCLUDED_)
