/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <map>
#include "ini_reader.h"

class Crules_ts_ini_reader : public Cini_reader
{
public:
	using t_key_list = map<string, string>;
	using t_object_type_list = map<string, t_key_list>;
	using t_aircraft_type_list = t_object_type_list;
	using t_building_type_list = t_object_type_list;
	using t_infantry_type_list = t_object_type_list;
	using t_overlay_type_list = t_object_type_list;
	using t_smudge_type_list = t_object_type_list;
	using t_terrain_type_list = t_object_type_list;
	using t_vehicle_type_list = t_object_type_list;
	using t_animation_list = map<int, string>;
	using t_voxel_animation_list = t_object_type_list;
	using t_particle_type_list = t_object_type_list;
	using t_particle_system_type_list = t_object_type_list;
	using t_projectile_type_list = t_object_type_list;
	using t_rules_list = t_object_type_list;
	using t_warhead_type_list = t_object_type_list;
	using t_weapon_type_list = t_object_type_list;
	
	Crules_ts_ini_reader();
	int process_section_start(const string& line);
	bool process_section() const;
	int process_key(const string& name, const string& value);
	bool is_valid() const;

	const t_infantry_type_list& get_infantry_type_list() const
	{
		return m_infantry_type_list;
	}

	const t_building_type_list& get_building_type_list() const
	{
		return m_building_type_list;
	}

	const t_aircraft_type_list& get_aircraft_type_list() const
	{
		return m_aircraft_type_list;
	}

	const t_vehicle_type_list& get_vehicle_type_list() const
	{
		return m_vehicle_type_list;
	}

	const t_terrain_type_list& get_terrain_type_list() const
	{
		return m_terrain_type_list;
	}

	const t_smudge_type_list& get_smudge_type_list() const
	{
		return m_smudge_type_list;
	}

	const t_overlay_type_list& get_overlay_type_list() const
	{
		return m_overlay_type_list;
	}

	const t_animation_list& get_animation_list() const
	{
		return m_animation_list;
	}

	const t_voxel_animation_list& get_voxel_animation_list() const
	{
		return m_voxel_animation_list;
	}

	const t_particle_type_list& get_particle_type_list() const
	{
		return m_particle_type_list;
	}

	const t_particle_system_type_list& get_particle_system_type_list() const
	{
		return m_particle_system_type_list;
	}

	const t_projectile_type_list& get_projectile_type_list() const
	{
		return m_projectile_type_list;
	}

	const t_object_type_list& get_rules_list() const
	{
		return m_rules_list;
	}

	const t_warhead_type_list& get_warhead_type_list() const
	{
		return m_warhead_type_list;
	}

	const t_weapon_type_list& get_weapon_type_list() const
	{
		return m_weapon_type_list;
	}
private:
	enum t_section_id 
	{
		sei_infantry_types, 
		sei_building_types,
		sei_aircraft_types,
		sei_vehicle_types,
		sei_terrain_types,
		sei_smudge_types,
		sei_overlay_types,
		sei_animations,
		sei_voxel_animations,
		sei_particles,
		sei_particle_systems,
		sei_warhead_types,
		sei_projectile_types,
		sei_unknown,
		sei_infantry_type ,
		sei_building_type,
		sei_aircraft_type,
		sei_vehicle_type,
		sei_terrain_type,
		sei_smudge_type,
		sei_overlay_type,
		sei_animation,
		sei_voxel_animation,
		sei_particle,
		sei_particle_system,
		sei_warhead_type,
		sei_projectile_type
	};

	t_key_list* m_current_entry;
	t_infantry_type_list m_infantry_type_list;
	t_building_type_list m_building_type_list;
	t_aircraft_type_list m_aircraft_type_list;
	t_vehicle_type_list m_vehicle_type_list;
	t_terrain_type_list m_terrain_type_list;
	t_smudge_type_list m_smudge_type_list;
	t_overlay_type_list m_overlay_type_list;
	t_animation_list m_animation_list;
	t_voxel_animation_list m_voxel_animation_list;
	t_particle_type_list m_particle_type_list;
	t_particle_system_type_list m_particle_system_type_list;
	t_projectile_type_list m_projectile_type_list;
	t_object_type_list m_rules_list;
	t_warhead_type_list m_warhead_type_list;
	t_weapon_type_list m_weapon_type_list;
	t_key_list m_unknown_entry;
	t_section_id m_section;
	string m_section_name;
};
