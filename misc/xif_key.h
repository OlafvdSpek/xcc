// xif_key.h: interface for the Cxif_key class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XIF_KEY_H__99A07CE4_FA5D_11D2_B601_8B199B22657D__INCLUDED_)
#define AFX_XIF_KEY_H__99A07CE4_FA5D_11D2_B601_8B199B22657D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <map>
#include <string>
#include "virtual_binary.h"
#include "xif_value.h"
#include "zlib.h"

using namespace std;

const static __int32 file_id = *reinterpret_cast<const __int32*>("XIF\x1a");
const static int file_version_old = 0;
const static int file_version_new = 1;

struct t_xif_header
{
	__int32 id;
	__int32 version;
	__int32 size_uncompressed;
};

class Cxif_key;

typedef map<int, Cxif_key> t_xif_key_map;
typedef map<int, Cxif_value> t_xif_value_map;

class Cxif_key
{
public:
	Cxif_key():
		m_keys(*new t_xif_key_map),
		m_values(*new t_xif_value_map)
	{
	}

	~Cxif_key()
	{
		delete &m_values;
		delete &m_keys;
	}

	Cxif_key(const Cxif_key& v):
		m_keys(*new t_xif_key_map),
		m_values(*new t_xif_value_map)
	{
		m_keys = v.m_keys;
		m_values = v.m_values;
	}

	const Cxif_key& operator=(const Cxif_key& v)
	{
		m_keys = v.m_keys;
		m_values = v.m_values;
		return *this;
	}

	Cxif_key& set_key(int id)
	{
		m_keys[id] = Cxif_key();
		return m_keys[id];
	}

	const Cxif_key& open_key_read(int id) const
	{
		return m_keys.find(id)->second;
	}

	Cxif_key& open_key_edit(int id)
	{
		return m_keys[id];
	}

	Cxif_key& open_key_write(int id)
	{
		m_keys[id] = Cxif_key();
		return m_keys[id];
	}

	const Cxif_value& open_value_read(int id) const
	{
		return m_values.find(id)->second;
	}

	Cxif_value& open_value_edit(int id)
	{
		return m_values[id];
	}

	Cxif_value& open_value_write(int id)
	{
		m_values[id] = Cxif_value();
		return m_values[id];
	}
	
	Cxif_value& set_value(int id)
	{
		m_values[id] = Cxif_value();
		return m_values[id];
	}
	
	void set_value_bin(int id, int v)
	{
		m_values[id] = Cxif_value(vt_bin32, v);
	}

	void set_value_binary(int id, const Cvirtual_binary v)
	{
		m_values[id] = Cxif_value(v);
	}

	/*
	void set_value_binary(int id, const void* v, int size)
	{
		m_values[id] = Cxif_value(v, size);
	}
	*/

	void set_value_int(int id, int v)
	{
		m_values[id] = Cxif_value(vt_int32, v);
	}

	void set_value_string(int id, const string& v)
	{
		m_values[id] = Cxif_value(v);
	}

	void set_value(int id, __int64 v)
	{
		set_value_binary(id, Cvirtual_binary(&v, 8));
	}

	const Cxif_key& get_key(int id) const
	{
		t_xif_key_map::iterator i = m_keys.find(id);
		/*
		if (i == m_keys.end())
			throw Cxif_key_not_found();
		*/
		return i->second;
	}

	const Cxif_value& get_value(int id) const
	{
		t_xif_value_map::iterator i = m_values.find(id);
		/*
		if (i == m_values.end())
			throw Cxif_value_not_found();
		*/
		return i->second;
	}

	int get_value_int(int id) const
	{
		return get_value(id).get_int();
	}

	__int64 get_value_int64(int id) const
	{
		return *reinterpret_cast<const __int64*>(get_value(id).get_data());
	}

	string get_value_string(int id) const
	{
		return get_value(id).get_string();
	}

	bool exists_key(int id) const
	{
		return m_keys.find(id) != m_keys.end();
	}

	bool exists_value(int id) const
	{
		return m_values.find(id) != m_values.end();
	}

	int c_keys() const
	{
		return m_keys.size();
	}

	int c_values() const
	{
		return m_values.size();
	}

	int load_key(const byte* data, int size)
	{
		const byte* read_p = data;
		const t_xif_header& header = *reinterpret_cast<const t_xif_header*>(read_p);
		if (header.id != file_id ||
			header.version != file_version_old && header.version != file_version_new)
			return 1;
		int error = 0;
		if (header.version == file_version_old)
		{
			read_p += sizeof(t_xif_header) - 4;
			load_old(read_p);
			error = size != read_p - data;
		}
		else
		{
			unsigned long cb_d = header.size_uncompressed;
			byte* d = new byte[header.size_uncompressed];
			error = uncompress(d, &cb_d, data + sizeof(t_xif_header), size - sizeof(t_xif_header)) != Z_OK;
			if (!error)
			{
				read_p = d;
				load_new(read_p);
				error = header.size_uncompressed != read_p - d;
			}
			delete[] d;
		}
		return error;
	}

