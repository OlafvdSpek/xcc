#include "stdafx.h"
#include "ucr_formats.h"

#include "ucr_container_ws_ra_mix.h"

Cucr_formats::Cucr_formats()
{
	add(Cucr_format::get_big_format());
	add(Cucr_format::get_td_mix_format());
	add(Cucr_format::get_enoid_res_format());
	add(Cucr_format::get_rg_mix_format());
	add(Cucr_format::get_conquest_wad_format());
	add(Cucr_format::get_lost_eden_dat_format());
	// add(Cucr_format("Westwood Studios - Command & Conquer: Red Alert - MIX", "mix;mmx", "hkey_local_machine\\software\\westwood\\red alert 2\\installpath", new_container<Cucr_container_ws_ra_mix>));
	// Cucr_format::t_new_container_f f = new_container<Cucr_container_ws_ra_mix>;
}

Cxif_key Cucr_formats::export() const
{
	Cxif_key key;
	for (t_list::const_iterator i = list().begin(); i != list().end(); i++)
		key.open_key_write() = i->export();
	return key;
}

void Cucr_formats::import(const Cxif_key& key)
{
	for (t_xif_key_map::const_iterator i = key.m_keys.begin(); i != key.m_keys.end(); i++)
		add(Cucr_format(i->second));
}

void Cucr_formats::add(const Cucr_format& v)
{
	m_list.push_back(v);
}
