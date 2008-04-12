#include "stdafx.h"
#include "ucr_format.h"

#include "xif_key.h"

float Cucr_format::t_var::read_float(Cstream_reader& sr) const
{
	assert(type == vt_float);
	float v = 0;
	return v;
}

int Cucr_format::t_var::read_int(Cstream_reader& sr) const
{
	assert(type == vt_int);
	int v = 0;
	switch (size)
	{
	case 8:
	case 16:
	case 24:
	case 32:
		if (big_endian)
		{
			for (int i = 0; i < size >> 3; i++)
				v = v << 8 | *sr.read(1);
		}
		else
		{
			for (int i = 0; i < size >> 3; i++)
				v |= *sr.read(1) << (i << 3);
		}
		break;
	default:
		assert(false);
	}
	return v;
}

string Cucr_format::t_var::read_string(Cstream_reader& sr) const
{
	assert(type == vt_string);
	if (!size)
		return sr.read_string();
	assert(!(size & 3));
	if (big_endian)
	{
		string v;
		v.resize(size >> 3);
		int i = size >> 3;
		while (i--)
			v[i] = *sr.read(1);
		return v;
	}
	return string(reinterpret_cast<const char*>(sr.read(size >> 3)), size >> 3);
}

string Cucr_format::t_var::read_string(Cstream_reader& sr, int length) const
{
	assert(type == vt_string);
	return length ? string(reinterpret_cast<const char*>(sr.read(length)), length) : sr.read_string();
}

wstring Cucr_format::t_var::read_wstring(Cstream_reader& sr) const
{
	assert(type == vt_wstring);
	assert(size);
	/*
	if (!size)
		return sr.read_wstring();
	*/
	assert(!(size & 3));
	if (big_endian)
	{
		wstring v;
		v.resize(size >> 3);
		int i = size >> 3;
		while (i--)
			v[i] = *sr.read(1);
		return v;
	}
	return wstring(reinterpret_cast<const wchar_t*>(sr.read(size >> 3)), size >> 3);
}

