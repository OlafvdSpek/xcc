// stream_reader.h: interface for the Cstream_reader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STREAM_READER_H__FC96F4EB_360D_4836_9D31_2C0D0D0377A8__INCLUDED_)
#define AFX_STREAM_READER_H__FC96F4EB_360D_4836_9D31_2C0D0D0377A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "virtual_binary.h"

class Cstream_reader  
{
public:
	const byte* d() const
	{
		return m_d;
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
		m_r = m_d + o;
	}

	void skip(int o)
	{
		m_r += o;
	}

	Cstream_reader()
	{
	}

	Cstream_reader(const Cvirtual_binary& d)
	{
		m_r = m_d = d;
	}
private:
	Cvirtual_binary m_d;
	const byte* m_r;
};

#endif // !defined(AFX_STREAM_READER_H__FC96F4EB_360D_4836_9D31_2C0D0D0377A8__INCLUDED_)