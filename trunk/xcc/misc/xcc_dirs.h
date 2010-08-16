#pragma once

#include "cc_structures.h"
#include "fname.h"

class xcc_dirs  
{
public:
	static bool enable_log();
	static void load_from_registry();
	static void save_to_registry();
	static string find_file(Cfname s);
	static bool is_available(t_game game);
	static string get_audio_mix(t_game game);
	static string get_csf_fname(t_game game);
	static string get_dir(t_game game);
	static string get_exe(t_game game);
	static string get_ecache_mix(t_game game, bool dir, int i);
	static string get_ecache_mix(t_game game, bool dir, const string& s);
	static string get_expand_mix(t_game game, int i);
	static string get_expand_mix(t_game game, const string& s);
	static string get_language_mix(t_game game);
	static string get_local_mix(t_game game);
	static string get_main_mix(t_game game);
	static void set_td_secondary_dir(const string& s);
	static void set_cd_dir(const string &s);
	static void set_data_dir(const string &s);
	static void set_dir(t_game game, const string& s);
	static void reset_cd_dir();
	static void reset_data_dir();
	static const string& get_td_secondary_dir();
	static const string& get_cd_dir();
	static const string& get_data_dir();

	static bool use_external_files()
	{
		return m_use_external_files;
	}

	static void use_external_files(bool v)
	{
		m_use_external_files = v;
	}
private:
	static void read_dir(const string& key, const string& value, t_game game);

	static bool m_use_external_files;
};
