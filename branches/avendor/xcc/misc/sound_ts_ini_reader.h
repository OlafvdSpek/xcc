// sound_ts_ini_reader.h: interface for the Csound_ts_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUND_TS_INI_READER_H__D91E9100_7E8B_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_SOUND_TS_INI_READER_H__D91E9100_7E8B_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

class Csound_ts_ini_reader: public Cini_reader
{
public:
	enum t_section_id {sei_sounds, sei_unknown};
	enum t_sound_id {soi_priority, soi_volume, soi_unknown};
	typedef map<string, Csound_data> t_sound_list;

	Csound_ts_ini_reader();
	void erase();
	int process_section_start(const string& line);
	bool process_section() const;
	int process_key(const string& name, const string& value);
	bool is_valid() const;

	const t_sound_list& get_sound_list() const
	{
		return m_sound_list;
	}
private:
	string m_current_sound;
	t_section_id m_section;
	t_sound_list m_sound_list;
};

#endif // !defined(AFX_SOUND_TS_INI_READER_H__D91E9100_7E8B_11D4_B606_0000B4936994__INCLUDED_)
