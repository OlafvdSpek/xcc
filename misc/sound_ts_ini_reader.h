#pragma once

#include <map>
#include "ini_reader.h"

using namespace std;

class Csound_data
{
public:
	Csound_data();
	void priority(int v);
	void volume(float v);

	int priority() const
	{
		return m_priority;
	}

	float volume() const
	{
		return m_volume;
	}
private:
	int m_priority;
	float m_volume;
};

class Csound_ts_ini_reader : public Cini_reader
{
public:
	enum t_section_id {sei_sounds, sei_unknown};
	enum t_sound_id {soi_priority, soi_volume, soi_unknown};
	using t_sound_list = map<string, Csound_data, less<>>;

	int process_section_start(string_view) override;
	bool process_section() const override;
	int process_key(string_view, string_view) override;
	bool is_valid() const;

	const t_sound_list& get_sound_list() const
	{
		return m_sound_list;
	}
private:
	string m_current_sound;
	t_section_id m_section = sei_unknown;
	t_sound_list m_sound_list;
};
