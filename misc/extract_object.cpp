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

#include "stdafx.h"
#include "extract_object.h"

#include <boost/algorithm/string.hpp>
#include <fstream>
#include "aud_file.h"
#include "file31.h"
#include "fname.h"
#include "html.h"
#include "mix_file_write.h"
#include "mix_sfl.h"
#include "shp_ts_file.h"
#include "string_conversion.h"
#include "web_tools.h"
#include "xcc_dirs.h"

using namespace boost;

Cextract_object::Cextract_object()
{
}

Cextract_object::~Cextract_object()
{
	close_all();
}

void Cextract_object::open_default(t_game game) 
{
	m_game = game;
	if (game == game_ts)
		add_mix(xcc_dirs::get_dir(game) + "patch.mix");
	else
	{
		add_mix(xcc_dirs::get_dir(game) + "language.mix");
		m_xste.open(game);
	}
	for (int j = 0; j < 100; j++)
	{
		add_mix(xcc_dirs::get_dir(m_game) + "ecache" + nwzl(2, 99 - j) + ".mix");
		add_mix(xcc_dirs::get_dir(m_game) + "expand" + nwzl(2, 99 - j) + ".mix");
	}
	add_mix(xcc_dirs::get_main_mix(m_game));
	add_path(xcc_dirs::get_dir(m_game));
}

void Cextract_object::close_all()
{
	if (m_game != game_ts && m_xste.csf_f().is_open())
		m_xste.close();
	for (t_mix_list::iterator i = m_mix_list.begin(); i != m_mix_list.end(); i++)
		i->close();
	m_mix_list.clear();
}

int Cextract_object::add_mix(string name, Cmix_file* g)
{
	m_mix_list.push_back(Cmix_file());
	Cmix_file& f = *m_mix_list.rbegin();
	int error;
	if (g)
	{
		error = f.open(name, *g);
		if (!error)
		{
			f.close();
			error = f.open(xcc_dirs::get_dir(m_game) + name);
			if (error)
				error = f.open(name, *g);
		}
	}
	else
		error = f.open(name);
	if (!error)
	{
		for (int j = 0; j < 100; j++)
		{
			add_mix("e" + nwzl(2, 99 - j) + "sc01.mix", &f);
			add_mix("e" + nwzl(2, 99 - j) + "sc02.mix", &f);
			add_mix("ecache" + nwzl(2, 99 - j) + ".mix", &f);
		}
		add_mix("audio.mix", &f);
		add_mix("cameo.mix", &f);
		add_mix("conquer.mix", &f);
		add_mix("isosnow.mix", &f);
		add_mix("isotem.mix", &f);
		add_mix("isourb.mix", &f);
		add_mix("local.mix", &f);
		add_mix("snow.mix", &f);
		add_mix("sounds01.mix", &f);
		add_mix("sounds.mix", &f);
		add_mix("temperat.mix", &f);
		add_mix("urban.mix", &f);
	}
	for (t_mix_list::iterator i = m_mix_list.begin(); i != m_mix_list.end(); )
	{
		if (i->is_open())
			i++;
		else
			m_mix_list.erase(i++);
	}
	return error;
}

void Cextract_object::add_path(string name)
{
	m_path_list.push_back(name);
}

int Cextract_object::load()
{
	int error = load_art();
	if (!error)
		error = load_rules();
	if (!error)
		error = load_sound();
	return error;

}

int Cextract_object::load_art()
{
	Ccc_file f(true);
	int error = open(f, "art.ini");
	if (!error)
	{
		m_air.skip_errors(true);
		error = m_air.process(f.get_data(), f.get_size());
		f.close();
		if (!error)
		{
			error = open(f, "artfs.ini");
			if (!error)
			{
				error = m_air.process(f.get_data(), f.get_size());
				f.close();
			}
			else
				error = 0;
		}
	}
	return error;
}

int Cextract_object::load_rules()
{
	Ccc_file f(true);
	int error = open(f, "rules.ini");
	if (!error)
	{
		m_rir.skip_errors(true);
		error = m_rir.process(f.get_data(), f.get_size());
		f.close();
		if (!error)
		{
			error = open(f, "firestrm.ini");
			if (!error)
			{
				error = m_rir.process(f.get_data(), f.get_size());
				f.close();
			}
			else
				error = 0;
		}
	}
	return error;
}

