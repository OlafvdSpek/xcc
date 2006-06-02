#if !defined(AFX_VIRTUAL_BINARY_H__B59C9DC0_DB25_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_VIRTUAL_BINARY_H__B59C9DC0_DB25_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cassert>
#include <string>
#include "const_memory_range.h"
#include "smart_ref.h"
#include "vartypes.h"

using namespace std;

class Cvirtual_binary_source
{
public:
	Cvirtual_binary_source(const void* d, size_t cb_d, Csmart_ref_base* source = NULL);
	Cvirtual_binary_source* attach();
	void detach();
	Cvirtual_binary_source* pre_edit();

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

	size_t size() const
	{
		return m_size;
	}

	void size(size_t v)
	{
		assert(mc_references == 1 && !m_source && v <= m_size);
		m_size = v;
	}
private:
	byte* m_data;
	size_t m_size;
	int mc_references;
	Csmart_ref_base* m_source;
};

class Cvirtual_binary  
{
public:
	Cvirtual_binary sub_bin(size_t offset, size_t size) const;
	int save(const string& fname) const;
	int load(const string& fname, bool use_mm = true);
	void clear();
	void memset(int v);
	size_t read(void* d) const;
	byte* write_start(size_t cb_d);
	void write(const void* d, size_t cb_d);
	const Cvirtual_binary& operator=(const Cvirtual_binary& v);
	Cvirtual_binary();
	Cvirtual_binary(const Cvirtual_binary& v);
	Cvirtual_binary(const void* d, size_t cb_d);
	Cvirtual_binary(const void* d, size_t cb_d, Csmart_ref_base* source);
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

	byte* mutable_end()
	{
		return data_edit() + size();
	}

	size_t size() const
	{
		return m_source ? m_source->size() : 0;
	}

	void size(size_t v)
	{
		assert(m_source);
		m_source = m_source->pre_edit();
		m_source->size(v);
	}

	operator const byte*() const
	{
		return data();
	}

	operator const_memory_range() const
	{
		return const_memory_range(data(), size());
	}

	operator memory_range()
	{
		return memory_range(data_edit(), size());
	}
private:
	Cvirtual_binary_source* m_source;
};

#endif // !defined(AFX_VIRTUAL_BINARY_H__B59C9DC0_DB25_11D4_A95D_0050042229FC__INCLUDED_)