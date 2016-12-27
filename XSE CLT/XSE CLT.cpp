#include "stdafx.h"
#include <iostream>
#include "mix_file.h"
#include "mix_file_write.h"
#include "wav_file.h"
#include "xcc_dirs.h"
#include "xse.h"

using namespace std;

int main(int c_args, char** arg)
{
	cerr << " XSE CLT, Copyright (C) Olaf van der Spek 2000             OlafvdSpek@GMail.Com" << endl
		<< endl;
	if (c_args != 2)
	{
		cerr << "Syntax:" << endl
			<< "  xse_clt - or" << endl
			<< "  xse_clt +" << endl;
		return 1;
	}
	const string mode = arg[1];
	xcc_dirs::load_from_registry();
	Cxse xse;
	int error = xse.open();
	if (!error)
	{
		const Cxse::t_map& map = xse.map();
		if (mode == "-")
		{
			Cmix_file language;
			error = language.open(xcc_dirs::get_dir(game_ra2) + "language.mix");
			if (!error)
			{
				language.set_game(game_ra2);
				Cmix_file audio;
				error = audio.open("audio.mix", language);
				if (!error)
				{
					audio.set_game(game_ra2);
					Caudio_idx_file g;
					error = g.open("audio.idx", audio);
					if (!error)
					{
						Cmix_file_write out_f(game_ra2);
						for (int i = 0; i < g.c_sounds(); i++)
						{
							const t_audio_idx_entry& s  = g.sound_entry(i);
							auto j = map.find(s.fname);
							if (j == map.end() || j->second.size != s.size)
							{
								Cvirtual_file f;
								error = xse.extract(s.fname, f);
								if (!error)
									out_f.add_file(static_cast<string>(s.fname) + ".wav", f.read());

							}
						}
						if (!error)
							error = out_f.write().save("audio.diff");
						g.close();
					}
					audio.close();
				}
				language.close();
			}
		}
		else if (mode == "+")
		{
			Cmix_file audio;
			error = audio.open("audio.diff");
			if (!error)
			{
				for (int i = 0; i < audio.get_c_files(); i++)
				{
					Cwav_file f;
					int id = audio.get_id(i);
					error = f.open(id, audio);
					if (!error)
					{
						if (f.is_valid())
							error = xse.insert(Cfname(audio.get_name(id)).get_ftitle(), f);
						f.close();
					}
				}
				if (!error)
					xse.write_idx_file();
				audio.close();
			}
		}
		xse.close();
	}
	return 0;
}
