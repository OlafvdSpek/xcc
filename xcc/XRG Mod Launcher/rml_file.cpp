#include "stdafx.h"
#include "rml_file.h"

#include <fstream>
#include "jpeg_file.h"
#include "mix_file.h"
#include "mix_rg_file_write.h"
#include "string_conversion.h"
#include "tga_file.h"
#include "xcc_dirs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int get_run_len(const byte* s, const byte* s_end, const byte* d, const byte* d_end)
{
	int c = 0;
	while (s < s_end && d < d_end && *s++ == *d++)
		c++;
	return c;
}

int strip_chunk(const byte* s, int cb_s, byte* d, int id)
{
	const byte* r = s;
	const byte* r_end = s + cb_s;
	byte* w = d;
	while (r < r_end)
	{
		const t_w3d_header& h = *reinterpret_cast<const t_w3d_header*>(r);
		if (h.id == id)
		{
			t_w3d_header& h = *reinterpret_cast<t_w3d_header*>(w);
			memcpy(w, r, sizeof(t_w3d_header));
			r += sizeof(t_w3d_header) + h.size();
			w += sizeof(t_w3d_header);
			h.id = 0;
			h.m_size = 0;
		}
		else if (h.container())
		{
			t_w3d_header& h = *reinterpret_cast<t_w3d_header*>(w);
			memcpy(w, r, sizeof(t_w3d_header));
			r += sizeof(t_w3d_header);
			w += sizeof(t_w3d_header);
			int size = strip_chunk(r, h.size(), w, id);
			r += h.size();
			w += size;
			h.m_size = 0x80000000 | size;
		}
		else
		{
			memcpy(w, r, sizeof(t_w3d_header) + h.size());
			r += sizeof(t_w3d_header) + h.size();
			w += sizeof(t_w3d_header) + h.size();
		}
	}
	return w - d;
}

void wipe_chunk(Cvirtual_binary& d, int id)
{
	byte* r = d.data_edit();
	while (r < d.data_end())
	{
		t_w3d_header& h = *reinterpret_cast<t_w3d_header*>(r);
		r += sizeof(t_w3d_header);
		if (h.id == id)
		{
			h.id = 0;
			memset(r, 0, h.size());
		}
		if (!h.container())
			r += h.size();		
	}
}

typedef vector<int> t_offset_map;
typedef vector<t_offset_map> t_word_map;

Cvirtual_binary encode_diff(Cvirtual_binary s, Cvirtual_binary d)
{
	Cvirtual_binary e, f;
	memcpy(e.write_start(s.size() + d.size()), s.data(), s.size());
	memcpy(e.data_edit() + s.size(), d.data(), d.size());
	t_word_map word_map;
	{
		word_map.resize(0x10000);
		const byte* r = e.data();
		const byte* r_end = e.data_end() - 1;
		while (r < r_end)
		{
			word_map[*reinterpret_cast<const unsigned __int16*>(r)].push_back(r - e.data());
			r++;
		}
		ofstream f("c:/temp/word_map.txt");
		for (int i = 0; i < 0x10000; i++)
		{
			for (int j = 0; j < word_map[i].size(); j++)
				f << nh(4, i) << ": " << word_map[i][j] << endl;
		}
	}
	const byte* r = d.data();
	const byte* r_end = d.data_end();
	__int32* w = reinterpret_cast<__int32*>(f.write_start(1 << 20));
	int raw_count = 0;
	while (r < r_end)
	{
		int d_ofs = r - d.data();
		const byte* p;
		int cb_p = 0;
		if (r_end - r > 1)
		{
			int v = *reinterpret_cast<const unsigned __int16*>(r);
			for (t_offset_map::const_iterator i = word_map[v].begin(); i != word_map[v].end(); i++)
			{
				int cb = get_run_len(e.data() + (r - d.data() + s.size()), e.data_end(), e.data() + *i, e.data() + (r - d.data() + s.size()));
				if (cb > cb_p)
				{
					p = e.data() + *i;
					cb_p = cb;
				}
			}
		}
		if (cb_p < 3)
		{
			r++;
			raw_count++;
		}
		else
		{
			if (raw_count)
			{
				// cout << raw_count << endl;
				*w++ = -1;
				*w++ = raw_count;
				memcpy(w, r - raw_count, raw_count);
				w = reinterpret_cast<__int32*>(reinterpret_cast<byte*>(w) + raw_count);
				raw_count = 0;
			}
			// cout << d_ofs << ": " << cb_p << ", " << p - e.data() << endl;
			r += cb_p;
			*w++ = p - e.data();
			*w++ = cb_p;
		}
	}
	if (raw_count)
	{
		// cout << raw_count << endl;
		*w++ = -1;
		*w++ = raw_count;
		memcpy(w, r - raw_count, raw_count);
		w = reinterpret_cast<__int32*>(reinterpret_cast<byte*>(w) + raw_count);
		raw_count = 0;
	}
	f.size(reinterpret_cast<byte*>(w) - f.data());
	return f;
}