int Cextract_object::load_sound()
{
	Ccc_file f(true);
	int error = open(f, "sound.ini");
	if (!error)
	{
		error = m_sir.process(f.get_data(), f.get_size());
		f.close();
		if (!error)
		{
			error = open(f, "sound01.ini");
			if (!error)
			{
				error = m_sir.process(f.get_data(), f.get_size());
				f.close();
			}
			else
				error = 0;
		}
	}
	return error;
}

enum 
{
	ki_files,
	ki_keys,
	vi_name,
	vi_value,
	vi_mail,
	vi_link_title,
	vi_link,
	vi_game
};

typedef map<string, string> t_key_list;

static void store_key_list(const t_key_list& kl, Cxif_key& k)
{
	int j = 0;
	for (t_key_list::const_iterator i = kl.begin(); i != kl.end(); i++)
	{
		Cxif_key& l = k.open_key_write(j++);
		l.set_value_string(vi_name, i->first);
		l.set_value_string(vi_value, i->second);
	}
}

int Cextract_object::open(Ccc_file& f, string name)
{
	for (t_path_list::iterator i = m_path_list.begin(); i != m_path_list.end(); i++)
	{
		if (!f.open(*i + name))
			return 0;
	}
	for (t_mix_list::iterator j = m_mix_list.begin(); j != m_mix_list.end(); j++)
	{
		if (!f.open(name, *j))
			return 0;
	}
	return 1;
}

void Cextract_object::store_file(string name, Cxif_key& k, int& n)
{
	if (mix_sfl::contains(m_game, Cmix_file::get_id(m_game, name)))
	{
		Cxif_key& l = k.open_key_edit(ki_files).open_key_write(n++);
		l.set_value_string(vi_name, to_lower_copy(name));
		return;
	}
	Ccc_file f(true);
	if (!open(f, name))
	{
		Cxif_key& l = k.open_key_edit(ki_files).open_key_write(n++);
		l.set_value_string(vi_name, to_lower_copy(name));
		l.set_value_binary(vi_value, f.get_vdata());
		f.close();
	}
	if (name.length() >= 2 && tolower(name[1]) == 'a')
	{
		name[1] = 't';
		store_file(name, k, n);
		name[1] = 'u';
		store_file(name, k, n);
	}
}

void Cextract_object::store_file(const t_key_list& kl, string name, string fext, Cxif_key& k, int& n)
{
	t_key_list::const_iterator i = kl.find(name);
	if (i != kl.end())
		store_file(i->second + fext, k, n);
}

const Cextract_object::t_object_type_list& Cextract_object::get_object_type_list(t_object_type ot) const
{
	switch (ot)
	{
	case ot_animation:
	case ot_art:
	case ot_infantry_sequence:
		return m_air.get_art_list();
	case ot_aircraft:
	case ot_building:
	case ot_infantry:
	case ot_particle:
	case ot_particle_system:
	case ot_projectile:
	case ot_vehicle:
	case ot_warhead:
	case ot_weapon:
		return m_rir.get_rules_list();
	}
	assert(false);
	return m_rir.get_rules_list();
}

