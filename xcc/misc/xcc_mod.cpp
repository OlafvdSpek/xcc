// xcc_mod.cpp: implementation of the Cxcc_mod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xcc_mod.h"

#include <fstream>
#include <strstream>
#include "aud_file_write.h"
#include "csf_file.h"
#include "jpeg_file.h"
#include "html.h"
#include "mix_file.h"
#include "mix_file_write.h"
#include "neat_ini_reader.h"
#include "ogg_file.h"
#include "pcx_file.h"
#include "shp_ts_file.h"
#include "shp_ts_file_write.h"
#include "string_conversion.h"
#include "web_tools.h"
#include "xcc_dirs.h"
#include "xse.h"
#include "xste.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "cc_file.h"

const char* Cxcc_mod::ct_name[] = {"cameo", "hva", "ini", "map", "mix", "screen", "shp", "sound", "speech", "string table", "theme", "video", "vxl", "launcher", "manual", "interface", "unknown"};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cxcc_mod::Cxcc_mod()
{
	m_options.link = "http://";
	m_options.mod_name = "XCC Mod";
	m_options.game = game_ra2;
	m_options.csf_diff_compression = true;
	m_options.ini_diff_compression = true;
	m_options.custom_button_text = false;
	m_options.exit_button = true;
	m_options.manual_button = true;
	m_options.site_button = true;
	m_options.update_button = true;
	m_options.xhp_button = true;
	m_options.mod_version = "1.00";
	m_options.mod_ucf = "http://";
	m_options.confirm_deactivate = true;
}

Cxcc_mod::~Cxcc_mod()
{
}

Cxcc_mod::t_category_file_list Cxcc_mod::category_file_list(t_category_type category) const
{
	t_file_list::const_iterator i = m_file_list.find(category);
	return i != m_file_list.end() ? i->second : t_category_file_list();
}

void Cxcc_mod::clear()
{
	m_file_list.clear();
}

bool Cxcc_mod::contains(t_category_type category) const
{
	t_file_list::const_iterator i = m_file_list.find(category);
	return i != m_file_list.end() && i->second.size();
}

bool Cxcc_mod::contains(t_category_type category, string fname, bool strip_path) const
{
	if (strip_path)
	{
		t_file_list::const_iterator i = m_file_list.find(category);
		if (i != m_file_list.end())
		{
			for (t_category_file_list::const_iterator j = i->second.begin(); j != i->second.end(); j++)
			{
				if (Cfname(*j).get_fname() == fname)
					return true;
			}
		}
		return false;
	}
	else
	{
		t_file_list::const_iterator i = m_file_list.find(category);
		return i != m_file_list.end() && i->second.find(fname) != i->second.end();
	}
}

int Cxcc_mod::insert(t_category_type category, string fname)
{
	int error = 0;
	m_file_list[category].insert(fname);
	return error;
}

void Cxcc_mod::remove(t_category_type category, string fname)
{
	m_file_list[category].erase(fname);
}

static void delete_files(string fname)
{
	WIN32_FIND_DATA finddata;
	HANDLE findhandle = FindFirstFile(fname.c_str(), &finddata);
	if (findhandle != INVALID_HANDLE_VALUE)
	{
		do
		{
			delete_file(Cfname(fname).get_path() + finddata.cFileName);
		}
		while (FindNextFile(findhandle, &finddata));
		FindClose(findhandle);
	}
}

enum 
{
	vi_cx,
	vi_cy,
	vi_c_frames,
	vi_fname,
	vi_ft,
	vi_fdata,
	vi_encoding,
	vi_name,
	vi_mail,
	vi_link_title,
	vi_link,
	vi_game,
	vi_mod_name,
	vi_csf_diff_compression,
	vi_ini_diff_compression,
	vi_custom_button_text,
	vi_exit_button,
	vi_manual_button,
	vi_site_button,
	vi_update_button,
	vi_xhp_button,
	vi_mod_version,
	vi_mod_ucf,
	vi_confirm_deactivate
};

