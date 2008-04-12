#include "stdafx.h"
#include "xcc universal container reader.h"
#include "ucr_library.h"

#include "string_conversion.h"

Cucr_library::Cucr_library()
{
	m_directories.insert("c:\\temp\\");
	m_directories.insert("c:\\command & conquer\\");
}

enum
{
	ki_containers,
	ki_directories,
};

Cxif_key Cucr_library::export_containers() const
{
	Cxif_key key;
	int j = 0;
	for (t_containers::const_iterator i = containers().begin(); i != containers().end(); i++)
		key.set_value_string(j++, *i);
	return key;
}

Cxif_key Cucr_library::export_directories() const
{
	Cxif_key key;
	int j = 0;
	for (t_directories::const_iterator i = directories().begin(); i != directories().end(); i++)
		key.set_value_string(j++, *i);
	return key;
}

Cxif_key Cucr_library::export() const
{
	Cxif_key key;
	key.open_key_write(ki_containers) = export_containers();
	key.open_key_write(ki_directories) = export_directories();
	return key;
}

void Cucr_library::import_containers(const Cxif_key& key)
{
	for (t_xif_value_map::const_iterator i = key.m_values.begin(); i != key.m_values.end(); i++)
		m_containers.insert(i->second.get_string());
}

void Cucr_library::import_directories(const Cxif_key& key)
{
	for (t_xif_value_map::const_iterator i = key.m_values.begin(); i != key.m_values.end(); i++)
		m_directories.insert(i->second.get_string());
}

void Cucr_library::import(const Cxif_key& key)
{
	import_containers(key.open_key_read(ki_containers));
	import_directories(key.open_key_read(ki_directories));
}

void Cucr_library::scan(const Cucr_formats& formats)
{
	m_containers.clear();
	const Cucr_formats::t_list& list = formats.list();
	for (Cucr_formats::t_list::const_iterator i = list.begin(); i != list.end(); i++)
		scan(*i);
}

void Cucr_library::scan(const Cucr_format& format)
{
	const Cucr_format::t_registry_keys& list = format.registry_keys();
	for (Cucr_format::t_registry_keys::const_iterator i = list.begin(); i != list.end(); i++)
	{
		const string& registry_key = *i;
		if (registry_key.find("hkey_local_machine") != 0)
			continue;
		int e = registry_key.rfind('\\');
		if (e == string::npos)
			continue;
		HKEY h;
		if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, registry_key.substr(19, e - 19).c_str(), 0, KEY_QUERY_VALUE, &h))
		{
			DWORD type;
			Cvirtual_binary data;
			DWORD cb_data = 0;
			if (ERROR_SUCCESS == RegQueryValueEx(h, registry_key.substr(e + 1).c_str(), NULL, &type, NULL, &cb_data)
				&& type == REG_SZ)
			{
				if (ERROR_SUCCESS == RegQueryValueEx(h, registry_key.substr(e + 1).c_str(), NULL, &type, data.write_start(cb_data), &cb_data))
					scan(format, string(reinterpret_cast<const char*>(data.data()), data.size()));
			}
			RegCloseKey(h);
		}
	}
	{
		for (t_directories::const_iterator i = directories().begin(); i != directories().end(); i++)
			scan(format, *i);
	}
}

void Cucr_library::scan(const Cucr_format& format, string dir)
{
	int e = dir.rfind('\\');
	if (e == string::npos)
		return;
	dir.erase(e + 1);
	const Cucr_format::t_extensions& list = format.extensions();
	for (Cucr_format::t_extensions::const_iterator i = list.begin(); i != list.end(); i++)
		scan(format, dir, *i);
}

void Cucr_library::scan(const Cucr_format& format, string dir, string ext)
{
	WIN32_FIND_DATA fd;
	{
		HANDLE h_find = FindFirstFile((dir + "*").c_str(), &fd);
		if (h_find != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && fd.cFileName[0] != '.')
					scan(format, dir + fd.cFileName + "\\", ext);
			}
			while (FindNextFile(h_find, &fd));
			FindClose(h_find);
		}
	}
	{
		HANDLE h_find = FindFirstFile((dir + "*." + ext).c_str(), &fd);
		if (h_find != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (~fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					m_containers.insert(to_lower(dir + fd.cFileName));
			}
			while (FindNextFile(h_find, &fd));
			FindClose(h_find);
		}
	}
}

void Cucr_library::insert_directory(const string& v)
{
	m_directories.insert(v);
}

void Cucr_library::erase_directory(const string& v)
{
	m_directories.erase(v);
}