void Cextract_object::add_one(string name, t_object_type ot)
{
	if (ot == ot_animation || ot == ot_art || ot == ot_infantry_sequence)
	{
		if (m_art_list.find(name) != m_art_list.end())
			return;
	}
	else
	{
		if (m_object_list.find(name) != m_object_list.end())
			return;
	}
	switch (ot)
	{
	case ot_aircraft:
	case ot_animation:
	case ot_art:
	case ot_building:
	case ot_infantry:
	case ot_infantry_sequence:
	case ot_particle:
	case ot_particle_system:
	case ot_projectile:
	case ot_vehicle:
	case ot_warhead:
	case ot_weapon:
		{
			const t_object_type_list& tl = get_object_type_list(ot);
			if (tl.find(name) == tl.end())
			{
				if (tl.find(to_upper_copy(name)) != tl.end())
				{
					add_one(to_upper_copy(name), ot);
					return;
				}
				if (ot != ot_animation)
					return;
			}
			if (ot == ot_animation || ot == ot_art || ot == ot_infantry_sequence)
				m_art_list[name] = ot;
			else
				m_object_list[name] = ot;
			if (tl.find(name) == tl.end())
				return;
			const t_key_list& kl = tl.find(name)->second;
			switch (ot)
			{
			case ot_aircraft:
			case ot_building:
			case ot_infantry:
			case ot_vehicle:
				{
					add(kl, "AuxSound1", ot_sound);
					add(kl, "AuxSound2", ot_sound);
					add(kl, "CrashingSound", ot_sound);
					add(kl, "CrushSound", ot_sound);					
					add(kl, "DebrisAnim", ot_animation);
					add(kl, "DeploySound", ot_sound);
					add(kl, "DestroyAnim", ot_animation);
					add(kl, "DieSound", ot_sound);
					add(kl, "Elite", ot_weapon);
					add(kl, "ElitePrimary", ot_weapon);
					add(kl, "EliteSecondary", ot_weapon);
					add(kl, "ImpactLandSound", ot_sound);
					add(kl, "MoveSound", ot_sound);
					add(kl, "Primary", ot_weapon);
					add(kl, "Secondary", ot_weapon);
					add(kl, "SinkingSound", ot_sound);
					add(kl, "VoiceAttack", ot_sound);
					add(kl, "VoiceComment", ot_sound);
					add(kl, "VoiceDie", ot_sound);
					add(kl, "VoiceFeedback", ot_sound);
					add(kl, "VoiceMove", ot_sound);
					add(kl, "VoiceSelect", ot_sound);
					add(kl, "VoiceSpecialAttack", ot_sound);
					add(kl, "UIName", ot_st_entry);
					t_key_list::const_iterator image = kl.find("Image");
					add(image == kl.end() ? name : image->second, ot_art);
					t_key_list::const_iterator explosion = kl.find("Explosion");
					if (explosion != kl.end())
						add(explosion->second, ot_animation);
					t_key_list::const_iterator damageparticlesystems = kl.find("DamageParticleSystems");
					if (damageparticlesystems != kl.end())
						add(damageparticlesystems->second, ot_particle_system);
					t_key_list::const_iterator deploysinto = kl.find("DeploysInto");
					if (deploysinto != kl.end())
						add(deploysinto->second, ot_building);
					t_key_list::const_iterator undeploysinto = kl.find("UndeploysInto");
					if (undeploysinto != kl.end())
						add(undeploysinto->second, ot_vehicle);
					break;
				}
			case ot_animation:
				{
					t_key_list::const_iterator report = kl.find("Report");
					if (report != kl.end())
						add(report->second, ot_sound);
					break;
				}
			case ot_art:
				{
					for (t_key_list::const_iterator i = kl.begin(); i != kl.end(); i++)
					{
						if (i->first == "ActiveAnim" ||
							i->first == "ActiveAnimDamaged" ||
							i->first == "ActiveAnimTwo" ||
							i->first == "ActiveAnimTwoDamaged" ||
							i->first == "ActiveAnimThree" ||
							i->first == "ActiveAnimThreeDamaged" ||
							i->first == "ActiveAnimFour" ||
							i->first == "ActiveAnimFourDamaged" ||
							i->first == "BibShape" ||							
							i->first == "Buildup" ||
							i->first == "DeployingAnim" ||							
							i->first == "PowerUp1Anim" ||
							i->first == "PowerUp1AnimDamaged" ||
							i->first == "PowerUp2Anim" ||
							i->first == "PowerUp2AnimDamaged" ||
							i->first == "PowerUp3Anim" ||
							i->first == "PowerUp3AnimDamaged" ||
							i->first == "UnderDoorAnim" ||
							i->first == "Trailer")
							add(i->second, ot_animation);
						else if (i->first == "Sequence")
							add(i->second, ot_infantry_sequence);
					}
					break;
				}
			case ot_particle:
				{
					t_key_list::const_iterator image = kl.find("Image");
					if (image != kl.end())
						add(image->second, ot_animation);
					break;
				}
			case ot_particle_system:
				{
					t_key_list::const_iterator holdswhat = kl.find("HoldsWhat");
					if (holdswhat != kl.end())
						add(holdswhat->second, ot_particle);
					break;
				}
			case ot_projectile:
				{
					t_key_list::const_iterator image = kl.find("Image");
					add(image == kl.end() ? name : image->second, ot_art);
					break;
				}
			case ot_warhead:
				{
					t_key_list::const_iterator animlist = kl.find("AnimList");
					if (animlist != kl.end())
						add(animlist->second, ot_animation);
					t_key_list::const_iterator particle = kl.find("Particle");
					if (particle != kl.end())
						add(particle->second, ot_particle_system);
					break;
				}
			case ot_weapon:
				{
					t_key_list::const_iterator anim = kl.find("Anim");
					if (anim != kl.end())
						add(anim->second, ot_animation);
					t_key_list::const_iterator attachedparticlesystem = kl.find("AttachedParticleSystem");
					if (attachedparticlesystem != kl.end())
						add(attachedparticlesystem->second, ot_particle_system);
					t_key_list::const_iterator projectile = kl.find("Projectile");
					if (projectile != kl.end())
						add(projectile->second, ot_projectile);
					t_key_list::const_iterator report = kl.find("Report");
					if (report != kl.end())
						add(report->second, ot_sound);
					t_key_list::const_iterator warhead = kl.find("Warhead");
					if (warhead != kl.end())
						add(warhead->second, ot_warhead);
					break;
				}
			}
			break;
		}
	case ot_sound:
	case ot_st_entry:
		m_object_list[name] = ot;
		break;
	}
}