enum t_encoding
{
	enc_none,
	enc_diff,
	enc_jpeg,
	enc_mng,
	enc_mpeg,
	enc_ogg,
	enc_png
};

int Cxcc_mod::load(const Cxif_key& key, string dir)
{
	int error = 0;
	m_options.name = key.get_value_string(vi_name);
	m_options.mail = key.get_value_string(vi_mail);
	m_options.link_title = key.get_value_string(vi_link_title);
	m_options.link = key.get_value_string(vi_link);
	m_options.mod_name = key.get_value_string(vi_mod_name);
	m_options.game = static_cast<t_game>(key.get_value_int(vi_game));
	for (t_xif_value_map::const_iterator value = key.m_values.begin(); value != key.m_values.end(); value++)
	{
		switch (value->first)
		{
		case vi_csf_diff_compression:
			m_options.csf_diff_compression = value->second.get_int();
			break;
		case vi_ini_diff_compression:
			m_options.ini_diff_compression = value->second.get_int();
			break;
		case vi_custom_button_text:
			m_options.custom_button_text = value->second.get_int();
			break;
		case vi_exit_button:
			m_options.exit_button = value->second.get_int();
			break;
		case vi_manual_button:
			m_options.manual_button = value->second.get_int();
			break;
		case vi_site_button:
			m_options.site_button = value->second.get_int();
			break;
		case vi_update_button:
			m_options.update_button = value->second.get_int();
			break;
		case vi_xhp_button:
			m_options.xhp_button = value->second.get_int();
			break;
		case vi_mod_version:
			m_options.mod_version = value->second.get_string();
			break;
		case vi_mod_ucf:
			m_options.mod_ucf = value->second.get_string();
			break;
		case vi_confirm_deactivate:
			m_options.confirm_deactivate = value->second.get_int();
			break;
			/*
		case vi_@:
			m_options.@ = value->second.get_int();
			break;
			*/
		}
	}
	for (t_xif_key_map::const_iterator category = key.m_keys.begin(); category != key.m_keys.end(); category++)
	{
		t_category_file_list& list = m_file_list[static_cast<t_category_type>(category->first)];
		for (t_xif_key_map::const_iterator i = category->second.m_keys.begin(); i != category->second.m_keys.end(); i++)
		{
			if (error)
				break;
			if (dir.size() && i->second.exists_value(vi_fdata))
			{
				const Cxif_value& fdata = i->second.get_value(vi_fdata);
				Cfname fname = dir + ct_name[category->first] + '\\' + i->second.get_value_string(vi_fname);
				if (!fname.exists())
				{
					create_directory(dir);
					create_directory(fname.get_path());
					error = file32_write(fname, fdata.get_data(), fdata.get_size());
				}
				list.insert(fname);
			}
			else
				list.insert(i->second.get_value_string(vi_fname));
		}
	}
	return error;
}

Cxcc_mod::t_options Cxcc_mod::options() const
{
	return m_options;
}

void Cxcc_mod::options(t_options options)
{
	m_options = options;
}

