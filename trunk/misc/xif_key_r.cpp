#include "stdafx.h"
#include "xif_key_r.h"

#include <bzip/bzlib.h>
#include <zlib.h>
#include "xif_key.h"

template <class T>
static T read(const byte*& r)
{
	T v = *reinterpret_cast<const T*>(r);
	r += sizeof(T);
	return v;
}

int Cxif_key_r::import(Cvirtual_binary s)
{
	Cvirtual_binary d;
	const t_xif_header_fast& h = *reinterpret_cast<const t_xif_header_fast*>(s.data());
	if (s.size() < sizeof(t_xif_header_fast) + 8
		|| h.id != file_id
		|| h.version != file_version_fast)
		return 1;
	unsigned long cb_d = h.size_uncompressed;
	if (cb_d)
	{
		if (Z_OK != uncompress(d.write_start(cb_d), &cb_d, s.data() + sizeof(t_xif_header_fast), h.size_compressed)
			&& (memcmp(s.data() + sizeof(t_xif_header_fast), "BZh", 3)
			|| BZ_OK != BZ2_bzBuffToBuffDecompress(reinterpret_cast<char*>(d.write_start(cb_d)), reinterpret_cast<unsigned int*>(&cb_d), const_cast<char*>(reinterpret_cast<const char*>(s.data() + sizeof(t_xif_header_fast))), h.size_compressed, 0, 0)))
			return 1;
		/*
		if (uncompress(d.write_start(cb_d), &cb_d, s + sizeof(t_xif_header_fast), h.size_compressed) != Z_OK)
			return 1;
		*/
		load(d.data());
		// m_external_data = d + h.size_compressed;
	}
	else
	{
		load(s.data() + sizeof(t_xif_header_fast));
		// m_external_data = s + sizeof(t_xif_header_fast) + h.size_uncompressed
	}

	return 0;
}

int Cxif_key_r::load(const byte* s)
{
	const byte* r = s;
	{
		int count = read<int>(r);
		int id = 0;
		m_keys.reserve(count);
		while (count--)
		{
			id += read<int>(r);
			m_keys.push_back(make_pair(id, Cxif_key_r()));
			r += m_keys.rbegin()->second.load(r);
		}
	}
	{
		int count = read<int>(r);
		int id = 0;
		m_values.reserve(count);
		while (count--)
		{
			id += read<int>(r);
			m_values.push_back(make_pair(id, Cxif_value()));
			m_values.rbegin()->second.load_new(r);
		}
	}
	return r - s;
}

const Cxif_key_r* Cxif_key_r::find_key(int id) const
{
	for (auto& i : keys())
	{
		if (i.first == id)
			return &i.second;
	}
	return NULL;
}

const Cxif_value* Cxif_key_r::find_value(int id) const
{
	for (auto& i : values())
	{
		if (i.first == id)
			return &i.second;
	}
	return NULL;
}