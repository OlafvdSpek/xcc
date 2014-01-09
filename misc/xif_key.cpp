#include "stdafx.h"
#include "xif_key.h"

#include <bzip/bzlib.h>
#include <string_conversion.h>
#include <zlib.h>

#pragma comment(lib, "libbz2.lib")
#pragma comment(lib, "zlib.lib")

template <class T>
static T read(const byte*& r)
{
	T v = *reinterpret_cast<const T*>(r);
	r += sizeof(T);
	return v;
}

template <class T>
static void write(byte*& w, T v)
{
	*reinterpret_cast<T*>(w) = v;
	w += sizeof(T);
}

static int read_int(const byte*& r)
{
	return read<int>(r);
}

void Cxif_key::load_old(const byte*& data)
{
	{
		// keys
		int count = read_int(data);
		while (count--)
		{
			Cxif_key& i = set_key(read_int(data));
			i.load_old(data);
		}
	}

	{
		// values
		int count = read_int(data);
		while (count--)
		{
			Cxif_value& i = set_value(read_int(data));
			i.load_old(data);
		}
	}
}

void Cxif_key::load_new(const byte*& data)
{
	{
		// keys
		int count = read_int(data);
		int id = 0;
		while (count--)
		{
			id += read_int(data);
			open_key_write(id).load_new(data);
		}
	}

	{
		// values
		int count = read_int(data);
		int id = 0;
		while (count--)
		{
			id += read_int(data);
			open_value_write(id).load_new(data);
		}
	}
}

void Cxif_key::load_external(const byte*& data)
{
	for (auto& i : m_keys)
		i.second.load_external(data);
	for (auto& i : m_values)
		i.second.load_external(data);
}

int Cxif_key::get_size() const
{
	int size = 8;
	for (auto& i : m_keys)
		size += 4 + i.second.get_size();
	for (auto& i : m_values)
	{
		size += 9;
		switch (i.second.get_type())
		{
		case vt_bin32:
		case vt_int32:
			break;
		default:
			if (!i.second.external_data())
				size += i.second.get_size();
		}
	}
	return size;
}

int Cxif_key::get_external_size() const
{
	int size = 0;
	for (auto& i : m_keys)
		size += i.second.get_external_size();
	for (auto& i : m_values)
	{
		if (i.second.external_data())
			size += i.second.get_size();
	}
	return size;
}

void Cxif_key::save(byte*& data) const
{
	{
		// keys
		write<__int32>(data, m_keys.size());
		int id = 0;
		for (auto& i : m_keys)
		{
			*reinterpret_cast<int*>(data) = i.first - id;
			id = i.first;
			data += 4;
			i.second.save(data);
		}
	}

	{
		// values
		write<__int32>(data, m_values.size());
		int id = 0;
		for (auto& i : m_values)
		{
			*reinterpret_cast<int*>(data) = i.first - id;
			id = i.first;
			data += 4;
			i.second.save(data);
		}
	}
}

void Cxif_key::external_save(byte*& data) const
{
	for (auto& i : m_keys)
		i.second.external_save(data);
	for (auto& i : m_values)
		i.second.external_save(data);
}

static void dump_spaces(ostream& os, int count)
{
	while (count--)
		os << ' ';
}

void Cxif_key::dump_ratio(ostream& os, Cvirtual_binary* t) const
{
	int cb_s = get_size();
	unsigned long cb_z = cb_s + (cb_s + 999) / 1000 + 12;
	if (!t->data())
		t->write_start(cb_s + cb_z);
	assert(t->size() >= cb_s + cb_z);
	byte* w = t->data_edit();
	save(w);
	if (Z_OK == compress(t->data_edit() + cb_s, &cb_z, t->data(), cb_s))
		os << " (" << cb_z << '/' << cb_s << ')';
}

void Cxif_key::dump(ostream& os, bool show_ratio, int depth, Cvirtual_binary* t) const
{
	bool own_t = !t;
	if (own_t)
	{
		t = new Cvirtual_binary;
		os << "K\\";
		dump_ratio(os, t);
		os << ':' << endl;
		depth++;
	}
	for (auto& i : m_keys)
	{
		dump_spaces(os, depth << 1);
		os << 'K' << nh(8, i.first);
		int cb_s = i.second.get_size();
		if (show_ratio && cb_s > 64)
			i.second.dump_ratio(os, t);
		os << ':' << endl;
		i.second.dump(os, show_ratio, depth + 1, t);
	}
	for (auto& i : m_values)
	{
		dump_spaces(os, depth << 1);
		os << 'V' << nh(8, i.first);
		int cb_s = i.second.get_size();
		if (show_ratio && cb_s > 64)
		{
			unsigned long cb_z = t->size();
			if (Z_OK == compress(t->data_edit(), &cb_z, i.second.get_data(), cb_s))
				os << " (" << cb_z << '/' << cb_s << ')';
		}
		os << ": ";
		i.second.dump(os, depth + 1);
	}
	if (own_t)
		delete t;
}

