// ini_reader.h: interface for the Cini_reader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INI_READER_H__FB64E122_71EC_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_INI_READER_H__FB64E122_71EC_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "vartypes.h"
#include "virtual_binary.h"

using namespace std;

class Cini_reader  
{
public:
	Cini_reader();
	static int find_id(const string& s, const char* t[], int count);
	int process(const byte* s, int cb_s);
	int process(const Cvirtual_binary s);
	int process_line(string line);
	virtual int process_section_start(const string& name) = 0;
	virtual bool process_section() const = 0;
	virtual int process_key(const string& name, const string& value) = 0;
	virtual void process_section_end();
	void fast(bool v);
	void lower_case(bool v);
	void skip_errors(bool v);
protected:
	bool m_fast;
	bool m_lower_case;
	bool m_section_open;
	bool m_skip_errors;
};

#endif // !defined(AFX_INI_READER_H__FB64E122_71EC_11D4_B606_0000B4936994__INCLUDED_)