void Cextract_object::add(Cmulti_line l, t_object_type ot)
{
	while (!l.empty())
		add_one(l.get_next_line(','), ot);
}

void Cextract_object::add(const t_key_list& kl, string s, t_object_type ot)
{
	t_key_list::const_iterator i = kl.find(s);
	if (i != kl.end())
		add(i->second, ot);
}

Cxif_key Cextract_object::extract(string name)
{
	int error = 0;
	Cxif_key k;
	if (m_rir.get_aircraft_type_list().find(name) != m_rir.get_aircraft_type_list().end())
		add(name, ot_aircraft);
	else if (m_rir.get_building_type_list().find(name) != m_rir.get_building_type_list().end())
		add(name, ot_building);
	else if (m_rir.get_infantry_type_list().find(name) != m_rir.get_infantry_type_list().end())
		add(name, ot_infantry);
	else if (m_rir.get_vehicle_type_list().find(name) != m_rir.get_vehicle_type_list().end())
		add(name, ot_vehicle);
	if (0)
	{
		t_object_type_list::const_iterator i;
		for (i = m_rir.get_aircraft_type_list().begin(); i != m_rir.get_aircraft_type_list().end(); i++)
			add(i->first, ot_aircraft);
		for (i = m_rir.get_building_type_list().begin(); i != m_rir.get_building_type_list().end(); i++)
			add(i->first, ot_building);
		for (i = m_rir.get_infantry_type_list().begin(); i != m_rir.get_infantry_type_list().end(); i++)
			add(i->first, ot_infantry);
		for (i = m_rir.get_vehicle_type_list().begin(); i != m_rir.get_vehicle_type_list().end(); i++)
			add(i->first, ot_vehicle);
	}
	int j = 0;
	for (t_object_list::iterator i = m_object_list.begin(); i != m_object_list.end(); i++)
	{		
		Cxif_key& l = k.open_key_edit(i->second);
		Cxif_key& m = l.open_key_write(j++);
		int z = 0;
		m.set_value_string(vi_name, i->first);
		switch (i->second)
		{
		case ot_aircraft:
		case ot_building:
		case ot_infantry:
		case ot_particle:
		case ot_particle_system:
		case ot_projectile:
		case ot_vehicle:
		case ot_warhead:
		case ot_weapon:
			store_key_list(get_object_type_list(i->second).find(i->first)->second, m.open_key_write(ki_keys));
			break;
		case ot_sound:
			store_file(i->first + ".aud", m, z);
			store_file(i->first + ".wav", m, z);
			break;
		case ot_st_entry:
			{
				const Ccsf_file& csf_f = m_xste.csf_f();
				if (csf_f.has_name(i->first))
				{
					Cxif_key& k = m.open_key_write(ki_keys);
					Cxif_key& l = k.open_key_write(j++);
					l.set_value_string(vi_name, csf_f.get_converted_value(i->first));
					l.set_value_string(vi_value, csf_f.get_extra_value(i->first));
				}
				break;
			}
		}
	}
	m_object_list.clear();
	store_art_list(k);
	k.set_value_int(vi_game, m_game);
	return k;
}

