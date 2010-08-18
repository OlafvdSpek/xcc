#include "stdafx.h"
#include "rules_ts_ini_reader.h"

#include "multi_line.h"

static const char* section_code[] = 
{
	"infantrytypes",
	"buildingtypes",
	"aircrafttypes",
	"vehicletypes",
	"terraintypes",
	"smudgetypes",
	"overlaytypes",
	"animations",
	"voxelanims",
	"particles",
	"particlesystems",
	"warheads",
	"projectiles",
	"unknown",
};

Crules_ts_ini_reader::Crules_ts_ini_reader()
{
	lower_case(false);
}

int Crules_ts_ini_reader::process_section_start(const string& line)
{
	m_current_entry = NULL;
	m_section = static_cast<t_section_id>(find_id(to_lower_copy(line), section_code, sei_unknown));
	if (m_section == sei_unknown)
		m_current_entry = &m_rules_list[line];
	return 0;
}

bool Crules_ts_ini_reader::process_section() const
{
	return m_current_entry || m_section != sei_unknown;
}

int Crules_ts_ini_reader::process_key(const string& name, const string& value)
{
	if (m_current_entry)
	{
		(*m_current_entry)[name] = value;
		if (name == "Projectile")
			m_projectile_type_list[value];
		return 0;
	}
	switch (m_section)
	{
	case sei_infantry_types:
		m_infantry_type_list[value];
		break;
	case sei_building_types:
		m_building_type_list[value];
		break;
	case sei_aircraft_types:
		m_aircraft_type_list[value];
		break;
	case sei_vehicle_types:
		m_vehicle_type_list[value];
		break;
	case sei_terrain_types:
		m_terrain_type_list[value];
		break;
	case sei_smudge_types:
		m_smudge_type_list[value];
		break;
	case sei_overlay_types:
		m_overlay_type_list[value];
		break;
	case sei_animations:
		m_animation_list[atoi(name.c_str())] = value;
		break;
	case sei_voxel_animations:
		m_voxel_animation_list[value];
		break;
	case sei_particles:
		m_particle_type_list[value];
		break;
	case sei_particle_systems:
		m_particle_system_type_list[value];
		break;
	case sei_warhead_types:
		m_warhead_type_list[value];
		break;
	case sei_projectile_types:
		m_projectile_type_list[value];
		break;
	case sei_unknown:
		break;
	}
	return 0;
}

bool Crules_ts_ini_reader::is_valid() const
{
	return false;
}
