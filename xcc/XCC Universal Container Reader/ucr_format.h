// ucr_format.h: interface for the Cucr_format class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCR_FORMAT_H__73ACC3D9_0D77_43E0_A034_26838E542A3B__INCLUDED_)
#define AFX_UCR_FORMAT_H__73ACC3D9_0D77_43E0_A034_26838E542A3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stream_reader.h"
#include "xif_key.h"

class Cucr_container;

template <class T>
Cucr_container* new_container()
{
	return new T;
}

class Cucr_format  
{
public:
	enum t_ct
	{
		ct_once,
		ct_object_count,
	};

	enum t_vi
	{
		vi_block_offset,
		vi_object_count,
		vi_object_data,
		vi_object_id,
		vi_object_name,
		vi_object_offset,
		vi_object_size,
		vi_literal,
		vi_var_size,
		vi_custom,
	};

	enum t_vt
	{
		vt_float,
		vt_int,
		vt_string,
		vt_wstring,
	};

	struct t_var
	{
		bool big_endian;
		int block;
		int var;
		t_vi id;
		string name;
		int offset;
		int size;
		t_vt type;
		int int_value;
		string string_value;

		float read_float(Cstream_reader& sr) const;
		int read_int(Cstream_reader& sr) const;
		string read_string(Cstream_reader& sr) const;
		string read_string(Cstream_reader& sr, int length) const;
		wstring read_wstring(Cstream_reader& sr) const;
		wstring read_wstring(Cstream_reader& sr, int length) const;

		Cxif_key export() const;
		t_var(const Cxif_key& key);
		
		t_var()
		{
			big_endian = false;
		}

		t_var(t_vi _id, int _offset, int _size, bool _big_endian = false, int _block = 0, int _var = 0)
		{
			big_endian = _big_endian;
			block = _block;
			var = _var;
			id = _id;
			offset = _offset;
			size = _size;
			switch (_id)
			{
			case vi_object_name:
				type = vt_string;
				break;
			default:
				type = vt_int;
			}			
		}

		t_var(const string& _name, int _offset, int _size, bool _big_endian = false, t_vt _type = vt_int)
		{
			big_endian = _big_endian;
			id = vi_custom;
			name = _name;
			offset = _offset;
			size = _size;
			type = _type;
		}
	};

	static t_var t_var_literal(int _offset, int _size, bool _big_endian, int _value)
	{
		t_var var;
		var.big_endian = _big_endian;
		var.id = vi_literal;
		var.offset = _offset;
		var.size = _size;
		var.type = vt_int;
		var.int_value = _value;
		return var;
	}

	static t_var t_var_literal(int _offset, int _size, bool _big_endian, string _value)
	{
		t_var var;
		var.big_endian = _big_endian;
		var.id = vi_literal;
		var.offset = _offset;
		var.size = _size;
		var.type = vt_string;
		var.string_value = _value;
		return var;
	}

	typedef vector<t_var> t_vars;

	struct t_block
	{
		bool add_object;
		bool update_object;
		t_ct count;
		int offset;
		int size;
		t_vars vars;

		Cxif_key export() const;
		t_block(const Cxif_key& key);

		t_block()
		{
			add_object = false;
			update_object = false;
			count = ct_once;
			offset = 0;
			size = 0;
		}
	};

	typedef vector<t_block> t_blocks;
	typedef set<string> t_extensions;
	typedef set<string> t_registry_keys;

	typedef Cucr_container* (*t_new_container_f)();
	
	static const char* get_vi_name(int i);
	static const char* get_vt_name(int i);
	static Cucr_format get_big_format();
	static Cucr_format get_dune2_pak_format();
	static Cucr_format get_ra2_csf_format();
	static Cucr_format get_enoid_res_format();
	static Cucr_format get_rg_mix_format();
	static Cucr_format get_td_mix_format();
	static Cucr_format get_conquest_wad_format();
	static Cucr_format get_lost_eden_dat_format();
	string extensions_string(const string& separator) const;
	string registry_keys_string(const string& separator) const;
	Cxif_key export() const;
	Cucr_format();
	Cucr_format(const string& name, const string& extensions, const string& registry_keys, t_new_container_f new_container_f = NULL);
	Cucr_format(const Cxif_key& key);
	// virtual ~Cucr_format();

	const t_blocks& blocks() const
	{
		return m_blocks;
	}

	const string& name() const
	{
		return m_name;
	}

	const t_extensions& extensions() const
	{
		return m_extensions;
	}

	const t_registry_keys& registry_keys() const
	{
		return m_registry_keys;
	}

	t_new_container_f new_container_f() const
	{
		return m_new_container_f;
	}
private:
	Cxif_key export_blocks() const;
	Cxif_key export_extensions() const;
	Cxif_key export_registry_keys() const;
	void import_blocks(const Cxif_key& key);
	void import_extensions(const Cxif_key& key);
	void import_registry_keys(const Cxif_key& key);

	t_blocks m_blocks;
	t_extensions m_extensions;
	t_registry_keys m_registry_keys;
	string m_name;

	t_new_container_f m_new_container_f;
};

#endif // !defined(AFX_UCR_FORMAT_H__73ACC3D9_0D77_43E0_A034_26838E542A3B__INCLUDED_)