wstring Cucr_format::t_var::read_wstring(Cstream_reader& sr, int length) const
{
	assert(type == vt_wstring);
	return wstring(reinterpret_cast<const wchar_t*>(sr.read(length << 1)), length);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cucr_format::Cucr_format()
{
}

Cucr_format::Cucr_format(const string& name, const string& extensions, const string& registry_keys, t_new_container_f new_container_f)
{
	m_name = name;
	{
		int a = 0;
		int b;
		while ((b = extensions.find(';', a)) != string::npos)
		{
			m_extensions.insert(extensions.substr(a, b - a));
			a = b + 1;
		}
		if (a != extensions.length())
			m_extensions.insert(extensions.substr(a));
	}
	{
		int a = 0;
		int b;
		while ((b = registry_keys.find(';', a)) != string::npos)
		{
			m_registry_keys.insert(registry_keys.substr(a, b - a));
			a = b + 1;
		}
		if (a != registry_keys.length())
			m_registry_keys.insert(registry_keys.substr(a));
	}
	m_new_container_f = new_container_f;
}

string Cucr_format::extensions_string(const string& separator) const
{
	string v;
	for (t_extensions::const_iterator i = extensions().begin(); i != extensions().end(); i++)
		v += *i + separator;
	return v;
}

string Cucr_format::registry_keys_string(const string& separator) const
{
	string v;
	for (t_registry_keys::const_iterator i = registry_keys().begin(); i != registry_keys().end(); i++)
		v += *i + separator;
	return v;
}

const char* Cucr_format::get_vi_name(int i)
{
	const char* names[] =
	{
		"block_offset",
		"object_count",
		"object_data",
		"object_id",
		"object_name",
		"object_offset",
		"object_size",
		"literal",
		"var_size",
		"custom",
	};
	return names[i];
}

const char* Cucr_format::get_vt_name(int i)
{
	const char* names[] =
	{
		"float",
		"int",
		"string",
		"wstring",
	};
	return names[i];
}

enum
{
	ki_blocks,
	ki_extensions,
	ki_registry_keys,
	ki_vars,

	vi_add_object,
	vi_update_object,
	vi_count,
	vi_offset,
	vi_size,

	vi_big_endian,
	vi_block,
	vi_var,
	vi_id,
	vi_name,
	vi_data,
	vi_type,
	vi_int_value,
	vi_string_value,
};

Cxif_key Cucr_format::t_var::export() const
{
	Cxif_key key;
	key.set_value_int(vi_big_endian, big_endian);
	key.set_value_int(vi_block, block);
	key.set_value_int(vi_var, var);
	key.set_value_int(vi_id, id);
	key.set_value_string(vi_name, name);
	key.set_value_int(vi_offset, offset);
	key.set_value_int(vi_size, size);
	key.set_value_int(vi_type, type);
	key.set_value_int(vi_int_value, int_value);
	key.set_value_string(vi_string_value, string_value);
	return key;
}

Cucr_format::t_var::t_var(const Cxif_key& key)
{
	big_endian = key.get_value_int(vi_big_endian);
	block = key.get_value_int(vi_block);
	var = key.get_value_int(vi_var);
	id = static_cast<t_vi>(key.get_value_int(vi_id));
	name = key.get_value_string(vi_name);
	offset = key.get_value_int(vi_offset);
	size = key.get_value_int(vi_size);
	type = static_cast<t_vt>(key.get_value_int(vi_type));
	int_value = key.get_value_int(vi_int_value);
	string_value = key.get_value_string(vi_string_value);
}

Cxif_key Cucr_format::t_block::export() const
{
	Cxif_key key;
	for (t_vars::const_iterator i = vars.begin(); i != vars.end(); i++)
		key.open_key_write() = i->export();
	key.set_value_int(vi_add_object, add_object);
	key.set_value_int(vi_update_object, update_object);
	key.set_value_int(vi_count, count);
	key.set_value_int(vi_offset, offset);
	key.set_value_int(vi_size, size);
	return key;
}

Cucr_format::t_block::t_block(const Cxif_key& key)
{
	for (t_xif_key_map::const_iterator i = key.m_keys.begin(); i != key.m_keys.end(); i++)
		vars.push_back(t_var(i->second));
	add_object = key.get_value_int(vi_add_object);
	update_object = key.get_value_int(vi_update_object);
	count = static_cast<t_ct>(key.get_value_int(vi_count));
	offset = key.get_value_int(vi_offset);
	size = key.get_value_int(vi_size);
}

Cxif_key Cucr_format::export_blocks() const
{
	Cxif_key key;
	for (t_blocks::const_iterator i = blocks().begin(); i != blocks().end(); i++)
		key.open_key_write() = i->export();
	return key;
}

Cxif_key Cucr_format::export_extensions() const
{
	Cxif_key key;
	int j = 0;
	for (t_extensions::const_iterator i = extensions().begin(); i != extensions().end(); i++)
		key.set_value_string(j++, *i);
	return key;
}

Cxif_key Cucr_format::export_registry_keys() const
{
	Cxif_key key;
	int j = 0;
	for (t_registry_keys::const_iterator i = registry_keys().begin(); i != registry_keys().end(); i++)
		key.set_value_string(j++, *i);
	return key;
}

Cxif_key Cucr_format::export() const
{
	Cxif_key key;
	key.open_key_write(ki_blocks) = export_blocks();
	key.open_key_write(ki_extensions) = export_extensions();
	key.open_key_write(ki_registry_keys) = export_registry_keys();
	key.set_value_string(vi_name, name());
	return key;
}

void Cucr_format::import_blocks(const Cxif_key& key)
{
	for (t_xif_key_map::const_iterator i = key.m_keys.begin(); i != key.m_keys.end(); i++)
		m_blocks.push_back(t_block(i->second));
}

void Cucr_format::import_extensions(const Cxif_key& key)
{
	for (t_xif_value_map::const_iterator i = key.m_values.begin(); i != key.m_values.end(); i++)
		m_extensions.insert(i->second.get_string());
}

void Cucr_format::import_registry_keys(const Cxif_key& key)
{
	for (t_xif_value_map::const_iterator i = key.m_values.begin(); i != key.m_values.end(); i++)
		m_registry_keys.insert(i->second.get_string());
}

Cucr_format::Cucr_format(const Cxif_key& key)
{
	import_blocks(key.open_key_read(ki_blocks));
	import_extensions(key.open_key_read(ki_extensions));
	import_registry_keys(key.open_key_read(ki_registry_keys));
	m_name = key.get_value_string(vi_name);
}

Cucr_format Cucr_format::get_big_format()
{
	Cucr_format format("Westwood Studios - Command & Conquer: Generals - BIG", "big", "hkey_local_machine\\software\\electronic arts\\ea games\\generals\\installpath");
	t_block header;
	{
		header.vars.push_back(t_var_literal(0, 32, false, "BIGF"));
		header.vars.push_back(t_var("File Size", 4, 32, false));
		header.vars.push_back(t_var(vi_object_count, 8, 32, true));
		header.vars.push_back(t_var("Header Size", 12, 32, true));
	}
	t_block index_entry;
	{
		index_entry.add_object = true;
		index_entry.count = ct_object_count;
		index_entry.vars.push_back(t_var(vi_object_offset, 0, 32, true));
		index_entry.vars.push_back(t_var(vi_object_size, 4, 32, true));
		index_entry.vars.push_back(t_var(vi_object_name, 8, 0));
	}
	format.m_blocks.push_back(header);
	format.m_blocks.push_back(index_entry);
	return format;
}

Cucr_format Cucr_format::get_td_mix_format()
{
	Cucr_format format("Westwood Studios - Command & Conquer: Tiberian Dawn - MIX", "mix;mmx", "");
	t_block header;
	{
		header.vars.push_back(t_var(vi_object_count, 0, 16, false));
		header.vars.push_back(t_var("File Size", 0, 32, false));
	}
	t_block index_entry;
	{
		index_entry.add_object = true;
		index_entry.count = ct_object_count;
		index_entry.vars.push_back(t_var(vi_object_id, 0, 32, false));
		index_entry.vars.push_back(t_var(vi_object_offset, 0, 32, false, 2));
		index_entry.vars.push_back(t_var(vi_object_size, 0, 32, false));
	}
	t_block body;
	{
	}
	format.m_blocks.push_back(header);
	format.m_blocks.push_back(index_entry);
	format.m_blocks.push_back(body);
	return format;
}

Cucr_format Cucr_format::get_rg_mix_format()
{
	Cucr_format format("Westwood Studios - Command & Conquer: Renegade - MIX", "dat;dbs;mix", "hkey_local_machine\\software\\westwood\\renegade\\installpath");
	t_block header;
	{
		header.vars.push_back(t_var_literal(0, 32, false, "MIX1"));
		header.vars.push_back(t_var(vi_block_offset, 0, 32, false, 1));
		header.vars.push_back(t_var(vi_block_offset, 0, 32, false, 3));
		header.vars.push_back(t_var_literal(0, 32, false, 0));
	}
	t_block index_header;
	{
		index_header.vars.push_back(t_var(vi_object_count, 0, 32, false));
	}
	t_block index_entry;
	{
		index_entry.add_object = true;
		index_entry.count = ct_object_count;
		index_entry.vars.push_back(t_var(vi_object_id, 0, 32, false));
		index_entry.vars.push_back(t_var(vi_object_offset, 0, 32, false));
		index_entry.vars.push_back(t_var(vi_object_size, 0, 32, false));
	}
	t_block tailer_header;
	{
		tailer_header.vars.push_back(t_var(vi_object_count, 0, 32, false));
	}
	t_block tailer_entry;
	{
		tailer_entry.update_object = true;
		tailer_entry.count = ct_object_count;
		tailer_entry.vars.push_back(t_var("Name Length", 0, 8, false));
		tailer_entry.vars.push_back(t_var(vi_object_name, 0, 0));
	}
	format.m_blocks.push_back(header);
	format.m_blocks.push_back(index_header);
	format.m_blocks.push_back(index_entry);
	format.m_blocks.push_back(tailer_header);
	format.m_blocks.push_back(tailer_entry);
	return format;
}

Cucr_format Cucr_format::get_ra2_csf_format()
{
	Cucr_format format("Westwood Studios - Command & Conquer: Red Alert 2 - CSF", "csf", "");
	t_block header;
	{
		header.vars.push_back(t_var_literal(0, 32, true, "CSF "));
		header.vars.push_back(t_var("Flags", 0, 32, false));
		header.vars.push_back(t_var(vi_object_count, 0, 32, false));
		header.vars.push_back(t_var("Count 2", 0, 32, false));
		header.vars.push_back(t_var_literal(0, 32, false, 0));
		header.vars.push_back(t_var("Flags", 0, 32, false));
	}
	t_block object_entry;
	{
		object_entry.add_object = true;
		object_entry.count = ct_object_count;
		object_entry.vars.push_back(t_var_literal(0, 32, true, "LBL "));
		object_entry.vars.push_back(t_var("Flags", 0, 32, false));
		object_entry.vars.push_back(t_var(vi_var_size, 0, 32, false, 0, 3));
		object_entry.vars.push_back(t_var(vi_object_name, 0, 0, false, 0, vt_string));
		object_entry.vars.push_back(t_var_literal(0, 32, true, "STR "));
		object_entry.vars.push_back(t_var(vi_var_size, 0, 32, false, 0, 6));
		object_entry.vars.push_back(t_var("Value", 0, 0, false, vt_wstring));
		// header.vars.push_back(t_var("Extra Value", 0, 0, false, 0, vt_string));
	}
	format.m_blocks.push_back(header);
	format.m_blocks.push_back(object_entry);
	return format;
}

Cucr_format Cucr_format::get_conquest_wad_format()
{
	Cucr_format format("Conquest - WAD", "wad", "");
	t_block header;
	{
		header.vars.push_back(t_var(vi_object_count, 4, 8, false));
	}
	t_block index_entry;
	{
		index_entry.add_object = true;
		index_entry.count = ct_object_count;
		index_entry.vars.push_back(t_var(vi_object_offset, 0, 32, false));
		index_entry.vars.push_back(t_var(vi_object_size, 0, 32, false));
		index_entry.vars.push_back(t_var(vi_object_name, 0, 0));
	}
	format.m_blocks.push_back(header);
	format.m_blocks.push_back(index_entry);
	return format;
}

Cucr_format Cucr_format::get_enoid_res_format()
{
	Cucr_format format("Enoid - RES", "res", "");
	t_block header;
	{
		header.vars.push_back(t_var(vi_object_count, 0, 16, false));
	}
	t_block index_entry;
	{
		index_entry.add_object = true;
		index_entry.count = ct_object_count;
		index_entry.size = 22;
		index_entry.vars.push_back(t_var(vi_object_name, 1, 8 * 12));
		index_entry.vars.push_back(t_var(vi_object_offset, 0, 32, false));
		index_entry.vars.push_back(t_var(vi_object_size, 0, 32, false));
	}
	format.m_blocks.push_back(header);
	format.m_blocks.push_back(index_entry);
	return format;
}

Cucr_format Cucr_format::get_lost_eden_dat_format()
{
	Cucr_format format("Lost Eden - DAT", "dat", "");
	t_block header;
	{
		header.vars.push_back(t_var(vi_object_count, 0, 16, false));
	}
	t_block index_entry;
	{
		index_entry.add_object = true;
		index_entry.count = ct_object_count;
		index_entry.size = 25;
		index_entry.vars.push_back(t_var(vi_object_name, 0, 8 * 16));
		index_entry.vars.push_back(t_var(vi_object_size, 0, 32, false));
		index_entry.vars.push_back(t_var(vi_object_offset, 0, 32, false));
	}
	format.m_blocks.push_back(header);
	format.m_blocks.push_back(index_entry);
	return format;
}