Cextract_object::t_credits Cextract_object::get_credits(const Cxif_key& k)
{
	t_credits r;
	const Cxif_key& l = k.open_key_read(ot_credits);
	r.name = l.get_value_string(vi_name);
	r.mail = l.get_value_string(vi_mail);
	r.link_title = l.get_value_string(vi_link_title);
	r.link = l.get_value_string(vi_link);
	return r;
}

void Cextract_object::set_credits(Cxif_key& k, t_credits credits)
{
	Cxif_key& l = k.open_key_edit(ot_credits);
	l.set_value_string(vi_name, credits.name);
	l.set_value_string(vi_mail, credits.mail);
	l.set_value_string(vi_link_title, credits.link_title);
	l.set_value_string(vi_link, credits.link);
}

t_game Cextract_object::get_game(Cxif_key& k) const
{
	return static_cast<t_game>(k.get_value_int(vi_game));
}

void Cextract_object::store_art_list(Cxif_key& k)
{
	int z = 0;
	for (t_art_list::iterator i = m_art_list.begin(); i != m_art_list.end(); i++)
	{
		Cxif_key& l = k.open_key_edit(i->second);
		Cxif_key& m = l.open_key_write(z++);
		m.set_value_string(vi_name, i->first);
		int z = 0;
		if (i->second == ot_art)
		{
			store_file(i->first + ".hva", m, z);
			store_file(i->first + ".vxl", m, z);
			if (i->first.length() > 4)
			{
				store_file(i->first + "bar.hva", m, z);
				store_file(i->first + "bar.vxl", m, z);
			}
			else
			{
				store_file(i->first + "barl.hva", m, z);
				store_file(i->first + "barl.vxl", m, z);
			}
			store_file(i->first + "tur.hva", m, z);
			store_file(i->first + "tur.vxl", m, z);
		}
		t_object_type_list::const_iterator j = m_air.get_art_list().find(i->first);
		if (j == m_air.get_art_list().end())
		{
			store_file(i->first + ".shp", m, z);
			continue;
		}
		t_key_list::const_iterator image = j->second.find("Image");
		store_file((image == j->second.end() ? i->first : image->second) + ".shp", m, z);
		store_key_list(j->second, m.open_key_write(ki_keys));
		if (i->second == ot_art)
		{
			store_file(j->second, "AltCameo", ".shp", m, z);
			store_file(j->second, "Cameo", ".shp", m, z);
		}
	}
	m_art_list.clear();
}

static string report_file_list(const Cxif_key& k, const string& files_url)
{
	if (!k.m_keys.size())
		return "&nbsp;";
	string r;
	for (t_xif_key_map::const_iterator i = k.m_keys.begin(); i != k.m_keys.end(); i++)
	{
		Cfname name = i->second.get_value_string(vi_name);
		string d = name; // .get_all();
		int cb_f = i->second.exists_value(vi_value) ? i->second.get_value(vi_value).get_size() : -1;
		if (cb_f < 0)
			d += " (standard)";
		else
			d += " (" + n(cb_f) + " bytes)";
		if (name.get_fext() == ".aud")
		{
			name.set_ext(".wav");
			d += " " + a("play", "href=\"" + files_url + name.get_all() + "\"");
		}
		else if (name.get_fext() == ".shp" && cb_f == 3104)
		{
			Cshp_ts_file f;
			f.load(i->second.get_value(vi_value).get_vdata(), cb_f);
			if (f.get_cx() == 64 && f.get_cx() == 48 && f.get_c_images() == 1)
			{
				name.set_ext(".png");
				d += " " + a("view", "href=\"" + files_url + name.get_all() + "\"");
			}
		}
		r += d + "<br>";
	}
	return r;
}

