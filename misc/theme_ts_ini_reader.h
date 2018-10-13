#pragma once

#include <map>
#include "ini_reader.h"

using namespace std;

class Ctheme_data
{
public:
	Ctheme_data();
	void name(string v);
	void length(float v);
	void normal(bool v);
	void scenario(int v);
	void side(string v);
	void sound(string v);
	void repeat(bool v);

	string name() const
	{
		return m_name;
	}

	float length() const
	{
		return m_length;
	}

	bool normal() const
	{
		return m_normal;
	}

	int scenario() const
	{
		return m_scenario;
	}

	string side() const
	{
		return m_side;
	}

	string sound() const
	{
		return m_sound;
	}

	bool repeat() const
	{
		return m_repeat;
	}
private:
	string m_name;
	float m_length;
	bool m_normal;
	int m_scenario;
	string m_sound;
	string m_side;
	bool m_repeat;
};

class Ctheme_ts_ini_reader : public Cini_reader  
{
public:
	enum t_section_id {sei_themes, sei_unknown};
	enum t_theme_id {thi_name, thi_length, thi_normal, thi_scenario, thi_side, thi_sound, thi_repeat, thi_unknown};
	using t_theme_list = map<string, Ctheme_data>;

	Ctheme_ts_ini_reader();
	void erase();
	int process_section_start(const string& line);
	bool process_section() const;
	int process_key(const string& name, const string& value);
	bool is_valid() const;

	const t_theme_list& get_theme_list() const
	{
		return m_theme_list;
	}
private:
	string m_current_theme;
	t_section_id m_section;
	t_theme_list m_theme_list;
};
