// xif_value.h: interface for the Cxif_value class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XIF_VALUE_H__99A07CE5_FA5D_11D2_B601_8B199B22657D__INCLUDED_)
#define AFX_XIF_VALUE_H__99A07CE5_FA5D_11D2_B601_8B199B22657D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "vartypes.h"

using namespace std;

enum t_vt {vt_bin32, vt_binary, vt_int32, vt_string, vt_unknown};

class Cxif_value  
{
public:
	Cxif_value()
	{
		m_data = NULL;
		m_size = 0;
		m_type = vt_unknown;
	}

	~Cxif_value()
	{
		delete[] m_data;
	}

	Cxif_value(const Cxif_value& v):
		m_size(v.m_size),
		m_type(v.m_type)
	{
		m_data = new byte[m_size];
		memcpy(m_data, v.m_data, m_size);
	}

	Cxif_value(t_vt type, int v):
		m_size(4),
		m_type(type)
	{
		m_data = new byte[m_size];
		memcpy(m_data, &v, m_size);
	}	

	Cxif_value(const void* v, int size):
		m_size(size),
		m_type(vt_binary)
	{
		m_data = new byte[m_size];
		memcpy(m_data, v, m_size);
	}	

	Cxif_value(const string& v):
		m_size(v.length() + 1),
		m_type(vt_string)
	{
		m_data = new byte[m_size];
		memcpy(m_data, v.c_str(), m_size);
	}	

	Cxif_value& operator=(const Cxif_value& v)
	{
		if (&v != this)
		{
			delete[] m_data;
			m_size = v.m_size;
			m_type = v.m_type;
			m_data = new byte[m_size];
			memcpy(m_data, v.m_data, m_size);
		}
		return *this;
	}
	

	byte* get_data() const
	{
		return m_data;
	}

	int get_size() const 
	{
		return m_size;
	}

	int get_int() const
	{
		assert(m_data && m_size == 4);
		return *reinterpret_cast<__int32*>(m_data);
	}

	string get_string() const
	{
		assert(m_data && m_size);
		return reinterpret_cast<const char*>(m_data);
	}

	t_vt get_type() const
	{
		if (m_type != vt_unknown)
			return m_type;
		if (!m_data)
			return vt_binary;
		if (!m_data[m_size - 1])
		{
			const byte* r = m_data;
			int c = m_size - 1;
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
		delete[] m_data;
		m_size = *reinterpret_cast<const __int32*>(data);
		data += 4;
		m_data = m_size ? new byte[m_size] : NULL;
		memcpy(m_data, data, m_size);
		data += m_size;
		m_type = vt_unknown;
		m_type = get_type();
	}

	void load_new(const byte*& data)
	{
		delete[] m_data;
		m_type = static_cast<t_vt>(*reinterpret_cast<const __int8*>(data));
		data++;
		switch (m_type)
		{
		case vt_bin32:
			m_size = 4;
			m_data = new byte[m_size];
			*reinterpret_cast<__int32*>(m_data) = *reinterpret_cast<const unsigned __int32*>(data);
			data += 4;
			break;
		case vt_int32:
			m_size = 4;
			m_data = new byte[m_size];
			*reinterpret_cast<__int32*>(m_data) = *reinterpret_cast<const __int32*>(data);
			data += 4;
			break;
		default:
			m_size = *reinterpret_cast<const __int32*>(data);
			data += 4;
			m_data = new byte[m_size];
			memcpy(m_data, data, m_size);
			data += m_size;
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
			*reinterpret_cast<__int32*>(data) = m_size;
			data += 4;
			memcpy(data, m_data, m_size);
			data += m_size;
		}
	}

	void dump(ostream& os, int depth = 0) const;
private:
	byte* m_data;
	t_vt m_type;
	int m_size;
};

#endif // !defined(AFX_XIF_VALUE_H__99A07CE5_FA5D_11D2_B601_8B199B22657D__INCLUDED_)
