// art_ts_ini_reader.cpp: implementation of the Cart_ts_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "art_ts_ini_reader.h"
#include "string_conversion.h"

static const char* section_code[] = {"movies", "unknown"};

static const char* key_code[] =
{
	"activeanim",
	"activeanimdamaged",
	"activeanimfour",
	"activeanimfourdamaged",
	"activeanimfourzadjust",
	"activeanimpowered",
	"activeanimthree",
	"activeanimthreedamaged",
	"activeanimthreepowered",
	"activeanimthreepoweredlight",
	"activeanimthreex",
	"activeanimthreey",
	"activeanimthreeysort",
	"activeanimthreezadjust",
	"activeanimtwo",
	"activeanimtwodamaged",
	"activeanimtwopowered",
	"activeanimtwopoweredlight",
	"activeanimtwox",
	"activeanimtwoy",
	"activeanimtwoysort",
	"activeanimtwozadjust",
	"activeanimx",
	"activeanimy",
	"activeanimysort",
	"activeanimzadjust",
	"altimage",
	"altpalette",
	"angle",
	"animactive",
	"animhigh",
	"animlow",
	"animpalette",
	"animrate",
	"auxanim",
	"barrellength",
	"barreloffset",
	"bibshape",
	"bouncer",
	"buildup",
	"cameo",
	"chargeanim",
	"crater",
	"crawl",
	"crawls",
	"customrotor",
	"damage",
	"damageddoor",
	"damagelevels",
	"damageradius",
	"demandload",
	"demandloadbuildup",
	"deployinganim",
	"detaillevel",
	"die1",
	"die2",
	"die3",
	"die4",
	"die5",
	"dooranim",
	"doorstages",
	"down",
	"elasticity",
	"end",
	"expireanim",
	"extradamagestage",
	"extralight",
	"fireangle",
	"firefly",
	"fireprone",
	"fireup",
	"firingframes",
	"flamer",
	"flat",
	"fly",
	"foundation",
	"frames",
	"freebuildup",
	"gatestages",
	"guard",
	"height",
	"hover",
	"idle1",
	"idle2",
	"image",
	"isanimatedtiberium",
	"isflamingguy",
	"ismeteor",
	"istiberium",
	"isveins",
	"loopcount",
	"loopend",
	"loopstart",
	"maxxyvel",
	"midpoint",
	"minzvel",
	"newtheater",
	"next",
	"normalized",
	"normalzadjust",
	"pbarrellength",
	"pbarrelthickness",
	"pingpong",
	"powerup1anim",
	"powerup1animdamaged",
	"powerup1locx",
	"powerup1locxx",
	"powerup1locy",
	"powerup1locyy",
	"powerup1locz",
	"powerup1loczz",
	"powerup1ysort",
	"powerup2anim",
	"powerup2animdamaged",
	"powerup2locx",
	"powerup2locxx",
	"powerup2locy",
	"powerup2locyy",
	"powerup2locz",
	"powerup2loczz",
	"powerup2ysort",
	"powerup3anim",
	"powerup3animdamaged",
	"powerup3locx",
	"powerup3locy",
	"powerup3locz",
	"powerup3ysort",
	"preproductionanim",
	"preproductionanimzadjust",
	"primaryfireflh",
	"primaryfirepixeloffset",
	"productionanim",
	"productionanimdamaged",
	"productionanimx",
	"productionanimy",
	"productionanimysort",
	"productionanimzadjust",
	"prone",
	"randomloopdelay",
	"randomrate",
	"rate",
	"ready",
	"recoilless",
	"remapable",
	"report",
	"reverse",
	"rotates",
	"rotcount",
	"rotors",
	"runningframes",
	"sbarrellength",
	"scorch",
	"secondaryfireflh",
	"secondaryfirepixeloffset",
	"sequence",
	"shadowindex",
	"shouldfogremove",
	"shouldusecelldrawer",
	"silodamage",
	"simpledamage",
	"spawncount",
	"spawns",
	"specialanim",
	"specialanimdamaged",
	"specialanimthree",
	"specialanimthreezadjust",
	"specialanimtwo",
	"specialanimtwozadjust",
	"specialanimzadjust",
	"specialzoverlay",
	"start",
	"sticky",
	"surface",
	"terrainpalette",
	"theater",
	"tiberiumchainreaction",
	"tiberiumspawntype",
	"tiberiumspreadradius",
	"tiled",
	"tooverlay",
	"trailer",
	"traileranim",
	"trailerseperation",
	"translucency",
	"translucencydetaillevel",
	"translucent",
	"tumble",
	"turretnotexportedonground",
	"turretoffset",
	"underdooranim",
	"up",
	"usenormallight",
	"useturretshadow",
	"visibleload",
	"voxel",
	"walk",
	"walkframes",
	"warhead",
	"ydrawoffset",
	"ysortadjust",
	"zshapepointmove",
	"unknown"
};

