// xif_value.h: interface for the Cxif_value class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XIF_VALUE_H__99A07CE5_FA5D_11D2_B601_8B199B22657D__INCLUDED_)
#define AFX_XIF_VALUE_H__99A07CE5_FA5D_11D2_B601_8B199B22657D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "vartypes.h"
#include "virtual_binary.h"

using namespace std;

enum t_vt {vt_bin32, vt_binary, vt_int32, vt_string, vt_unknown};

class Cxif_value  
{
public:
	Cxif_value()
	{
		m_type = vt_unknown;
	}

	Cxif_value(t_vt type, int v)
	{
		m_type = type;
		memcpy(m_data.write_start(4), &v, 4);
	}	

	Cxif_value(const Cvirtual_binary v)
	{
		m_type = vt_binary;
		m_data = v;
	}	

	Cxif_value(const string& v)
	{
		m_type = vt_string;
		memcpy(m_data.write_start(v.length() + 1), v.c_str(), v.length() + 1);
	}	

	Cvirtual_binary get_vdata() const
	{
		return m_data;
	}

	const byte* get_data() const
	{
		return m_data.data();
	}

	int get_size() const 
	{
		return m_data.size();
	}

	int get_int() const
	{
		assert(get_size() == 4);
		return *reinterpret_cast<const __int32*>(get_data());
	}

	int get_int(int v) const
	{
		return get_size() ? *reinterpret_cast<const __int32*>(get_data()) : v;
	}

	string get_string() const
	{
		assert(get_size());
		return reinterpret_cast<const char*>(get_data());
	}

	string get_string(const string& v) const
	{
		return get_size() ? reinterpret_cast<const char*>(get_data()) : v;
	}

	t_vt get_type() const
	{
		if (m_type != vt_unknown)
			return m_type;
		const byte* data = get_data();
		int size = get_size();
		if (!data)
			return vt_binary;
		if (!data[size - 1])
		{
			const byte* r = data;
			int c = size - 1;
			while (c--)
			{
				if (*r != 9 && *r < 0x20)
					break;
				r++;
			}
			if (c == -1)
				return vt_string;
		}	
		if (get_size() == 4)
			return vt_int32;
		return vt_binary;
	}

	void load_old(const byte*& data)
	{
		m_data.clear();
		int size = *reinterpret_cast<const __int32*>(data);
		data += 4;
		// m_data = m_size ? new byte[m_size] : NULL;
		memcpy(m_data.write_start(size), data, size);
		data += size;
		m_type = vt_unknown;
		m_type = get_type();
	}

	void load_new(const byte*& data)
	{
		m_data.clear();
		m_type = static_cast<t_vt>(*reinterpret_cast<const __int8*>(data));
		data++;
		switch (m_type)
		{
		case vt_bin32:
			// m_size = 4;
			// m_data = new byte[m_size];
			*reinterpret_cast<__int32*>(m_data.write_start(4)) = *reinterpret_cast<const unsigned __int32*>(data);
			data += 4;
			break;
		case vt_int32:
			// m_size = 4;
			// m_data = new byte[m_size];
			*reinterpret_cast<__int32*>(m_data.write_start(4)) = *reinterpret_cast<const __int32*>(data);
			data += 4;
			break;
		default:
			{
				int size = *reinterpret_cast<const __int32*>(data);
				data += 4;
				// m_data = new byte[m_size];
				memcpy(m_data.write_start(size), data, size);
				data += size;
			}
		}
	}

	void save(byte*& data) const
	{
		*reinterpret_cast<__int8*>(data) = m_type;
		data++;
		switch (m_type)
		{
		case vt_bin32:
		case vt_int32:
			*reinterpret_cast<__int32*>(data) = get_int();
			data += 4;
			break;
		default:
			{
				int size = get_size();
				*reinterpret_cast<__int32*>(data) = size;
				data += 4;
				memcpy(data, get_data(), size);
				data += size;
			}
		}
	}

	void dump(ostream& os, int depth = 0) const;
private:
	Cvirtual_binary m_data;
	// byte* m_data;
	t_vt m_type;
	// int m_size;
};

#endif // !defined(AFX_XIF_VALUE_H__99A07CE5_FA5D_11D2_B601_8B199B22657D__INCLUDED_)
