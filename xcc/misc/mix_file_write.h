// mix_file_write.h: interface for the Cmix_file_write class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIX_FILE_WRITE_H__DA164780_9581_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_MIX_FILE_WRITE_H__DA164780_9581_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <string>
#include "cc_structures.h"
#include "virtual_binary.h"
#include "xcc_lmd_file_write.h"

using namespace std;

class Cmix_file_write  
{
public:
	void add_file(int id, const Cvirtual_binary d);
	void add_file(string name, const Cvirtual_binary d);
	// void add_file(string name, Cmix_file_write& s);
	Cvirtual_binary write();
	// int write(string fname);
private:
	typedef map<int, Cvirtual_binary> t_index;

	int write_start();
	int write(byte* d) const;

	t_index m_index;
	Cxcc_lmd_file_write m_lmd_fw;
};

#endif // !defined(AFX_MIX_FILE_WRITE_H__DA164780_9581_11D4_B606_0000B4936994__INCLUDED_)