static string report_key_list(const Cxif_key& k)
{
	if (!k.m_keys.size())
		return "&nbsp;";
	string r;
	for (t_xif_key_map::const_iterator i = k.m_keys.begin(); i != k.m_keys.end(); i++)
		r += i->second.get_value_string(vi_name) + "=" + i->second.get_value_string(vi_value) + "<br>";
	return r;
}

Cextract_object::t_object_type Cextract_object::get_object_type(const Cxif_key& k) const
{
	if (k.exists_key(ot_aircraft))
		return ot_aircraft;
	else if (k.exists_key(ot_infantry))
		return ot_infantry;
	else if (k.exists_key(ot_vehicle))
		return ot_vehicle;
	else if (k.exists_key(ot_building))
		return ot_building;
	else
		return ot_unknown;
}

string Cextract_object::get_object_name(const Cxif_key& k)
{
	const Cxif_key* l = NULL;
	if (k.exists_key(ot_aircraft))
		l = &k.open_key_read(ot_aircraft);
	else if (k.exists_key(ot_infantry))
		l = &k.open_key_read(ot_infantry);
	else if (k.exists_key(ot_vehicle))
		l = &k.open_key_read(ot_vehicle);
	else if (k.exists_key(ot_building))
		l = &k.open_key_read(ot_building);
	if (l)
	{
		const Cxif_key& m = l->m_keys.begin()->second.open_key_read(ki_keys);
		for (t_xif_key_map::const_iterator i = m.m_keys.begin(); i != m.m_keys.end(); i++)
		{
			if (i->second.get_value_string(vi_name) == "Name")
				return i->second.get_value_string(vi_value);
		}
	}
	return "Unknown";

}

const char* ot_name[] = {"Aircraft", "Animation", "Art", "Building", "Credits", "Infantry", "Infantry sequence", "Particle", "Particle system", "Projectile", "Sound", "Vehicle", "Voxel animation", "Warhead", "Weapon", "ST entry", "Unknown"};

int Cextract_object::report(const Cxif_key& k, char* d, const string& files_url)
{
	string page;
	if (k.exists_key(ot_credits))
	{
		const Cxif_key& credits_key = k.open_key_read(ot_credits);
		string line = web_name(credits_key.get_value_string(vi_name), credits_key.get_value_string(vi_mail));
		string link = credits_key.get_value_string(vi_link);
		if (web_is_link(link))
		{
			if (!line.empty())
				line += ", ";
			line += web_link(credits_key.get_value_string(vi_link_title), link);
		}
		if (!line.empty())
		{
			page +=
				"<tr><th colspan=3>" + static_cast<string>(ot_name[ot_credits]) +
				"<tr><td colspan=3>" + get_object_name(k) + " created by " + line;
		}
	}
	for (t_xif_key_map::const_iterator i = k.m_keys.begin(); i != k.m_keys.end(); i++)
	{
		if (i->first == ot_credits)
			continue;
		const Cxif_key& l = i->second;
		page += "<tr><th colspan=3>" + static_cast<string>(ot_name[i->first]);
		for (t_xif_key_map::const_iterator j = l.m_keys.begin(); j != l.m_keys.end(); j++)
		{
			const Cxif_key& m = j->second;
			string r;
			if (m.exists_key(ki_keys))
				r += "<td>" + report_key_list(m.open_key_read(ki_keys));
			else
				r += "<td>&nbsp;";
			if (m.exists_key(ki_files))
				r += "<td>" + report_file_list(m.open_key_read(ki_files), files_url);
			else
				r += "<td>&nbsp;";
			page += "<tr><td>" + m.get_value_string(vi_name) + r;
		}
	}
	strcpy(d, ("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"><link rel=stylesheet href=\"http://xccu.sourceforge.net/xcc.css\"><title>" + get_object_name(k) + "</title><table border=1 width=\"100%\">" + page + "</table>").c_str());
	return strlen(d);
}