Cxif_key Cxcc_mod::save(bool export) const
{
	Cxif_key key;
	Cmix_file language_mix, main_mix;
	Cmix_file local_mix;
	if (export)
	{
		const t_game game = m_options.game;
		const string dir = xcc_dirs::get_dir(game);
		language_mix.open(dir + "language.mix");
		if (!main_mix.open(xcc_dirs::get_main_mix(game)))
			local_mix.open("local.mix", main_mix);
	}
	for (int category = 0; category < ct_unknown; category++)
	{
		if (!contains(static_cast<t_category_type>(category)))
			continue;
		Cxif_key& k = key.open_key_edit(category);
		t_category_file_list list = category_file_list(static_cast<t_category_type>(category));
		int id = 0;
		for (t_category_file_list::const_iterator i = list.begin(); i != list.end(); i++)
		{
			if (export)
			{
				Ccc_file f(true);
				if (!f.open(*i))
				{
					t_file_type ft = f.get_file_type();
					Cxif_key& l = k.open_key_edit(id++);
					l.set_value_string(vi_fname, Cfname(*i).get_fname());
					l.set_value_int(vi_ft, ft);
					switch (category)
					{
					case ct_ini:
						l.set_value_binary(vi_fdata, f.get_data(), f.get_size());
						if (m_options.ini_diff_compression && local_mix.is_open())
						{
							Ccc_file g(true);
							string fname = Cfname(*i).get_fname();
							if (!g.open(fname, local_mix))
							{
								Cneat_ini_reader ir1, ir2;
								ir1.process(f.get_data(), f.get_size());
								ir2.process(g.get_data(), g.get_size());
								g.close();
								const Cneat_ini_reader::t_section_list& sl1 = ir1.get_section_list();
								const Cneat_ini_reader::t_section_list& sl2 = ir2.get_section_list();
								const Cneat_ini_reader::t_section_map& sm1 = ir1.get_section_map();
								const Cneat_ini_reader::t_section_map& sm2 = ir2.get_section_map();
								Cneat_ini_reader::t_section_list::const_iterator i;
								for (i = sl1.begin(); i != sl1.end(); i++)
								{
									string section_name = (*i)->first;
									Cneat_ini_reader::t_section_map::const_iterator j = sm2.find(section_name);
									ir1.sub_section(section_name, j == sm2.end() ? Cneat_key_list() : j->second);
								}
								for (i = sl2.begin(); i != sl2.end(); i++)
								{
									string section_name = (*i)->first;
									if (sm1.find(section_name) == sm1.end())
										ir1.sub_section(section_name, (*i)->second);
								}
								strstream s;
								ir1.write(s);
								// ir1.write("c:/temp/" + fname);
								l.set_value_binary(vi_fdata, s.str(), s.pcount());
								l.set_value_int(vi_encoding, enc_diff);						
							}
						}
						break;
					case ct_st:
						l.set_value_binary(vi_fdata, f.get_data(), f.get_size());
						if (m_options.csf_diff_compression && language_mix.is_open())
						{
							Ccsf_file e, g, h;
							string fname = Cfname(*i).get_fname();
							if (!g.open(fname, language_mix))
							{
								Ccsf_file h;
								h.load(f);
								const Ccsf_file::t_map& map = h.get_map();
								for (Ccsf_file::t_map::const_iterator i = map.begin(); i != map.end(); i++)
								{
									if (!g.has_name(i->first) || g.get_value(i->first) != i->second.value)
										e.set_value(i->first, i->second.value, i->second.extra_value);
								}
								g.close();
								int cb_d = e.get_write_size();
								byte* d = new byte[cb_d];
								e.write(d);
								l.set_value_binary(vi_fdata, d, cb_d);
								l.set_value_int(vi_encoding, enc_diff);
								delete[] d;
							}
						}
						break;
					default:
						switch (ft)
						{
						/*
						case ft_shp_ts:
						{
						// FIXME: palet should be removed
						t_palet palet;
						Cshp_ts_file g;
						g.load(f.get_data(), f.get_size());
						Cvirtual_image image;
						g.extract_as_pcx(image, palet, false);
						shp_xor_encode_frames(image, g.get_c_images());
						l.set_value_int(vi_cx, image.cx());
						l.set_value_int(vi_cy, image.cy());
						l.set_value_int(vi_c_frames, g.get_c_images());
						l.set_value_binary(vi_fdata, image.image(), image.cb_image());
						break;
						}
							*/
						default:
							l.set_value_binary(vi_fdata, f.get_data(), f.get_size());
						}
					}
					f.close();
				}
			}
			else
			{
				Cxif_key& l = k.open_key_edit(id++);
				l.set_value_string(vi_fname, *i);
			}
		}
	}
	if (export)
	{
		if (local_mix.is_open())
			local_mix.close();
		if (main_mix.is_open())
			main_mix.close();
		if (language_mix.is_open())
			language_mix.close();
	}
	key.set_value_string(vi_name, m_options.name);
	key.set_value_string(vi_mail, m_options.mail);
	key.set_value_string(vi_link_title, m_options.link_title);
	key.set_value_string(vi_link, m_options.link);
	key.set_value_string(vi_mod_name, m_options.mod_name);
	key.set_value_int(vi_game, m_options.game);
	key.set_value_int(vi_csf_diff_compression, m_options.csf_diff_compression);
	key.set_value_int(vi_ini_diff_compression, m_options.ini_diff_compression);
	key.set_value_int(vi_custom_button_text, m_options.custom_button_text);
	key.set_value_int(vi_exit_button, m_options.exit_button);
	key.set_value_int(vi_manual_button, m_options.manual_button);
	key.set_value_int(vi_site_button, m_options.site_button);
	key.set_value_int(vi_update_button, m_options.update_button);
	key.set_value_int(vi_xhp_button, m_options.xhp_button);
	key.set_value_string(vi_mod_version, m_options.mod_version);
	key.set_value_string(vi_mod_ucf, m_options.mod_ucf);
	key.set_value_int(vi_confirm_deactivate, m_options.confirm_deactivate);
	return key;
}

