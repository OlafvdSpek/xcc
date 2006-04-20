#if !defined(AFX_VIRTUAL_TFILE_WRITE_H__19828F36_5BAE_48B2_86F8_5F8D36C4A910__INCLUDED_)
#define AFX_VIRTUAL_TFILE_WRITE_H__19828F36_5BAE_48B2_86F8_5F8D36C4A910__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <strstream>

class Cvirtual_tfile_write  
{
public:
	Cvirtual_binary save();
	void write(const string& s);
	void write_line(const string& s);
private:
	ostrstream m_v;
};

#endif // !defined(AFX_VIRTUAL_TFILE_WRITE_H__19828F36_5BAE_48B2_86F8_5F8D36C4A910__INCLUDED_)