Cvirtual_binary decode_diff(Cvirtual_binary s, Cvirtual_binary e)
{
	Cvirtual_binary d;
	const __int32* r = reinterpret_cast<const __int32*>(e.data());
	const __int32* r_end = reinterpret_cast<const __int32*>(e.data_end());
	byte* w = d.write_start(s.size() << 1);
	while (r < r_end)
	{
		int p = *r++;
		int cb_p = *r++;
		if (p == -1)
		{
			memcpy(w, r, cb_p);
			r = reinterpret_cast<const __int32*>(reinterpret_cast<const byte*>(r) + cb_p);
			w += cb_p;
		}
		else
		{
			memcpy(w, p < s.size() ? s.data() + p : d.data() + p - s.size(), cb_p);
			w += cb_p;
		}
	}
	d.size(w - d.data());
	return d;
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
	vi_confirm_deactivate,
	vi_mf_version,
	vi_shp_compression,
	vi_vxl_compression,
	vi_cb_d,
	vi_mode,
	vi_module,
	ki_modes = 0x100,
	ki_modules
};

enum t_encoding
{
	enc_none,
	enc_diff,
	enc_jpeg,
	enc_mng,
	enc_mpeg,
	enc_ogg,
	enc_png,
	enc_shp,
	enc_vxl
};

Cxif_key encode_rmlf(const string& fname, bool binary_diff_compression, bool tga_compression)
{
	Cxif_key key;
	Cmix_file always_dbs;
	Cmix_file always_dat;
	Cmix_file mix_f;
	always_dat.open(xcc_dirs::get_dir(game_rg) + "data/always.dat");
	always_dbs.open(xcc_dirs::get_dir(game_rg) + "data/always.dbs");
	mix_f.open(fname);
	for (int i = 0; i < mix_f.get_c_files(); i++)
	{
		int id = mix_f.get_id(i);
		string fname = mix_f.get_name(id);
		if (fname == "asset_report.txt" || fname == "scripts.dll")
			continue;
		Cvirtual_binary s = always_dat.get_vdata(id);
		Cvirtual_binary d = mix_f.get_vdata(id);
		if (!s.data())
			s = always_dbs.get_vdata(id);
		if (s.size() != d.size() || memcmp(s.data(), d.data(), s.size()))
		{
			Cxif_key& k = key.open_key_write();
			k.set_value_string(vi_fname, fname);
			Ccc_file f(true);
			f.load(d);
			t_file_type ft = f.get_file_type();
			if (fname == "objects.ddb")
			{
				Cvirtual_binary s = d;
				d.size(strip_chunk(s.data(), s.size(), d.data_edit(), 0x00100100));
			}
			if (ft == ft_tga)
			{
				Ctga_file f;
				f.load(d);
				Cvirtual_image image;
				Cvirtual_file vf;
				if (tga_compression && f.cb_pixel() == 3 && !f.decode(image) && !image.save(vf, ft_jpeg))
				{
					d = vf.read();
					k.set_value_int(vi_encoding, enc_jpeg);
				}
			}
			else if (binary_diff_compression && s.data())
			{
				d = encode_diff(s, d);
				k.set_value_int(vi_encoding, enc_diff);
			}
			k.set_value_binary(vi_fdata, d);
		}
	}
	mix_f.close();
	always_dbs.close();
	always_dat.close();
	return key;
}

Cvirtual_binary decode_rmlf(const string& fname)
{
	Cxif_key key;
	Cvirtual_binary s;
	s.import(fname);
	key.load_key(s);
	Cmix_file always_dat;
	Cmix_file always_dbs;
	Cmix_rg_file_write mix_f;
	always_dat.open(xcc_dirs::get_dir(game_rg) + "data/always.dat");
	always_dbs.open(xcc_dirs::get_dir(game_rg) + "data/always.dbs");
	for (t_xif_key_map::const_iterator i = key.m_keys.begin(); i != key.m_keys.end(); i++)
	{
		const Cxif_key& k = i->second;
		string fname = k.get_value_string(vi_fname);
		Cvirtual_binary d;
		if (k.exists_value(vi_fdata))
		{
			d = k.get_value(vi_fdata).get_vdata();
			if (k.get_value_int(vi_encoding, enc_none) == enc_diff)
			{
				Cvirtual_binary s = always_dat.get_vdata(fname);
				if (!s.data())
					s = always_dbs.get_vdata(fname);
				d = decode_diff(s, d);
			}
			else if (k.get_value_int(vi_encoding, enc_none) == enc_jpeg)
			{
				Cjpeg_file f;
				f.load(d);
				Cvirtual_image image;
				Cvirtual_file vf;
				if (!f.decode(image) && !image.save(vf, ft_tga))
					d = vf.read();
			}
		}
		else
			d = always_dat.get_vdata(fname);
		mix_f.insert(fname, d);
	}
	always_dbs.close();
	always_dat.close();
	return mix_f.write();
}
