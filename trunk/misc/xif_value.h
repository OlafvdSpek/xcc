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

enum t_vt {vt_bin32, vt_binary, vt_int32, vt_string, vt_external_binary, vt_float, vt_unknown};

class Cxif_value  
{
public:
	Cxif_value()
	{
		m_type = vt_unknown;
	}

	Cxif_value(float v)
	{
		m_type = vt_float;
		memcpy(m_data.write_start(4), &v, 4);
	}

	Cxif_value(t_vt type, int v)
	{
		m_type = type;
		memcpy(m_data.write_start(4), &v, 4);
	}

	Cxif_value(const Cvirtual_binary v, bool fast = false)
	{
		m_type = vt_binary;
		m_data = v;
		m_fast = fast;
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

	float get_float() const
	{
		assert(get_size() == 4);
		return *reinterpret_cast<const float*>(get_data());
	}

	float get_float(float v) const
	{
		return get_size() ? get_float() : v;
	}

	int get_int() const
	{
		assert(get_size() == 4);
		return *reinterpret_cast<const __int32*>(get_data());
	}

	int get_int(int v) const
	{
		return get_size() ? get_int() : v;
	}

	string get_string() const
	{
		assert(get_size());
		return reinterpret_cast<const char*>(get_data());
	}

	string get_string(const string& v) const
	{
		return get_size() ? get_string() : v;
	}

	void dump(ostream& os, int depth = 0) const;
	t_vt get_type() const;
	void load_old(const byte*& data);
	void load_new(const byte*& data);
	void load_external(const byte*& data);
	void save(byte*& data) const;
	bool external_data() const;
	void external_save(byte*& data) const;
private:
	Cvirtual_binary m_data;
	bool m_fast;
	t_vt m_type;
	// int m_value;
};

#endif // !defined(AFX_XIF_VALUE_H__99A07CE5_FA5D_11D2_B601_8B199B22657D__INCLUDED_)
