// virtual_binary.h: interface for the Cvirtual_binary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUAL_BINARY_H__B59C9DC0_DB25_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_VIRTUAL_BINARY_H__B59C9DC0_DB25_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "smart_ref.h"
#include "vartypes.h"

using namespace std;

class Cvirtual_binary_source
{
public:
	Cvirtual_binary_source(const void* d, int cb_d, Csmart_ref_base* source = NULL);
	void detach();
	Cvirtual_binary_source* pre_edit();

	Cvirtual_binary_source* attach()
	{
		mc_references++;
		return this;
	}

	const byte* data() const
	{
		return m_data;
	}

	const byte* data_end() const
	{
		return data() + size();
	}

	byte* data_edit()
	{
		assert(mc_references == 1 && !m_source);
		return m_data;
	}

	int size() const
	{
		return m_size;
	}

	void size(int v)
	{
		assert(mc_references == 1 && !m_source && v <= m_size);
		m_size = v;
	}
private:
	byte* m_data;
	int m_size;
	int mc_references;
	Csmart_ref_base* m_source;
};

class Cvirtual_binary  
{
public:
	Cvirtual_binary sub_bin(int offset, int size) const;
	int export(const string& fname) const;
	int import(const string& fname, bool use_mm = true);
	void clear();
	void memset(int v);
	int read(void* d) const;
	byte* write_start(int cb_d);
	void write(const void* d, int cb_d);
	const Cvirtual_binary& operator=(const Cvirtual_binary& v);
	Cvirtual_binary();
	Cvirtual_binary(const Cvirtual_binary& v);
	Cvirtual_binary(const void* d, int cb_d);
	Cvirtual_binary(const void* d, int cb_d, Csmart_ref_base* source);
	explicit Cvirtual_binary(const string& fname, bool use_mm = true);
	~Cvirtual_binary();

	const byte* data() const
	{
		return m_source ? m_source->data() : NULL;
	}

	const byte* data_end() const
	{
		return m_source ? m_source->data_end() : NULL;
	}

	byte* data_edit()
	{
		assert(m_source);
		m_source = m_source->pre_edit();
		return m_source->data_edit();
	}

	int size() const
	{
		return m_source ? m_source->size() : 0;
	}

	void size(int v)
	{
		assert(m_source);
		m_source = m_source->pre_edit();
		m_source->size(v);
	}

	operator const byte*() const
	{
		return data();
	}
private:
	Cvirtual_binary_source* m_source;
};

#endif // !defined(AFX_VIRTUAL_BINARY_H__B59C9DC0_DB25_11D4_A95D_0050042229FC__INCLUDED_)