__int64 get_last_write_time(string fname)
{
	FILETIME r;
	memset(&r, 0, sizeof(FILETIME));
	Cfile32 f;
	if (!f.open_read(fname))
	{
		r = f.get_last_write_time();
		f.close();
	}
	return *reinterpret_cast<__int64*>(&r);
}

int Cxcc_mod::activate(const Cxif_key& key, bool external_data)
{
	Cmix_file_write expand_mix;
	Cmix_file_write ecache_mix;
	Cmix_file main_mix;
	Cmix_file local_mix;
	Cmix_file language_mix;
	const string mod_name = key.get_value_string(vi_mod_name);
	const t_game game = static_cast<t_game>(key.get_value_int(vi_game));
	const string dir = xcc_dirs::get_dir(game);
	const string temp_dir = get_temp_path() + mod_name + " Cache/";
	if (external_data)
		CreateDirectory(temp_dir.c_str(), NULL);
	int error = main_mix.open(xcc_dirs::get_main_mix(game));
	if (!error)
	{
		language_mix.open(dir + "language.mix");
		error = local_mix.open("local.mix", main_mix);
		if (!error)
		{
			for (t_xif_key_map::const_iterator category = key.m_keys.begin(); category != key.m_keys.end(); category++)
			{
				if (error)
					break;
				if (category->second.m_keys.empty())
					continue;
				Cxse xse;
				switch (category->first)
				{
				case ct_launcher:
				case ct_manual:
					continue;
				case ct_sound:
					if (game == game_ra2 && xse.open())
					{
						error = 1;
						continue;
					}
					break;
				}
				for (t_xif_key_map::const_iterator i = category->second.m_keys.begin(); i != category->second.m_keys.end(); i++)
				{
					if (error)
						break;
					const Cfname external_fname = i->second.get_value_string(vi_fname);
					Cfname fname = Cfname(external_fname).get_fname();
					Ccc_file f(true);
					t_file_type ft;
					const byte* data;
					int cb_data;
					t_encoding encoding;
					__int64 last_write_time;
					if (external_data)
					{
						if (f.open(external_fname))
							break;
						ft = f.get_file_type();
						data = f.get_data();
						cb_data = f.get_size();
						encoding = enc_none;
						last_write_time = get_last_write_time(external_fname);
					}
					else
					{
						const Cxif_value& fdata = i->second.get_value(vi_fdata);
						ft = static_cast<t_file_type>(i->second.get_value_int(vi_ft));
						data = fdata.get_data();
						cb_data = fdata.get_size();
						encoding = i->second.exists_value(vi_encoding) ? static_cast<t_encoding>(i->second.get_value_int(vi_encoding)) : enc_none;
						last_write_time = 0;
					}
					Cvirtual_file h;
					bool ignore = false;
					switch (ft)
					{
					case ft_jpeg:
						fname.set_ext(".pcx");
						if (get_last_write_time(temp_dir + fname) < last_write_time || h.import(temp_dir + fname))
						{
							Cjpeg_file g;
							g.load(data, cb_data);
							Cvirtual_image image;
							if (!g.decode(image))
							{
								image.save_as_pcx(h);
								if (external_data)
								{
									string temp_fname = temp_dir + fname;
									h.export(temp_fname);
								}
								h.compact();
								data = h.data();
								cb_data = h.size();
							}
						}
						else
						{
							data = h.data();
							cb_data = h.size();
						}
						break;
					case ft_ogg:
						fname.set_ext(game == game_ts ? ".aud" : ".wav");
						if (Cfname(dir + fname).exists())
							ignore = true;
						else if (get_last_write_time(temp_dir + fname) < last_write_time || h.import(temp_dir + fname))
						{
							Cogg_file g;
							g.load(data, cb_data);
							Cvirtual_audio audio;
							if (!g.decode(audio))
							{
								if (game == game_ts)
								{
									/*
									if (audio.c_channels() == 2)
									{
										const __int16* r = audio.audio();
										const __int16* r_end = r + (audio.c_samples() << 1);
										__int16* d = new __int16[audio.c_samples()];
										__int16* w = d;
										while (r < r_end)
										{
											int v = *r++ + *r++;
											*w++ = v / 2;
										}
										audio.load(d, audio.c_samples(), audio.samplerate(), audio.cb_sample(), 1);
										delete[] d;
									}
									*/
									if (audio.c_channels() != 1)
										error = 1;
									else
										audio.save_as_aud(h);
								}
								else
									audio.save_as_wav_ima_adpcm(h);
								if (!error)
								{
									if (external_data)
									{
										string temp_fname = temp_dir + fname;
										h.export(temp_fname);
									}
									h.compact();
									data = h.data();
									cb_data = h.size();
								}
							}
						}
						else
						{
							data = h.data();
							cb_data = h.size();
						}
						break;
					case ft_pcx:
						if ((category->first == ct_cameo || (category->first == ct_screen && game == game_ra2)))
						{
							Cpcx_file g;
							g.load(data, cb_data);
							if (g.get_c_planes() == 1)
							{
								fname.set_ext(".shp");
								Cvirtual_image image;
								g.decode(image);							
								shp_ts_file_write(image, h, 1, true);
								h.compact();
								data = h.data();
								cb_data = h.size();
							}
						}
						break;
					}
					if (!error && !ignore)
					{
						switch (category->first)
						{
						case ct_cameo:
						case ct_shp:
							ecache_mix.add_file(fname, data, cb_data);
							break;
						case ct_ini:
							if (encoding == enc_diff)
							{
								Ccc_file g(true);
								if (g.open(fname, local_mix))
									error = 1;
								else
								{
									Cneat_ini_reader ir;
									ir.process(g.get_data(), g.get_size());
									ir.process(data, cb_data);
									g.close();
									strstream s;
									ir.write(s);
									expand_mix.add_file(fname, s.str(), s.pcount());
								}
							}
							else
								expand_mix.add_file(fname, data, cb_data);
							break;
						case ct_interface:
						case ct_screen:
							expand_mix.add_file(fname, data, cb_data);
							break;
						case ct_sound:
							if (game == game_ts)
								ecache_mix.add_file(fname, data, cb_data);
							else
							{
								Cwav_file f;
								f.load(data, cb_data);
								xse.insert(fname.get_ftitle(), f);
							}
							break;
						case ct_speech:
							ecache_mix.add_file(fname, data, cb_data);
							break;
						case ct_st:
							if (encoding == enc_diff)
							{
								Ccc_file g(true);
								if (!language_mix.is_open() || g.open(fname, language_mix))
									error = 1;
								else
								{
									Ccsf_file e, h;
									e.load(g);
									h.load(data, cb_data);
									const Ccsf_file::t_map& map = h.get_map();
									for (Ccsf_file::t_map::const_iterator i = map.begin(); i != map.end(); i++)
									{
										e.set_value(i->first, i->second.value, i->second.extra_value);
									}
									g.close();
									int cb_d = e.get_write_size();
									byte* d = new byte[cb_d];
									e.write(d);
									error = file32_write(dir + fname, d, cb_d);
									delete[] d;
								}
							}
							else
								error = file32_write(dir + fname, data, cb_data);
							break;
						case ct_theme:
						case ct_video:
							error = file32_write(dir + fname, data, cb_data);
							break;
						default:
							expand_mix.add_file(fname, data, cb_data);
						}
					}
					if (external_data)
						f.close();
				}
				switch (category->first)
				{
				case ct_sound:
					if (game == game_ra2)
					{
						if (!error)
							xse.write_idx_file();
						xse.close();
					}
					break;
				}
			}
			local_mix.close();
			if (language_mix.is_open())
				language_mix.close();
		}
		main_mix.close();
	}
	if (!error)
	{
		if (game == game_ts)
			expand_mix.add_file("ecache98.mix", ecache_mix);
		else
			error = ecache_mix.write(dir + "ecache98.mix");
		if (!error)
			error = expand_mix.write(dir + "expand98.mix");
	}
	return error;
}