	int load_key(const Cvirtual_binary data)
	{
		return load_key(data.data(), data.size());
	}

	/*
	int save_start()
	{
		int cb_s = get_size();
		byte* s = new byte[cb_s];
		byte* w = s;
		save(w);
		unsigned long cb_d = cb_s + (cb_s + 999) / 1000 + 12;
		m_data_c = new byte[sizeof(t_xif_header) + cb_d];
		t_xif_header& header = *reinterpret_cast<t_xif_header*>(m_data_c);
		header.id = file_id;
		header.version = file_version_new;		
		header.size_uncompressed = cb_s;
		int error = compress(m_data_c + sizeof(t_xif_header), &cb_d, s, cb_s) != Z_OK;
		mcb_data_c = sizeof(t_xif_header) + cb_d;
		delete[] s;
		if (error)
			delete[] m_data_c;
		return error;
	}

	int key_size() const
	{
		return mcb_data_c;
	}

	const byte* key_data() const
	{
		return m_data_c;
	}

	void save_finish() const
	{
		delete[] m_data_c;
	}
	*/

	void delete_key(int id)
	{
		m_keys.erase(id);
	}

	void delete_value(int id)
	{
		m_values.erase(id);
	}

	void clear()
	{
		m_keys.clear();
		m_values.clear();
	}

	void dump(ostream& os, bool show_ratio, int depth = 0, Cvirtual_binary* t = NULL) const;
	void dump_ratio(ostream& os, Cvirtual_binary* t) const;
	// int save(string fname);
	Cvirtual_binary vdata() const;

	t_xif_key_map& m_keys;
	t_xif_value_map& m_values;
private:
	void load_old(const byte*& data)
	{
		{
			// keys
			int count = *reinterpret_cast<const int*>(data);
			data += 4;
			while (count--)
			{
				Cxif_key& i = set_key(*reinterpret_cast<const int*>(data));
				data += 4;
				i.load_old(data);
			}
		}

		{
			// values
			int count = *reinterpret_cast<const int*>(data);
			data += 4;
			while (count--)
			{
				Cxif_value& i = set_value(*reinterpret_cast<const int*>(data));
				data += 4;
				i.load_old(data);
			}
		}
	}

	void load_new(const byte*& data)
	{
		{
			// keys
			int count = *reinterpret_cast<const int*>(data);
			data += 4;
			int id = 0;
			while (count--)
			{
				id += *reinterpret_cast<const int*>(data);
				Cxif_key& i = open_key_write(id);
				data += 4;
				i.load_new(data);
			}
		}

		{
			// values
			int count = *reinterpret_cast<const int*>(data);
			data += 4;
			int id = 0;
			while (count--)
			{
				id += *reinterpret_cast<const int*>(data);
				Cxif_value& i = open_value_write(id);
				data += 4;
				i.load_new(data);
			}
		}
	}

	int get_size() const
	{
		int size = 8;
		{
			// keys
			for (t_xif_key_map::const_iterator i = m_keys.begin(); i != m_keys.end(); i++)
				size += 4 + i->second.get_size();
		}

		{
			// values
			for (t_xif_value_map::const_iterator i = m_values.begin(); i != m_values.end(); i++)
			{
				size += 9;
				if (i->second.get_type() != vt_bin32 && i->second.get_type() != vt_int32)
					size += i->second.get_size();
			}
		}
		return size;
	}

	void save_key(byte* data) const
	{
		byte* write_p = data;
		t_xif_header& header = *reinterpret_cast<t_xif_header*>(write_p);
		header.id = file_id;
		header.version = file_version_new;		
		header.size_uncompressed = sizeof(t_xif_header) + get_size();
		write_p += sizeof(t_xif_header);
		save(write_p);
	}

	void save(byte*& data) const
	{
		{
			// keys
			*reinterpret_cast<int*>(data) = m_keys.size();
			data += 4;
			int id = 0;
			for (t_xif_key_map::const_iterator i = m_keys.begin(); i != m_keys.end(); i++)
			{
				*reinterpret_cast<int*>(data) = i->first - id;
				id = i->first;
				data += 4;
				i->second.save(data);
			}
		}

		{
			// values
			*reinterpret_cast<int*>(data) = m_values.size();
			data += 4;
			int id = 0;
			for (t_xif_value_map::const_iterator i = m_values.begin(); i != m_values.end(); i++)
			{
				*reinterpret_cast<int*>(data) = i->first - id;
				id = i->first;
				data += 4;
				i->second.save(data);
			}
		}
	}

	byte* m_data_c;
	int mcb_data_c;
};

#endif // !defined(AFX_XIF_KEY_H__99A07CE4_FA5D_11D2_B601_8B199B22657D__INCLUDED_)