static void add_type(Cneat_ini_reader& ir, string section_name, string type_name)
{
	ir.process_section_start(section_name);
	Cneat_key_list& kl = ir.current_section();
	Cneat_key_list::t_key_map km = kl.get_key_map();
	int slot = 1;
	for (Cneat_key_list::t_key_map::const_iterator i = km.begin(); i != km.end(); i++)
	{
		if (i->second == type_name)
			return;
		slot = max(slot, atoi(i->first.c_str()) + 1);
	}
	kl.add_key(n(slot), type_name);
}

int Cextract_object::read_ini(const string& name, Cneat_ini_reader& ir)
{
	Ccc_file f(true);
	int error = open(f, name);
	if (!error)
	{
		error = ir.process(f.get_data(), f.get_size());
		f.close();
	}
	return error;
}

int Cextract_object::insert(const Cxif_key& k)
{
	Cneat_ini_reader air, rir, sir;
	int error = read_ini("art.ini", air);
	if (!error)
		error = read_ini("rules.ini", rir);
	if (!error)
		error = read_ini("sound.ini", sir);
	if (!error)
	{
		Cmix_file_write expand_mix(m_game);
		Cmix_file_write ecache_mix(m_game);
		t_xif_key_map::const_iterator ki;
		for (ki = k.m_keys.begin(); ki != k.m_keys.end(); ki++)
		{
			t_object_type ot = static_cast<t_object_type>(ki->first);
			const Cxif_key& l = ki->second;
			for (t_xif_key_map::const_iterator li = l.m_keys.begin(); li != l.m_keys.end(); li++)
			{
				const Cxif_key& m = li->second;
				string name = m.get_value_string(vi_name);
				switch (ot)
				{
				case ot_aircraft:
					add_type(rir, "AircraftTypes", name);
					break;
				case ot_building:
					add_type(rir, "BuildingTypes", name);
					break;
				case ot_infantry:
					add_type(rir, "InfantryTypes", name);
					break;
				case ot_particle:
					add_type(rir, "Particles", name);
					break;
				case ot_particle_system:
					add_type(rir, "ParticleSystems", name);
					break;
				case ot_sound:
					add_type(sir, "SoundList", name);
					break;
				case ot_vehicle:
					add_type(rir, "VehicleTypes", name);
					break;
				case ot_voxel_animation:
					add_type(rir, "VoxelAnims", name);
					break;
				case ot_warhead:
					add_type(rir, "Warheads", name);
					break;
				}
			}
		}
		for (ki = k.m_keys.begin(); ki != k.m_keys.end(); ki++)
		{
			t_object_type ot = static_cast<t_object_type>(ki->first);
			const Cxif_key& l = ki->second;
			for (t_xif_key_map::const_iterator li = l.m_keys.begin(); li != l.m_keys.end(); li++)
			{
				const Cxif_key& m = li->second;
				if (m.exists_key(ki_files))
				{
					const Cxif_key& n = m.open_key_read(ki_files);
					for (t_xif_key_map::const_iterator ni = n.m_keys.begin(); ni != n.m_keys.end(); ni++)
					{
						if (error)
							break;
						const Cxif_key& o = ni->second;
						if (o.exists_value(vi_name) && o.exists_value(vi_value))
						{
							Cfname fname = o.get_value_string(vi_name);
							const Cxif_value& f = o.open_value_read(vi_value);
							if (fname.get_fext() == ".aud")
								ecache_mix.add_file(fname, Cvirtual_binary(f.get_data(), f.get_size()));
							else if (fname.get_fext() == ".shp")
								ecache_mix.add_file(fname, Cvirtual_binary(f.get_data(), f.get_size()));
							else
								expand_mix.add_file(fname, Cvirtual_binary(f.get_data(), f.get_size()));
						}
					}
					
				}
				if (m.exists_key(ki_keys))
				{
					const Cxif_key& n = m.open_key_read(ki_keys);
					for (t_xif_key_map::const_iterator ni = n.m_keys.begin(); ni != n.m_keys.end(); ni++)
					{
						const Cxif_key& o = ni->second;
						string name = m.get_value_string(vi_name);
						switch (ot)
						{
						case ot_aircraft:
						case ot_building: 
						case ot_infantry: 
						case ot_particle: 
						case ot_particle_system: 
						case ot_projectile: 
						case ot_vehicle: 
						case ot_voxel_animation: 
						case ot_warhead: 
						case ot_weapon:
							rir.process_section_start(name);
							rir.process_key(o.get_value_string(vi_name), o.get_value_string(vi_value));
							break;
						case ot_animation: 
						case ot_art: 
						case ot_infantry_sequence: 
							air.process_section_start(name);
							air.process_key(o.get_value_string(vi_name), o.get_value_string(vi_value));
							break;
						case ot_sound: 
							sir.process_section_start(name);
							break;
						}
					}								
				}
			}
		}
		if (!error)
			error = air.write(xcc_dirs::get_dir(m_game) + "art.ini");
		if (!error)
			error = rir.write(xcc_dirs::get_dir(m_game) + "rules.ini");
		if (!error)
			error = sir.write(xcc_dirs::get_dir(m_game) + "sound.ini");
		if (!error)
		{
			expand_mix.add_file("ecache99.mix", ecache_mix.write());
			if (!error)
			{
				close_all();
				error = expand_mix.write().save(xcc_dirs::get_dir(m_game) + "expand99.mix");
			}
		}
	}
	return error;
}