int Cxcc_mod::activate() const
{
	return activate(save(false), true);
}

int Cxcc_mod::deactivate(bool remove_themes) const
{
	const t_game game = m_options.game;
	string dir = xcc_dirs::get_dir(game);
	for (t_file_list::const_iterator category = m_file_list.begin(); category != m_file_list.end(); category++)
	{
		const t_category_file_list& list = category->second;
		if (category->first == ct_theme && !remove_themes)
			continue;
		for (t_category_file_list::const_iterator i = list.begin(); i != list.end(); i++)
		{
			Cfname fname = Cfname(*i).get_fname();
			if (category->first == ct_theme)
				fname.set_ext(game == game_ts ? ".aud" : ".wav");
			switch (category->first)
			{
			case ct_st:
			case ct_theme:
			case ct_video:
				delete_file(dir + fname);
				break;
			}
		}
	}
	// delete_file(dir + "audio.bag");
	// delete_file(dir + "audio.idx");
	delete_file(dir + "ecache98.mix");
	delete_file(dir + "expand98.mix");
	return 0;
}

static int create_process(const string& exe_name, const string& _cmd_line, bool wait)
{
	char cmd_line[256];
	strcpy(cmd_line, ("\"" + exe_name + "\" " + _cmd_line).c_str());
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
	int error = !CreateProcess(exe_name.c_str(), cmd_line, NULL, NULL, false, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);
	if (!error && wait)
		WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return error;
}