Cart_ts_ini_reader::Cart_ts_ini_reader()
{
	lower_case(false);
	erase();
}

void Cart_ts_ini_reader::erase()
{
	m_art_list.clear();
	m_movie_list.clear();
};

int Cart_ts_ini_reader::process_section_start(const string& line)
{
	m_section = static_cast<t_section_id>(find_id(to_lower(line), section_code, sei_unknown));
	if (m_section == sei_unknown)
	{
		t_art_list::iterator i = m_art_list.find(line);
		if (i == m_art_list.end())
			m_current_entry = &m_art_list[line];
		else
			m_current_entry = &i->second;
	}
	return 0;
}

bool Cart_ts_ini_reader::process_section() const
{
	return true;
}

int Cart_ts_ini_reader::process_key(const string& name, const string& value)
{
	switch (m_section)
	{
	case sei_movies:
		m_movie_list.insert(to_lower(value));
		break;
	case sei_unknown:
		if (m_fast)
		{
			switch (find_id(name, key_code, kid_unknown))
			{
			case kid_activeanim:
			case kid_activeanimdamaged:
			case kid_activeanimfour:
			case kid_activeanimfourdamaged:
			case kid_activeanimfourzadjust:
			case kid_activeanimpowered:
			case kid_activeanimthree:
			case kid_activeanimthreedamaged:
			case kid_activeanimthreepowered:
			case kid_activeanimthreepoweredlight:
			case kid_activeanimthreex:
			case kid_activeanimthreey:
			case kid_activeanimthreeysort:
			case kid_activeanimthreezadjust:
			case kid_activeanimtwo:
			case kid_activeanimtwodamaged:
			case kid_activeanimtwopowered:
			case kid_activeanimtwopoweredlight:
			case kid_activeanimtwox:
			case kid_activeanimtwoy:
			case kid_activeanimtwoysort:
			case kid_activeanimtwozadjust:
			case kid_activeanimx:
			case kid_activeanimy:
			case kid_activeanimysort:
			case kid_activeanimzadjust:
			case kid_altimage:
			case kid_altpalette:
			case kid_angle:
			case kid_animactive:
			case kid_animhigh:
			case kid_animlow:
			case kid_animpalette:
			case kid_animrate:
			case kid_auxanim:
			case kid_barrellength:
			case kid_barreloffset:
			case kid_bibshape:
			case kid_bouncer:
			case kid_buildup:
			case kid_cameo:
			case kid_chargeanim:
			case kid_crater:
			case kid_crawl:
			case kid_crawls:
			case kid_customrotor:
			case kid_damage:
			case kid_damageddoor:
			case kid_damagelevels:
			case kid_damageradius:
			case kid_demandload:
			case kid_demandloadbuildup:
			case kid_deployinganim:
			case kid_detaillevel:
			case kid_die1:
			case kid_die2:
			case kid_die3:
			case kid_die4:
			case kid_die5:
			case kid_dooranim:
			case kid_doorstages:
			case kid_down:
			case kid_elasticity:
			case kid_end:
			case kid_expireanim:
			case kid_extradamagestage:
			case kid_extralight:
			case kid_fireangle:
			case kid_firefly:
			case kid_fireprone:
			case kid_fireup:
			case kid_firingframes:
			case kid_flamer:
			case kid_flat:
			case kid_fly:
			case kid_foundation:
			case kid_frames:
			case kid_freebuildup:
			case kid_gatestages:
			case kid_guard:
			case kid_height:
			case kid_hover:
			case kid_idle1:
			case kid_idle2:
			case kid_image:
			case kid_isanimatedtiberium:
			case kid_isflamingguy:
			case kid_ismeteor:
			case kid_istiberium:
			case kid_isveins:
			case kid_loopcount:
			case kid_loopend:
			case kid_loopstart:
			case kid_maxxyvel:
			case kid_midpoint:
			case kid_minzvel:
			case kid_newtheater:
			case kid_next:
			case kid_normalized:
			case kid_normalzadjust:
			case kid_pbarrellength:
			case kid_pbarrelthickness:
			case kid_pingpong:
			case kid_powerup1anim:
			case kid_powerup1animdamaged:
			case kid_powerup1locx:
			case kid_powerup1locxx:
			case kid_powerup1locy:
			case kid_powerup1locyy:
			case kid_powerup1locz:
			case kid_powerup1loczz:
			case kid_powerup1ysort:
			case kid_powerup2anim:
			case kid_powerup2animdamaged:
			case kid_powerup2locx:
			case kid_powerup2locxx:
			case kid_powerup2locy:
			case kid_powerup2locyy:
			case kid_powerup2locz:
			case kid_powerup2loczz:
			case kid_powerup2ysort:
			case kid_powerup3anim:
			case kid_powerup3animdamaged:
			case kid_powerup3locx:
			case kid_powerup3locy:
			case kid_powerup3locz:
			case kid_powerup3ysort:
			case kid_preproductionanim:
			case kid_preproductionanimzadjust:
			case kid_primaryfireflh:
			case kid_primaryfirepixeloffset:
			case kid_productionanim:
			case kid_productionanimdamaged:
			case kid_productionanimx:
			case kid_productionanimy:
			case kid_productionanimysort:
			case kid_productionanimzadjust:
			case kid_prone:
			case kid_randomloopdelay:
			case kid_randomrate:
			case kid_rate:
			case kid_ready:
			case kid_recoilless:
			case kid_remapable:
			case kid_report:
			case kid_reverse:
			case kid_rotates:
			case kid_rotcount:
			case kid_rotors:
			case kid_runningframes:
			case kid_sbarrellength:
			case kid_scorch:
			case kid_secondaryfireflh:
			case kid_secondaryfirepixeloffset:
			case kid_sequence:
			case kid_shadowindex:
			case kid_shouldfogremove:
			case kid_shouldusecelldrawer:
			case kid_silodamage:
			case kid_simpledamage:
			case kid_spawncount:
			case kid_spawns:
			case kid_specialanim:
			case kid_specialanimdamaged:
			case kid_specialanimthree:
			case kid_specialanimthreezadjust:
			case kid_specialanimtwo:
			case kid_specialanimtwozadjust:
			case kid_specialanimzadjust:
			case kid_specialzoverlay:
			case kid_start:
			case kid_sticky:
			case kid_surface:
			case kid_terrainpalette:
			case kid_theater:
			case kid_tiberiumchainreaction:
			case kid_tiberiumspawntype:
			case kid_tiberiumspreadradius:
			case kid_tiled:
			case kid_tooverlay:
			case kid_trailer:
			case kid_traileranim:
			case kid_trailerseperation:
			case kid_translucency:
			case kid_translucencydetaillevel:
			case kid_translucent:
			case kid_tumble:
			case kid_turretnotexportedonground:
			case kid_turretoffset:
			case kid_underdooranim:
			case kid_up:
			case kid_usenormallight:
			case kid_useturretshadow:
			case kid_visibleload:
			case kid_voxel:
			case kid_walk:
			case kid_walkframes:
			case kid_warhead:
			case kid_ydrawoffset:
			case kid_ysortadjust:
			case kid_zshapepointmove:
				break;
			default:
				return 1;
			}
		}
		else
			(*m_current_entry)[name]=value;
		break;
	}
	return 0;
}

bool Cart_ts_ini_reader::is_valid() const
{
	return true;
}
