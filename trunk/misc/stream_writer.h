// stream_writer.h: interface for the Cstream_writer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STREAM_WRITER_H__283B8C8E_68DD_4E16_9122_42ADD010E634__INCLUDED_)
#define AFX_STREAM_WRITER_H__283B8C8E_68DD_4E16_9122_42ADD010E634__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "virtual_binary.h"

class Cstream_writer  
{
public:
	/*
	const byte* d() const
	{
		return m_d;
	}

	const byte* d_end() const
	{
		return m_d.data_end();
	}
	*/

	byte* w() const
	{
		return m_w;
	}

	byte* write(int size)
	{
		byte* v = w();
		skip(size);
		return v;
	}

	int write_int(int v)
	{
		*reinterpret_cast<__int32*>(write(4)) = v;
	}

	int write_int(int o, int v)
	{
		seek(o);
		return write_int(v);
	}

	void write_string(const string& v)
	{
		memcpy(write(v.length() + 1), v.c_str(), v.length() + 1);
	}

	void write_string(int o, const string& v)
	{
		seek(o);
		write_string(v);
	}

	void seek(int o)
	{
		assert(false);
		// m_w = m_d.data_edit() + o;
	}

	void skip(int o)
	{
		m_w += o;
	}

	Cstream_writer()
	{
	}

	Cstream_writer(byte* w)
	{
		m_w = w;
	}
private:
	// Cvirtual_binary m_d;
	byte* m_w;
};

#endif // !defined(AFX_STREAM_WRITER_H__283B8C8E_68DD_4E16_9122_42ADD010E634__INCLUDED_)
