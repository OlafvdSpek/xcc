// gr_ini_reader.cpp: implementation of the Cgr_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "gr_ini_reader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

bool opens_sub_section(const string& v)
{
	const char* opens_sub_section[] =
	{
		"AnimatingPart",
		"ApplyRandomForce",
		"ArmorSet",
		"Attack",
		"AttackContinueAreaRadiusCursor",
		"AttackDamageAreaRadiusCursor",
		"AttackScatterAreaRadiusCursor",
		"Behavior",
		"Body",
		"ConditionState",
		"CreateDebris",
		"CreateObject",
		"DefaultConditionState",
		"DeliverPayload",
		"DeliveryDecal",
		"Draw",
		"DynamicGameLOD",
		"EvaEvent",
		"FXListAtBonePos",
		"FireWeapon",
		"FriendlySpecialPowerRadiusCursor",
		"GameData",
		"GuardAreaRadiusCursor",
		"ImagePart",
		"LightPulse",
		"Locomotor",
		"Mission",
		"Object",
		"OffensiveSpecialPowerRadiusCursor",
		"ParticleSystem", // fxlist
		"Prerequisites",
		"SideInfo",
		"SideSounds",
		"SkillSet1",
		"SkillSet2",
		"SkillSet3",
		"SkillSet4",
		"SkillSet5",
		"SkirmishBuildList",
		"Sound",
		"StaticGameLOD",
		"Structure",
		"TerrainScorch",
		"Tracer",
		"TransitionState",
		"UnitSpecificSounds",
		"ViewShake",
		"WeaponSet",
		NULL
	};

	const char** r = opens_sub_section;
	while (*r && *r != v)
		r++;
	return *r && *r == v;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cgr_ini_reader::Csection::Csection()
{
}

Cgr_ini_reader::Csection::Csection(const string& _name, const string& _value)
{
	name = _name;
	value = _value;
}

ostream& Cgr_ini_reader::Csection::export(ostream& os, int t) const
{
	if (!name.empty())
	{
		os << string(t, '\t') << name;
		if (!value.empty())
			os << '=' << value;
		os << endl;
	}
	for (Csection::t_sections::const_iterator i = sections.begin(); i != sections.end(); i++)
		i->export(os, t + 1);
	if (opens_sub_section(name))
		os << string(t, '\t') << "End" << endl;
	return os;
}

Cgr_ini_reader::Cgr_ini_reader()
{
}

Cgr_ini_reader::Cgr_ini_reader(const Cvirtual_binary& d)
{
	import(d);
}

static void export(ostream& os, Cgr_ini_reader::t_sections::const_iterator i)
{
	if (i->second.first.empty())
		os << i->first << endl;
	else
		os << i->second.first << ' ' << i->first << endl;
	ostream& operator<<(ostream& os, const Cgr_ini_reader::Csection& v);
	os << i->second.second
		<< "End" << endl
		<< endl;
}

ostream& Cgr_ini_reader::export(ostream& os) const
{
	for (t_sections::const_iterator i = m_sections.begin(); i != m_sections.end(); i++)
		::export(os, i);
	return os;
}

int Cgr_ini_reader::import(const Cvirtual_binary& d)
{
	m_s = m_r = reinterpret_cast<const char*>(d.data());
	m_s_end = m_s + d.size();
	return read_sections();
}

void Cgr_ini_reader::eat_white()
{
	while (m_r < m_s_end && (*m_r == '\t' || *m_r == ' '))
		m_r++;
}

void Cgr_ini_reader::eat_newline()
{
	while (m_r < m_s_end && (*m_r == '\t' || *m_r == '\n' || *m_r == '\r' || *m_r == ' '))
		m_r++;
	if (m_r < m_s_end && *m_r == ';')
	{
		while (m_r < m_s_end && *m_r != '\n' && *m_r != '\r')
			m_r++;
		eat_newline();
	}
}

int Cgr_ini_reader::read_string(const string& a, string& v)
{
	const char* t = m_r;
	const char* u = m_r;
	while (m_r < m_s_end && a.find_first_of(*m_r) == string::npos)
	{
		if (*m_r != '\t' && *m_r != ' ')
			u = m_r + 1;
		m_r++;
	}
	v = string(t, u - t);
	eat_white();
	return 0;
}

int Cgr_ini_reader::read_section(Csection& section)
{
	while (m_r < m_s_end)
	{
		eat_newline();
		string entry_name;
		if (read_string("\n\r ;=", entry_name))
			return 1;
		if (!stricmp(entry_name.c_str(), "End"))
			return 0;
		if (m_r < m_s_end && *m_r == '=')
			m_r++;				
		eat_white();
		string entry_value;
		if (read_string("\n\r;", entry_value))
			return 1;
		section.sections.push_back(Csection(entry_name, entry_value));
		if (opens_sub_section(entry_name))
		{
			if (read_section(*section.sections.rbegin()))
				return 1;
		}
	}
	return 1;
}

int Cgr_ini_reader::read_sections()
{
	m_sections.clear();
	eat_newline();
	while (m_r < m_s_end)
	{
		string section_t;
		string section_name;
		if (read_string("\t\n\r ;", section_t)
			|| read_string("\t\n\r;", section_name))
			return 1;
		if (section_name.empty())
		{
			section_name = section_t;
			section_t.erase();
		}
		/*
		if (!stricmp(section_name.c_str(), "End"))
			cout << section_name << endl;
		*/
		m_sections[section_name].first = section_t;
		if (read_section(m_sections.find(section_name)->second.second))
			return 1;
		eat_newline();
	}
	return 0;
}

ostream& operator<<(ostream& os, const Cgr_ini_reader& v)
{
	return v.export(os);
}

ostream& operator<<(ostream& os, const Cgr_ini_reader::Csection& v)
{
	return v.export(os, 0);
}

