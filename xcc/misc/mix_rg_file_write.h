// mix_rg_file_write.h: interface for the Cmix_rg_file_write class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIX_RG_FILE_WRITE_H__17E1EABF_428A_4729_A534_5B5C07D9F2C0__INCLUDED_)
#define AFX_MIX_RG_FILE_WRITE_H__17E1EABF_428A_4729_A534_5B5C07D9F2C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "virtual_binary.h"

class Cmix_rg_file_write  
{
public:
	void clear();
	void insert(string name, const Cvirtual_binary d);
	Cvirtual_binary write();
private:
	typedef map<string, Cvirtual_binary> t_index;

	t_index m_index;
};

#endif // !defined(AFX_MIX_RG_FILE_WRITE_H__17E1EABF_428A_4729_A534_5B5C07D9F2C0__INCLUDED_)
