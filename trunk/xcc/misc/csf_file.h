// csf_file.h: interface for the Ccsf_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSF_FILE_H__327575A6_BFED_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_CSF_FILE_H__327575A6_BFED_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include "cc_file_sh.h"
#include "cc_structures.h"

class Ccsf_file: public Ccc_file_sh<t_csf_header>
{
public:
	struct t_map_entry
	{
		wstring value;
		string extra_value;
	};

	typedef map<string, t_map_entry> t_map;

    int post_open();
	void erase_value(const string& name);
	string get_converted_value(const string& name) const;
	void set_value(const string& name, const wstring& value, const string& extra_value);
	static string convert2string(const wstring& s);
	static wstring convert2wstring(const string& s);
	int get_write_size() const;
	void write(byte* d) const;

	bool is_valid() const
	{
		const t_csf_header& header = *get_header();
		int size = get_size();
		return !(sizeof(t_csf_header) > size || 
			header.id != csf_file_id);
	}

	int get_c_strings() const
	{
		return m_map.size();
	}

	const t_map& get_map() const
	{
		return m_map;
	}

	wstring get_value(const string& name) const
	{
		return m_map.find(name)->second.value;
	}

	string get_extra_value(const string& name) const
	{
		return m_map.find(name)->second.extra_value;
	}

	bool has_name(const string& name) const
	{
		return m_map.find(name) != m_map.end();
	}
private:
	t_map m_map;
};

#endif // !defined(AFX_CSF_FILE_H__327575A6_BFED_11D4_B606_0000B4936994__INCLUDED_)
