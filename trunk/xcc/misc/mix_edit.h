// mix_edit.h: interface for the Cmix_edit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIX_EDIT_H__6AB664E8_9EC9_4C9E_BD2E_D5E31354BAB9__INCLUDED_)
#define AFX_MIX_EDIT_H__6AB664E8_9EC9_4C9E_BD2E_D5E31354BAB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_structures.h"
#include "file32.h"
#include "mix_file.h"

class Cmix_edit  
{
public:
	static int cb_header(int size);
	void close();
	void clear();
	int compact();
	void erase(int id);
	void erase(const string& name);
	int id(const string& name) const;
	int insert(const string& name, Cvirtual_binary d);
	int open(const string& name);
	int write_index();
private:
	typedef map<int, t_mix_index_entry*> t_block_map;
	typedef map<int, t_mix_index_entry> t_index;

	t_block_map block_map();

	int new_block(int size);

	Cfile32 m_f;
	t_game m_game;
	t_index m_index;
};

#endif // !defined(AFX_MIX_EDIT_H__6AB664E8_9EC9_4C9E_BD2E_D5E31354BAB9__INCLUDED_)
