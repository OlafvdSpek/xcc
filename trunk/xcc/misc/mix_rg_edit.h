// mix_rg_edit.h: interface for the Cmix_rg_edit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIX_RG_EDIT_H__6AB664E8_9EC9_4C9E_BD2E_D5E31354BAB9__INCLUDED_)
#define AFX_MIX_RG_EDIT_H__6AB664E8_9EC9_4C9E_BD2E_D5E31354BAB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_structures.h"
#include "file32.h"
#include "mix_rg_file.h"

class Cmix_rg_edit  
{
public:
	void close();
	void clear();
	int compact();
	void erase(const string& name);
	int insert(const string& name, Cvirtual_binary d);
	int open(const string& name);
	int write_index();
private:
	typedef map<int, t_mix_rg_index_entry*> t_block_map;
	typedef Cmix_rg_file::t_index t_index;

	t_block_map block_map();

	int new_block(int size);

	Cfile32 m_f;
	t_mix_rg_header m_header;
	t_index m_index;
	int m_index_size;
	int m_tailer_size;
};

#endif // !defined(AFX_MIX_RG_EDIT_H__6AB664E8_9EC9_4C9E_BD2E_D5E31354BAB9__INCLUDED_)
