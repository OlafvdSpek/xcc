#pragma once

#include "xd2_animation.h"
#include "xd2_audio.h"
#include "xd2_image.h"
#include "xd2_shape.h"

#pragma pack(push, 1)

struct t_building_type
{
	__int16 u0;
	__int16 name;
	__int8 u1;
	__int8 u2;
	__int16 u3;
	__int16 wsa;
	__int8 u4;
	__int8 u5;
	__int16 u6;
	__int16 u7;
	__int16 strength;
	__int16 sight;
	__int16 cameo_shp_index;
	__int16 cost;
	__int16 buildtime;
	__int16 techlevel;
	__int32 prerequisites;
	unsigned __int8 u8;
	unsigned __int8 upgrades_required;
	__int8 u9;
	__int8 u10;
	__int8 u11;
	__int8 u12;
	__int8 u13;
	__int8 u14;
	__int8 u15;
	__int8 u16;
	__int8 u17;
	__int16 hint;
	__int16 firepower;
	__int16 u18;
	unsigned __int8 houses;
	unsigned __int8 u19;
	unsigned __int8 u20;
	__int16 units_can_enter;
	__int16 spice_capacity;
	__int16 power_in;
	__int16 size;
	__int16 icon_index;
	__int8 u21;
	__int8 u22;
	__int16 u23;
	__int8 u24;
	__int8 u25;
	__int16 u26;
	__int8 u27;
	__int8 u28;
	__int16 u29;
	__int16 u30;
	__int16 u31;
	__int16 u32;
	__int16 u33;
	__int16 u34;
	__int16 u35;
	__int16 u36;
	__int16 u37;
	__int16 u38;
	__int16 u39;
	__int16 u40;
};

struct t_unit_type
{
	__int16 u0;
	__int16 name;
	__int8 u1;
	__int8 u2;
	__int16 u3;
	__int16 wsa;
	__int16 u4;
	__int16 u5;
	__int16 u6;
	__int16 strength;
	__int16 sight;
	__int16 cameo_shp_index;
	__int16 cost;
	__int16 buildtime;
	__int8 u7;
	__int8 u8;
	__int32 prerequisites;
	unsigned __int8 u9;
	unsigned __int8 upgrades_required;
	__int16 control_0;
	__int16 control_1;
	__int16 control_2;
	__int16 control_3;
	__int8 u10;
	__int8 u11;
	__int8 u12;
	__int16 u13;
	__int16 u14;
	unsigned __int8 houses;
	unsigned __int8 u15;
	__int8 u16;
	unsigned __int8 u17;
	__int8 u18;
	unsigned __int8 u19;
	unsigned __int8 u20;
	__int16 u21;
	__int16 u22;
	__int16 mobility;
	__int16 u23;
	__int16 speed;
	__int16 u24;
	__int16 body_shp_index;
	__int16 turret_shp_index;
	__int16 u25;
	__int16 u26;
	__int16 u27;
	__int16 reload_time;
	__int16 range;
	__int16 firepower;
	__int16 u28;
	__int16 projectile;
	__int16 u29;
};

#pragma pack(pop)

class Cxd2_files
{
public:
	const Cxd2_shape& shapes2() const;
	const Cxd2_image& shape(int i) const;
	int load(const Cxif_key_r& key);
	Cxif_key save() const;
	int load(const string& dir);

	const Cxd2_animation_map& animations() const
	{
		return m_animation_map;
	}

	const Cxd2_audio_map& audio() const
	{
		return m_audio_map;
	}

	const Cxd2_data_map& data_map() const
	{
		return m_data_map;
	}

	const Cxd2_image_map& images() const
	{
		return m_image_map;
	}

	const Cxd2_shape_map& shapes() const
	{
		return m_shape_map;
	}

	Cvirtual_binary exe() const
	{
		return m_exe;
	}

	boost::iterator_range<const t_building_type*> building_types() const
	{
		auto i = reinterpret_cast<const t_building_type*>(m_building_types.data());
		return boost::make_iterator_range(i, i + m_building_types.size() / sizeof(t_building_type));
	}

	boost::iterator_range<const t_unit_type*> unit_types() const
	{
		auto i = reinterpret_cast<const t_unit_type*>(m_unit_types.data());
		return boost::make_iterator_range(i, i + m_unit_types.size() / sizeof(t_unit_type));
	}
private:
	int load_audio_pak(const string& name);
	int load_pak(const string& name);
	int process();

	Cxd2_animation_map m_animation_map;
	Cxd2_audio_map m_audio_map;
	Cxd2_data_map m_data_map;
	Cxd2_image_map m_image_map;
	Cxd2_shape_map m_shape_map;

	Cvirtual_binary m_exe;
	Cvirtual_binary m_building_types;
	Cvirtual_binary m_unit_types;
};
