#include "stdafx.h"
#include "pak_file.h"

#include "string_conversion.h"

void Cpak_file::close()
{
	m_index.clear();
	Ccc_file_small::close();
}

bool Cpak_file::is_valid()
{
	int size = get_size();
	if (5 > size)
		return false;
	const byte* r = data();
	int o1 = *reinterpret_cast<const __int32*>(r);
	if (o1 < 5 || o1 > size)
		return false;
	int ol = o1;
	const void* r_end = data() + o1;
	while (r < r_end)
	{
		int o = *reinterpret_cast<const __int32*>(r);
		r += 4;
		if (!o)
			return r - data() == o1;
		r += strlen(reinterpret_cast<const char*>(r)) + 1;
		if (o < ol || o > size)
			return false;
		ol = o;
	}
	return false;
}

int Cpak_file::post_open()
{
	if (!is_valid())
		return 1;
	const byte* r = data();
	int next_offset;
	do
	{
		t_index_entry e;
		e.offset = *reinterpret_cast<const __int32*>(r);
		r += 4;
		string name = reinterpret_cast<const char*>(r);
		r += name.length() + 1;
		next_offset = *reinterpret_cast<const __int32*>(r);
		e.size = (next_offset ? next_offset: get_size()) - e.offset;
		m_index[to_lower_copy(name)] = e;
	}
	while (next_offset);
	return 0;
}