static void extract_files(const Cxif_key& k, Cfile31& out_f)
{
	for (t_xif_key_map::const_iterator i = k.m_keys.begin(); i != k.m_keys.end(); i++)
	{
		if (!i->second.exists_value(vi_value))
			continue;
		Cfname name = i->second.get_value_string(vi_name);
		int cb_f = i->second.get_value(vi_value).get_size();
		if (name.get_fext() == ".aud")
		{
			Caud_file f;
			f.load(i->second.get_value(vi_value).get_vdata(), cb_f);
			name.set_ext(".wav");
			name.set_path("c:/temp/");
			f.extract_as_wav(name);
			Ccc_file g(true);
			if (!g.open(name))
			{
				out_f.write_str(name.get_fname());
				out_f.write_bin(g.get_data(), cb_f);
				g.close();
			}
		}
		else if (name.get_fext() == ".shp")
		{
			/*
			Cshp_ts_file f;
			f.load(i->second.get_value(vi_value).get_data(), cb_f);
			name.set_ext(".png");
			*/
		}
	}
}

int Cextract_object::prepare_for_web(Cfname fname, byte* d)
{
	byte* w = d;
	Ccc_file f(true);
	int error = f.open(fname);
	if (!error)
	{
		Cxif_key k;
		error = k.load_key(f.get_data(), f.get_size());
		if (!error)
		{
			char* report = new char[64 << 10];
			Cextract_object::report(k, report, "objects/files/");
			fname.set_ext(".xot");
			Cfile31 out_f;
			out_f.open_write(fname);
			out_f.write_int(0);
			out_f.write_int(Cextract_object::get_game(k));
			t_credits credits = Cextract_object::get_credits(k);
			out_f.write_str(credits.name);
			out_f.write_str(credits.mail);
			out_f.write_str(credits.link_title);
			out_f.write_str(credits.link);
			out_f.write_str(fname.get_ftitle());
			out_f.write_int(get_object_type(k));
			out_f.write_bin(f.get_data(), f.get_size());
			out_f.write_str(report);
			for (t_xif_key_map::const_iterator i = k.m_keys.begin(); i != k.m_keys.end(); i++)
			{
				if (i->first == ot_credits)
					continue;
				const Cxif_key& l = i->second;
				for (t_xif_key_map::const_iterator j = l.m_keys.begin(); j != l.m_keys.end(); j++)
				{
					const Cxif_key& m = j->second;
					if (m.exists_key(ki_files))
						extract_files(m.open_key_read(ki_files), out_f);
				}
			}
			out_f.close();
			delete[] report;
		}
		else
			return 0;		
		f.close();
	}
	else
		return 0;
	return w - d;
}