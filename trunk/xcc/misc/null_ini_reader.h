// null_ini_reader.h: interface for the Cnull_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NULL_INI_READER_H__06E64C82_7C49_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_NULL_INI_READER_H__06E64C82_7C49_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ini_reader.h"

class Cnull_ini_reader: public Cini_reader  
{
public:
	Cnull_ini_reader()
	{
		mc_sections = 0;
	}

	int process_section_start(const string& line)
	{
		mc_sections++;
		return 0;
	}

	bool process_section() const
	{
		return true;
	}
	
	int process_key(const string& name, const string& value)
	{
		return 0;
	}

	bool is_valid() const
	{
		return mc_sections;
	}
private:
	int mc_sections;
};

#endif // !defined(AFX_NULL_INI_READER_H__06E64C82_7C49_11D4_B606_0000B4936994__INCLUDED_)
