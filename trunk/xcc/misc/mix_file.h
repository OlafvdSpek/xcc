// mix_file.h: interface for the Cmix_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIX_FILE_H__6AA2E061_D405_11D3_8684_0000F81AF605__INCLUDED_)
#define AFX_MIX_FILE_H__6AA2E061_D405_11D3_8684_0000F81AF605__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "cc_file.h"
#include "cc_structures.h"

class Cmix_file: public Ccc_file  
{
public:
    int post_open();
	t_file_type get_type(int id);
	string get_name(int id);
    static int get_id(t_game game, string name);
    int get_index(unsigned int id) const;
	Ccc_file::get_size;
	Ccc_file::get_vdata;
	Cvirtual_binary get_vdata(int id);
	Cvirtual_binary get_vdata(const string& name);
	bool is_valid();
	void close();
	Cmix_file();

    static void enable_ft_support()
	{
		assert(!m_ft_support);
		m_ft_support = true;
	}

	void enable_mix_expansion()
	{
		assert(!m_mix_expansion);
		m_mix_expansion = true;
	}

	int get_c_files() const
	{
		return m_c_files;
	}

	t_game get_game() const
	{
		return m_game;
	}

	void set_game(t_game game)
	{
		m_game = game;
	}

	int get_id(int index) const
	{
		return m_index[index].id;
	}

	int get_offset(unsigned int id) const
    {
        return m_index[get_index(id)].offset;
    }

	int get_size(unsigned int id) const
    {
        return m_index[get_index(id)].size;
    }

	bool has_checksum() const
	{
		return m_has_checksum;	
	}

	bool is_encrypted() const
	{
		return m_is_encrypted;	
	}

	const t_mix_index_entry* index() const
	{
		return m_index;
	}
private:
	typedef map<int, int> t_id_index;

	static bool m_ft_support;

    void clean_up();
    int m_c_files;
	t_game m_game;
	bool m_mix_expansion;
	bool m_is_encrypted;
	bool m_has_checksum;
    t_mix_index_entry* m_index;
	t_file_type* m_index_ft;
	t_id_index m_id_index;
};

#endif // !defined(AFX_MIX_FILE_H__6AA2E061_D405_11D3_8684_0000F81AF605__INCLUDED_)
