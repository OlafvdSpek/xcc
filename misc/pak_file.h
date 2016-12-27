#pragma once

#include <map>
#include "cc_file_small.h"

class Cpak_file: public Ccc_file_small
{
public:
	void close();
	bool is_valid();
    int post_open();

	int get_c_files() const
	{
		return m_index.size();
	}

	string get_name(int index) const
	{
		return boost::next(m_index.begin(), index)->first;
	}

	int get_offset(const string& name) const
    {
        return find_ref(m_index, name).offset;
    }

    int get_size() const
	{
		return Ccc_file_small::get_size();
	}

	int get_size(const string& name) const
    {
        return find_ref(m_index, name).size;
    }
private:
	struct t_index_entry
	{
		int offset;
		int size;
	};
	typedef map<string, t_index_entry> t_index;
	t_index m_index;
};