int Cxcc_mod::launch_game(bool wait) const
{
	return create_process(xcc_dirs::get_exe(options().game), "", wait);
}

void Cxcc_mod::clear_game_dir() const
{
	string dir = xcc_dirs::get_dir(m_options.game);
	delete_file(dir + "ai.ini");
	delete_file(dir + "art.ini");
	delete_file(dir + "audio.bag");
	delete_file(dir + "audio.idx");
	delete_files(dir + "ecache*.mix");
	delete_files(dir + "elocal*.mix");
	delete_files(dir + "expand*.mix");
	delete_file(dir + "ra2.csf");
	delete_file(dir + "rules.ini");
	delete_file(dir + "sound.ini");
	delete_file(dir + "ui.ini");
}

int Cxcc_mod::load_banner(const Cxif_key& key, Cvirtual_image& image)
{
	if (!key.exists_key(ct_launcher))
		return 1;
	const Cxif_key& category = key.open_key_read(ct_launcher);
	for (t_xif_key_map::const_iterator i = category.m_keys.begin(); i != category.m_keys.end(); i++)
	{
		string fname = i->second.get_value_string(vi_fname);
		if (fname != "banner.jpeg")
			continue;
		Cjpeg_file f;
		const Cxif_value& fdata = i->second.get_value(vi_fdata);
		f.load(fdata.get_data(), fdata.get_size());
		if (!f.is_valid() || f.decode(image))
			break;
		return 0;
	}
	return 1;
}

