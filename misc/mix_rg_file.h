#pragma once

#include <vector>
#include "cc_file.h"
#include "cc_structures.h"

using namespace std;

class Cmix_rg_file: public Ccc_file
{
public:
	typedef map<string, t_mix_rg_index_entry> t_index;
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
	Cmix_rg_file();
private:
	t_index m_index;
	t_old_index m_old_index;
};
