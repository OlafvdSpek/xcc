// big_file.h: interface for the Cbig_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIG_FILE_H__F3E4434D_A9F6_40D7_AB78_5BA685414A17__INCLUDED_)
#define AFX_BIG_FILE_H__F3E4434D_A9F6_40D7_AB78_5BA685414A17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "cc_file.h"
#include "cc_structures.h"

class Cbig_file: public Ccc_file  
{
public:
	typedef map<string, t_big_index_entry> t_index;
	typedef vector<string> t_old_index;

	int get_c_files() const
	{
		return m_index.size();
	}

	string get_name(int index) const
	{
		return m_old_index[index];
	}

	int get_offset(const string& name) const
    {
        return m_index.find(name)->second.offset;
    }

    int get_size() const
	{
		return Ccc_file::get_size();
	}

	int get_size(const string& name) const
    {
        return m_index.find(name)->second.size;
    }

	const t_index& index() const
	{
		return m_index;
	}

	bool is_valid();
	int post_open();
	Cbig_file();
private:
	t_index m_index;
	t_old_index m_old_index;
};

#endif // !defined(AFX_BIG_FILE_H__F3E4434D_A9F6_40D7_AB78_5BA685414A17__INCLUDED_)
