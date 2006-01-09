// art_ts_ini_reader.h: interface for the Cart_ts_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ART_TS_INI_READER_H__82105441_7D9E_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_ART_TS_INI_READER_H__82105441_7D9E_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <set>
#include <string>
#include "ini_reader.h"

using namespace std;

class Cart_ts_ini_reader: public Cini_reader
{
public:
	typedef map<string, string> t_key_list;
	typedef map<string, t_key_list> t_art_list;
	typedef set<string> t_movie_list;

	Cart_ts_ini_reader();
	void erase();
	int process_section_start(const string& line);
	bool process_section() const;
	int process_key(const string& name, const string& value);
	bool is_valid() const;

	const t_art_list& get_art_list() const
	{
		return m_art_list;
	}

	const t_movie_list& get_movie_list() const
	{
		return m_movie_list;
	}
private:
	enum t_section_id {sei_movies, sei_unknown};

	enum t_key_id
	{
		kid_activeanim,
		kid_activeanimdamaged,
		kid_activeanimfour,
		kid_activeanimfourdamaged,
		kid_activeanimfourzadjust,
		kid_activeanimpowered,
		kid_activeanimthree,
		kid_activeanimthreedamaged,
		kid_activeanimthreepowered,
		kid_activeanimthreepoweredlight,
		kid_activeanimthreex,
		kid_activeanimthreey,
		kid_activeanimthreeysort,
		kid_activeanimthreezadjust,
		kid_activeanimtwo,
		kid_activeanimtwodamaged,
		kid_activeanimtwopowered,
		kid_activeanimtwopoweredlight,
		kid_activeanimtwox,
		kid_activeanimtwoy,
		kid_activeanimtwoysort,
		kid_activeanimtwozadjust,
		kid_activeanimx,
		kid_activeanimy,
		kid_activeanimysort,
		kid_activeanimzadjust,
		kid_altimage,
		kid_altpalette,
		kid_angle,
		kid_animactive,
		kid_animhigh,
		kid_animlow,
		kid_animpalette,
		kid_animrate,
		kid_auxanim,
		kid_barrellength,
		kid_barreloffset,
		kid_bibshape,
		kid_bouncer,
		kid_buildup,
		kid_cameo,
		kid_chargeanim,
		kid_crater,
		kid_crawl,
		kid_crawls,
		kid_customrotor,
		kid_damage,
		kid_damageddoor,
		kid_damagelevels,
		kid_damageradius,
		kid_demandload,
		kid_demandloadbuildup,
		kid_deployinganim,
		kid_detaillevel,
		kid_die1,
		kid_die2,
		kid_die3,
		kid_die4,
		kid_die5,
		kid_dooranim,
		kid_doorstages,
		kid_down,
		kid_elasticity,
		kid_end,
		kid_expireanim,
		kid_extradamagestage,
		kid_extralight,
		kid_fireangle,
		kid_firefly,
		kid_fireprone,
		kid_fireup,
		kid_firingframes,
		kid_flamer,
		kid_flat,
		kid_fly,
		kid_foundation,
		kid_frames,
		kid_freebuildup,
		kid_gatestages,
		kid_guard,
		kid_height,
		kid_hover,
		kid_idle1,
		kid_idle2,
		kid_image,
		kid_isanimatedtiberium,
		kid_isflamingguy,
		kid_ismeteor,
		kid_istiberium,
		kid_isveins,
		kid_loopcount,
		kid_loopend,
		kid_loopstart,
		kid_maxxyvel,
		kid_midpoint,
		kid_minzvel,
		kid_newtheater,
		kid_next,
		kid_normalized,
		kid_normalzadjust,
		kid_pbarrellength,
		kid_pbarrelthickness,
		kid_pingpong,
		kid_powerup1anim,
		kid_powerup1animdamaged,
		kid_powerup1locx,
		kid_powerup1locxx,
		kid_powerup1locy,
		kid_powerup1locyy,
		kid_powerup1locz,
		kid_powerup1loczz,
		kid_powerup1ysort,
		kid_powerup2anim,
		kid_powerup2animdamaged,
		kid_powerup2locx,
		kid_powerup2locxx,
		kid_powerup2locy,
		kid_powerup2locyy,
		kid_powerup2locz,
		kid_powerup2loczz,
		kid_powerup2ysort,
		kid_powerup3anim,
		kid_powerup3animdamaged,
		kid_powerup3locx,
		kid_powerup3locy,
		kid_powerup3locz,
		kid_powerup3ysort,
		kid_preproductionanim,
		kid_preproductionanimzadjust,
		kid_primaryfireflh,
		kid_primaryfirepixeloffset,
		kid_productionanim,
		kid_productionanimdamaged,
		kid_productionanimx,
		kid_productionanimy,
		kid_productionanimysort,
		kid_productionanimzadjust,
		kid_prone,
		kid_randomloopdelay,
		kid_randomrate,
		kid_rate,
		kid_ready,
		kid_recoilless,
		kid_remapable,
		kid_report,
		kid_reverse,
		kid_rotates,
		kid_rotcount,
		kid_rotors,
		kid_runningframes,
		kid_sbarrellength,
		kid_scorch,
		kid_secondaryfireflh,
		kid_secondaryfirepixeloffset,
		kid_sequence,
		kid_shadowindex,
		kid_shouldfogremove,
		kid_shouldusecelldrawer,
		kid_silodamage,
		kid_simpledamage,
		kid_spawncount,
		kid_spawns,
		kid_specialanim,
		kid_specialanimdamaged,
		kid_specialanimthree,
		kid_specialanimthreezadjust,
		kid_specialanimtwo,
		kid_specialanimtwozadjust,
		kid_specialanimzadjust,
		kid_specialzoverlay,
		kid_start,
		kid_sticky,
		kid_surface,
		kid_terrainpalette,
		kid_theater,
		kid_tiberiumchainreaction,
		kid_tiberiumspawntype,
		kid_tiberiumspreadradius,
		kid_tiled,
		kid_tooverlay,
		kid_trailer,
		kid_traileranim,
		kid_trailerseperation,
		kid_translucency,
		kid_translucencydetaillevel,
		kid_translucent,
		kid_tumble,
		kid_turretnotexportedonground,
		kid_turretoffset,
		kid_underdooranim,
		kid_up,
		kid_usenormallight,
		kid_useturretshadow,
		kid_visibleload,
		kid_voxel,
		kid_walk,
		kid_walkframes,
		kid_warhead,
		kid_ydrawoffset,
		kid_ysortadjust,
		kid_zshapepointmove,
		kid_unknown
	};

	t_key_list* m_current_entry;
	t_art_list m_art_list;
	t_movie_list m_movie_list;
	t_section_id m_section;
};

#endif // !defined(AFX_ART_TS_INI_READER_H__82105441_7D9E_11D4_B606_0000B4936994__INCLUDED_)