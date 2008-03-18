#pragma once

#include <map>
#include "cc_file_small.h"

using namespace std;

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
		t_index::const_iterator i = m_index.begin();
		while (index--)
			i++;
		return i->first;
	}

	int get_offset(const string& name) const
    {
        return m_index.find(name)->second.offset;
    }

    int get_size() const
	{
		return Ccc_file_small::get_size();
	}

	int get_size(const string& name) const
    {
        return m_index.find(name)->second.size;
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
