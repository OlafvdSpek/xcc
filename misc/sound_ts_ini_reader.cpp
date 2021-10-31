#include "stdafx.h"
#include "sound_ts_ini_reader.h"

Csound_data::Csound_data()
{
	m_priority = 10;
	m_volume = 1;
}

void Csound_data::priority(int v)
{
	m_priority = v;
}

void Csound_data::volume(float v)
{
	m_volume = v;
}

static const char* section_code[] = {"soundlist", "unknown"};
static const char* sound_code[] = {"priority", "volume", "unknown"};

int Csound_ts_ini_reader::process_section_start(string_view line)
{
	m_section = t_section_id(find_id(line, section_code, sei_unknown));
	if (m_section != sei_unknown)
		return 0;
	if (!m_sound_list.count(line))
		return 1;
	m_current_sound = line;
	return 0;
}

bool Csound_ts_ini_reader::process_section() const
{
	return true;
}

int Csound_ts_ini_reader::process_key(string_view name, string_view value)
{
	switch (m_section)
	{
	case sei_sounds:
		m_sound_list[to_lower_copy(string(value))];
		break;
	case sei_unknown:
		switch (find_id(name, sound_code, soi_unknown))
		{
		case soi_priority:
			m_sound_list[m_current_sound].priority(to_int(value));
			break;
		case soi_volume:
			m_sound_list[m_current_sound].volume(to_float(value));
			break;
		default:
			return 1;
		}
	}
	return 0;
}

bool Csound_ts_ini_reader::is_valid() const
{
	return m_sound_list.size();
}