int Cxif_key::load_key(const byte* data, int size)
{
	const byte* read_p = data;
	const t_xif_header_fast& header = *reinterpret_cast<const t_xif_header_fast*>(read_p);
	if (size < sizeof(t_xif_header_old)
		|| header.id != file_id
		|| header.version != file_version_old && header.version != file_version_new && header.version != file_version_fast)
		return 1;
	int error = 0;
	if (header.version == file_version_old)
	{
		read_p += sizeof(t_xif_header_old) - 4;
		load_old(read_p);
		error = size != read_p - data;
	}
	else
	{
		unsigned long cb_d = header.size_uncompressed;
		if (cb_d)
		{
			Cvirtual_binary d;
			if (header.version == file_version_new)
				error = Z_OK != uncompress(d.write_start(cb_d), &cb_d, data + sizeof(t_xif_header_old), size - sizeof(t_xif_header_old));
			else
			{
				if (memcmp(data + sizeof(t_xif_header_fast), "BZh", 3))
					error = Z_OK != uncompress(d.write_start(cb_d), &cb_d, data + sizeof(t_xif_header_fast), header.size_compressed);
				else
					error = BZ_OK != BZ2_bzBuffToBuffDecompress(reinterpret_cast<char*>(d.write_start(cb_d)), reinterpret_cast<unsigned int*>(&cb_d), const_cast<char*>(reinterpret_cast<const char*>(data + sizeof(t_xif_header_fast))), header.size_compressed, 0, 0);
			}
			// d.export("c:/temp/xif data.bin");
			if (!error)
			{
				read_p = d.data();
				load_new(read_p);
				error = read_p != d.data_end();
				if (header.version == file_version_fast && !error)
				{
					read_p = data + sizeof(t_xif_header_fast) + header.size_compressed;
					load_external(read_p);
					error = size != read_p - data;
				}
			}
		}
		else
		{
			read_p = data + (header.version == file_version_fast ? sizeof(t_xif_header_fast) : sizeof(t_xif_header_old));
			load_new(read_p);
			load_external(read_p);
			error = size != read_p - data;
		}
	}
	return error;
}

Cvirtual_binary Cxif_key::vdata(bool fast) const
{
	Cvirtual_binary d;
	int size = get_size();
	int external_size = get_external_size();
	if (fast)
	{
		t_xif_header_fast& header = *reinterpret_cast<t_xif_header_fast*>(d.write_start(sizeof(t_xif_header_fast) + size + external_size));
		header.id = file_id;
		header.version = file_version_fast;
		header.size_uncompressed = 0;
		header.size_compressed = size;
		header.size_external = external_size;
		byte* w = d.data_edit() + sizeof(t_xif_header_fast);
		save(w);
		external_save(w);
		assert(d.data_end() == w);
		return d;
	}
	Cvirtual_binary s;
	byte* w = s.write_start(size);
	save(w);
	unsigned long cb_d = s.size() + (s.size() + 999) / 1000 + 12;
	t_xif_header_fast& header = *reinterpret_cast<t_xif_header_fast*>(d.write_start(sizeof(t_xif_header_fast) + cb_d + external_size));
	compress(d.data_edit() + sizeof(t_xif_header_fast), &cb_d, s.data(), s.size());
	w = d.data_edit() + sizeof(t_xif_header_fast) + cb_d;
	external_save(w);
	header.id = file_id;
	header.version = file_version_fast;
	header.size_uncompressed = size;
	header.size_compressed = cb_d;
	header.size_external = external_size;
	d.size(sizeof(t_xif_header_fast) + cb_d + external_size);
	return d;
}

Cvirtual_binary Cxif_key::export_bz() const
{
	Cvirtual_binary d;
	int size = get_size();
	int external_size = get_external_size();
	Cvirtual_binary s;
	byte* w = s.write_start(size);
	save(w);
	unsigned int cb_d = s.size() + (s.size() + 99) / 100 + 600;
	t_xif_header_fast& header = *reinterpret_cast<t_xif_header_fast*>(d.write_start(sizeof(t_xif_header_fast) + cb_d + external_size));
	if (BZ_OK != BZ2_bzBuffToBuffCompress(reinterpret_cast<char*>(d.data_edit() + sizeof(t_xif_header_fast)), &cb_d, const_cast<char*>(reinterpret_cast<const char*>(s.data())), s.size(), 9, 0, 0))
		return Cvirtual_binary();
	w = d.data_edit() + sizeof(t_xif_header_fast) + cb_d;
	external_save(w);
	header.id = file_id;
	header.version = file_version_fast;
	header.size_uncompressed = size;
	header.size_compressed = cb_d;
	header.size_external = external_size;
	d.size(sizeof(t_xif_header_fast) + cb_d + external_size);
	return d;
}