int Cxcc_mod::launch_manual(const Cxif_key& key, string dir, HWND hWnd)
{
	if (!key.exists_key(ct_manual))
		return 1;
	int error = 0;
	string index;
	const Cxif_key& category = key.open_key_read(ct_manual);
	for (t_xif_key_map::const_iterator i = category.m_keys.begin(); i != category.m_keys.end(); i++)
	{
		if (error)
			break;
		string fname = i->second.get_value_string(vi_fname);
		if (Cfname(fname).get_ftitle() == "index")
			index = fname;
		const Cxif_value& fdata = i->second.get_value(vi_fdata);
		error = file32_write(dir + fname, fdata.get_data(), fdata.get_size());
	}
	if (!error)
	{
		if (index.empty())
			dir.erase(dir.length() - 1);
		ShellExecute(hWnd, "open", (dir + index).c_str(), NULL, NULL, SW_SHOW);
	}
	return error;
}

void Cxcc_mod::report(string fname) const
{
	Chtml page;
	const t_game game = m_options.game;
	t_file_type ft_audio = game == game_ts ? ft_aud : ft_wav;
	for (int category = 0; category < ct_unknown; category++)
	{
		if (!contains(static_cast<t_category_type>(category)))
			continue;
		page +=	tr(th(ct_name[category], "colspan=4"));
		t_category_file_list list = category_file_list(static_cast<t_category_type>(category));
		for (t_category_file_list::const_iterator i = list.begin(); i != list.end(); i++)
		{
			Cfname fname = Cfname(*i).get_fname();
			Chtml row = td(static_cast<string>(fname));
			Ccc_file f(false);
			if (f.open(*i))
				row += td("not found", "colspan=3");
			else
			{
				t_file_type ft = f.get_file_type();
				row += td(ft_name[ft]) + td(n(f.get_size()), "align=right");
				switch (ft)
				{
				case ft_jpeg:
					ft = ft_pcx;
					break;
				case ft_ogg:
					ft = ft_audio;
					break;
				case ft_pcx:
					if ((category == ct_cameo || (category == ct_screen && game == game_ra2)))
						ft = ft_shp_ts;
					break;
				}
				string error = "&nbsp;";
				switch (category)
				{
				case ct_cameo:
				case ct_shp:
					if (ft != ft_shp_ts)
						error = "Wrong file type";
					break;
				case ct_hva:
					fname.set_ext(".vxl");
					if (ft != ft_hva)
						error = "Wrong file type";
					else if (!contains(ct_vxl, fname, true))
						error = "Missing VXL";
					break;
				case ct_sound:
				case ct_speech:
				case ct_theme:
					if (ft != ft_audio)
						error = "Wrong file type";
					break;
				case ct_vxl:
					fname.set_ext(".hva");
					if (ft != ft_vxl)
						error = "Wrong file type";
					else if (!contains(ct_hva, fname, true))
						error = "Missing HVA";
					break;
				}
				row += td(error);
				f.close();
			}
			page += tr(row);
		}
	}
	page +=	tr(th("options", "colspan=4"))
		+ tr(td("name") + td(m_options.name, "colspan=3"))
		+ tr(td("mod_name") + td(m_options.mod_name, "colspan=3"))
		+ tr(td("mod_ucf") + td(m_options.mod_ucf, "colspan=3"))
		+ tr(td("mod_version") + td(m_options.mod_version, "colspan=3"))
		+ tr(td("game") + td(game_name[m_options.game], "colspan=3"))
		+ tr(td("csf_diff_compression") + td(n(m_options.csf_diff_compression), "colspan=3"))
		+ tr(td("ini_diff_compression") + td(n(m_options.ini_diff_compression), "colspan=3"));
	ofstream(fname.c_str()) << head_xcc(m_options.mod_name) + body(table(page, "border=1 width=100%"));
}
