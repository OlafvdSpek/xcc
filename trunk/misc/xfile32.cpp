// xfile32.cpp: implementation of the Cxfile32 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "assert.h"
#include "xfile32.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cxfile32::Cxfile32()
{
	fopen = false;
	pcache = 0;
}

Cxfile32::~Cxfile32()
{
	assert(!fopen);
}

long Cxfile32::open(const string &fname, dword access, dword creation, dword share, dword attributes)
{
	assert(!fopen);
	fhandle = CreateFile(fname.c_str(), access, share, 0, creation, attributes, 0);
	if (fhandle == INVALID_HANDLE_VALUE)
		return 1;
	pos = 0;
	fopen = true;
	fsize = get_size();
	return 0;
}

void Cxfile32::close()
{
	assert(fopen);	
	enable_cache(false);		
	CloseHandle(fhandle);
	fopen = false;
}

dword Cxfile32::get_size() const
{
	assert(fopen);
	dword result = GetFileSize(fhandle, 0);
	if (result == -1)
		throw Cxfile32_error();
	return result;
}

void Cxfile32::read(void* data, dword size)
{
	assert(fopen);
	if (!pcache)
	{
		//cache disabled
		if (SetFilePointer(fhandle, pos, 0, FILE_BEGIN) == -1)
			throw Cxfile32_read_error();
		dword cb_read;
		if (!ReadFile(fhandle, data, size, &cb_read, 0) || cb_read != size)
			throw Cxfile32_read_error();
	}
	else
	{
		//cache enabled
		if (pos + size > fsize)
			throw Cxfile32_read_error();
		memcpy(data, &pcache[pos], size);
	}
	pos += size;
	return;
}

void Cxfile32::write(void* data, dword size)
{
	assert(fopen && !pcache);
	if (SetFilePointer(fhandle, pos, 0, FILE_BEGIN) == -1)
		throw Cxfile32_write_error();
	dword cb_write;
	if (!WriteFile(fhandle, data, size, &cb_write, 0) || cb_write != size)
		throw Cxfile32_write_error();
	pos += size;
}

void Cxfile32::read_line(string &s)
{
	if (pos == fsize)
		throw Cxfile32_read_error();
	assert(pcache);
	dword spos = pos;
	while (spos < fsize)
	{
		if (pcache[spos] == 0xd)
			break;
		spos++;
	}
	s = "";
	while (pos < spos)
		s = s + char(pcache[pos++]);
	if (pos < fsize)
	{
		pos++;
		if (pos < fsize && pcache[pos] == 0xa)
			pos++;
	}
}

bool Cxfile32::is_open()
{
	return fopen;
}

void Cxfile32::seek(dword ipos)
{
	assert(fopen);
	pos = ipos;
}

void Cxfile32::skip(dword ipos)
{
	assert(fopen);
	pos += ipos;
}

void Cxfile32::enable_cache(bool v)
{
	if (v)
	{
		//enable cache
		if (pcache)
			//cache already enabled
			return;
		dword size = get_size();
		byte* p = new byte[size];
			//not in pcache, because read uses it to see if the cache is enabled
		pos = 0;
		seek(0);
		read(p, size);
		pcache = p;
		pos = 0;
	}
	else
	{
		//disable cache
		if (!pcache)
			//cache already disabled
			return;
		delete[] pcache;
		pcache = 0;
	}
}

bool Cxfile32::eof()
{
	return pos == fsize;
}