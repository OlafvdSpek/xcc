// big_file_write.h: interface for the Cbig_file_write class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIG_FILE_WRITE_H__74B8F9C6_BEB8_4133_9CAB_A1F6315B5B1C__INCLUDED_)
#define AFX_BIG_FILE_WRITE_H__74B8F9C6_BEB8_4133_9CAB_A1F6315B5B1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "virtual_binary.h"

class Cbig_file_write  
{
public:
	void clear();
	void insert(const string& name, const Cvirtual_binary& d);
	Cvirtual_binary write();
private:
	typedef map<string, Cvirtual_binary> t_index;

	t_index m_index;
};

#endif // !defined(AFX_BIG_FILE_WRITE_H__74B8F9C6_BEB8_4133_9CAB_A1F6315B5B1C__INCLUDED_)
