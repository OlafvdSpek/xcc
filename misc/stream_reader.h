#pragma once

#include <virtual_binary.h>

class Cstream_reader
{
public:
	const byte* d() const
	{
		return m_d.data();
	}

	const byte* d_end() const
	{
		return m_d.data_end();
	}

	const byte* r() const
	{
		return m_r;
	}

	const byte* read(int size)
	{
		const byte* v = r();
		skip(size);
		return v;
	}

	short read_short()
	{
		return *reinterpret_cast<const __int16*>(read(2));
	}

	int read_int()
	{
		return *reinterpret_cast<const __int32*>(read(4));
	}

	int read_int(int o)
	{
		seek(o);
		return read_int();
	}

	const char* read_string()
	{
		return reinterpret_cast<const char*>(read(strlen(reinterpret_cast<const char*>(r())) + 1));
	}

	const char* read_string(int o)
	{
		seek(o);
		return read_string();
	}

	void seek(int o)
	{
		m_r = d() + o;
	}

	void skip(int o)
	{
		m_r += o;
	}

	Cstream_reader()
	{
	}

	Cstream_reader(const Cvirtual_binary& v)
	{
		m_d = v;
    m_r = d();
	}
private:
	Cvirtual_binary m_d;
	const byte* m_r;
};
