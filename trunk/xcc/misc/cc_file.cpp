// cc_file.cpp: implementation of the Ccc_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cc_file.h"

#include "art_ts_ini_reader.h"
#include "aud_file.h"
#include "avi_file.h"
#include "big_file.h"
#include "bin_file.h"
#include "bink_file.h"
#include "bmp_file.h"
#include "csf_file.h"
#include "cps_file.h"
#include "dds_file.h"
#include "fnt_file.h"
#include "hva_file.h"
#include "id_log.h"
#include "jpeg_file.h"
#include "map_td_ini_reader.h"
#include "map_ra_ini_reader.h"
#include "map_ts_ini_reader.h"
#include "mix_file.h"
#include "mix_rg_file.h"
#include "mp3_file.h"
#include "null_ini_reader.h"
#include "ogg_file.h"
#include "pak_file.h"
#include "pal_file.h"
#include "pcx_file.h"
#include "png_file.h"
#include "pkt_ts_ini_reader.h"
#include "rules_ts_ini_reader.h"
#include "shp_dune2_file.h"
#include "shp_file.h"
#include "shp_ts_file.h"
#include "sound_ts_ini_reader.h"
#include "st_file.h"
#include "string_conversion.h"
#include "text_file.h"
#include "tga_file.h"
#include "theme_ts_ini_reader.h"
#include "tmp_file.h"
#include "tmp_ra_file.h"
#include "tmp_ts_file.h"
#include "virtual_tfile.h"
#include "voc_file.h"
#include "vqa_file.h"
#include "vqp_file.h"
#include "vxl_file.h"
#include "w3d_file.h"
#include "wav_file.h"
#include "wsa_dune2_file.h"
#include "wsa_file.h"
#include "xcc_dirs.h"
#include "xcc_file.h"
#include "xcc_lmd_file.h"
#include "xif_file.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* ft_name[] = 
{
	"ai ini (ts)", 
	"ai ini (ra2)", 
	"art ini (ts)", 
	"art ini (ra2)",
	"aud",
	"avi",
	"big",
	"bin",
	"bink",
	"bmp",
	"clipboard",
	"csf",
	"cps",
	"csv",
	"dds",
	"dir",
	"drive",
	"fnt",
	"html",
	"hva", 
	"ini",
	"jpeg",
	"jpeg (single)",
	"map (dune2)",
	"map (td)",
	"map (ra)",
	"map (ts)",
	"map (ts) preview",
	"map (ra2)", 
	"mix", 
	"mix (rg)",
	"mng",
	"mp3",
	"mrf",
	"ogg",
	"pak",
	"pal",
	"pal (jasc)",
	"pcx (single)",
	"pcx",
	"png (single)",
	"png",
	"pkt (ts)",
	"riff",
	"rules ini (ts)",
	"rules ini (ra2)",
	"shp (dune2)",
	"shp",
	"shp (ts)",
	"sound ini (ts)",
	"sound ini (ra2)",
	"string table",
	"text",
	"tga",
	"tga (single)",
	"theme ini (ts)",
	"theme ini (ra2)",
	"tmp",
	"tmp (ra)",
	"tmp (ts)",
	"voc",
	"vpl",
	"vqa",
	"vqp",
	"vxl",
	"w3d",
	"wav",
	"pcm wav",
	"ima adpcm wav",
	"wsa (dune2)",
	"wsa",
	"xcc lmd",
	"xcc unknown",
	"xif",
	"zip",
	"unknown"
};

Ccc_file::Ccc_file(bool read_on_open):
    m_read_on_open(read_on_open)
{
	m_is_open = false;
}

#define test_fail(res) { int v = res; if (v) { close(); return v; }}

#ifndef NO_MIX_SUPPORT
int Ccc_file::open(unsigned int id, Cmix_file& mix_f)
{
	if (mix_f.get_index(id) == -1)
		return -1;
	m_mix_f = &mix_f;
	m_offset = m_mix_f->get_offset(id);
	m_size = m_mix_f->get_size(id);
	m_p = 0;
	m_is_open = true;
	m_data = mix_f.get_vdata(id);
	test_fail(post_open())
		return 0;
}

int Ccc_file::open(const string& name, Cmix_file& mix_f)
{
    return open(Cmix_file::get_id(mix_f.get_game(), name), mix_f);
}
#endif

int Ccc_file::open(const string& name)
{
    assert(!is_open());
#ifdef NO_MIX_SUPPORT
	test_fail(m_f.open_read(name));
#else
	test_fail(m_f.open_read(xcc_dirs::find_file(name)));
#endif
	m_mix_f = NULL;
	m_size = m_f.get_size();
	m_p = 0;
    m_is_open = true;
	m_data = m_f.get_mm();
    if (m_read_on_open)
        m_f.close();
#ifndef NO_FT_SUPPORT
	Cfname fname = to_lower(name);
	if (fname.get_fext() == ".mmx")
	{
		fname.set_ext(".map");
		mix_database::add_name(game_ra2, fname.get_fname(), "-");
		fname.set_ext(".pkt");
		mix_database::add_name(game_ra2, fname.get_fname(), "-");
	}
#endif
    test_fail(post_open())
    return 0;
}

int Ccc_file::open(const char* name)
{
	return open(static_cast<string>(name));
}

const Cwin_handle& Ccc_file::h()
{
	assert(is_open());
	return m_f.h();
}

int Ccc_file::open(const Cwin_handle& h)
{
    assert(!is_open());
	m_f.open(h);
	m_mix_f = NULL;
	m_size = m_f.get_size();
	m_p = 0;
    m_is_open = true;
	m_data = m_f.get_mm();
    if (m_read_on_open)
        m_f.close();
    test_fail(post_open())
	return 0;
}

void Ccc_file::load(const Cvirtual_binary& d, int size)
{
	m_data = d;
	m_mix_f = NULL;
	m_is_open = true;
	m_p = 0;
	m_size = size == -1 ? d.size() : size;
	post_open();
}

void Ccc_file::load(const Ccc_file& f)
{
	load(f.get_vdata());
}

#ifndef NO_MIX_SUPPORT
#ifndef NO_FT_SUPPORT
t_file_type Ccc_file::get_file_type(bool fast)
{
	Cvirtual_binary data;
	int size;
	if (m_data)
	{
		data = m_data;
		size = m_size;
	}
	else
	{
		size = min(m_size, 64 << 10);
		seek(0);
		if (read(data.write_start(size), size))
			return ft_unknown;
		seek(0);
	}
	t_file_type ft = ft_unknown;
	Caud_file aud_f;
	Cbin_file bin_f;
	Cbink_file bink_f;
	Cbig_file big_f;
	Cbmp_file bmp_f;
	Ccsf_file csf_f;
	Ccps_file cps_f;
	Cdds_file dds_f;
	Cfnt_file fnt_f;
	Chva_file hva_f;
	Cmix_file mix_f;
	Cmix_rg_file mix_rg_f;
	Cmp3_file mp3_f;
	Cjpeg_file jpeg_f;
	Cogg_file ogg_f;
	Cpak_file pak_f;
	Cpal_file pal_f;
	Cpcx_file pcx_f;
	Cpng_file png_f;
	Criff_file riff_f;
	Cshp_dune2_file shp_dune2_f;
	Cshp_file shp_f;
	Cshp_ts_file shp_ts_f;
	Cst_file st_f;
	Ctext_file text_f;
	Ctga_file tga_f;
	Ctmp_file tmp_f;
	Ctmp_ra_file tmp_ra_f;
	Ctmp_ts_file tmp_ts_f;
	Cvoc_file voc_f;
	Cvqa_file vqa_f;
	Cvqp_file vqp_f;
	Cvxl_file vxl_f;
	Cw3d_file w3d_f;
	Cwsa_dune2_file wsa_dune2_f;
	Cwsa_file wsa_f;
	Cxcc_file xcc_f;
	Cxif_file xif_f;
	if (aud_f.load(data, m_size), aud_f.is_valid())
		ft = ft_aud;
	else if (big_f.load(data, m_size), big_f.is_valid())
		ft = ft_big;
	else if (bin_f.load(data, m_size), bin_f.is_valid())
		ft = ft_bin;
	else if (bink_f.load(data, m_size), bink_f.is_valid())
		ft = ft_bink;
	else if (bmp_f.load(data, m_size), bmp_f.is_valid())
		ft = ft_bmp;
	else if (csf_f.load(data, m_size), csf_f.is_valid())
		ft = ft_csf;
	else if (cps_f.load(data, m_size), cps_f.is_valid())
		ft = ft_cps;
	else if (dds_f.load(data, m_size), dds_f.is_valid())
		ft = ft_dds;
	else if (fnt_f.load(data, m_size), fnt_f.is_valid())
		ft = ft_fnt;
	else if (hva_f.load(data, m_size), hva_f.is_valid())
		ft = ft_hva;
	else if (mp3_f.load(data, m_size), mp3_f.is_valid())
		ft = ft_mp3;
	else if (jpeg_f.load(data, m_size), jpeg_f.is_valid())
		ft = ft_jpeg;
	else if (ogg_f.load(data, m_size), ogg_f.is_valid())
		ft = ft_ogg;
	else if (pal_f.load(data, m_size), pal_f.is_valid())
		ft = ft_pal;
	else if (pcx_f.load(data, m_size), pcx_f.is_valid())
		ft = ft_pcx;
	else if (png_f.load(data, m_size), png_f.is_valid())
		ft = ft_png;
	else if (riff_f.load(data, m_size), riff_f.is_valid())
	{
		Cavi_file avi_f;
		Cwav_file wav_f;
		avi_f.load(data, m_size);
		wav_f.load(data, m_size);
		if (avi_f.is_valid())
			ft = ft_avi;
		else if (wav_f.is_valid())
			ft = ft_wav;
		else
			ft = ft_riff;
	}
	else if (shp_dune2_f.load(data, m_size), shp_dune2_f.is_valid())
		ft = ft_shp_dune2;
	else if (shp_f.load(data, m_size), shp_f.is_valid())
		ft = ft_shp;
	else if (shp_ts_f.load(data, m_size), shp_ts_f.is_valid())
		ft = ft_shp_ts;
	else if (st_f.load(data, m_size), st_f.is_valid())
		ft = ft_st;
	else if (text_f.load(data, m_size), text_f.is_valid())
	{
		if (fast)
			ft = ft_text;
		else
		{
			Cvirtual_tfile tf;
			tf.load_data(data);
			Cnull_ini_reader ir;
			int error = 0;
			while (!error && !tf.eof())
			{
				error = ir.process_line(tf.read_line());
				if (tf.eof())
					error = 0;
			}
			if (!error && ir.is_valid())
			{
				if (!m_read_on_open && m_size != size)
				{
					size = m_size;
					if (read(data.write_start(size), size))
					{
						return ft_unknown;
					}
					seek(0);
				}
				Cart_ts_ini_reader ir;
				ir.fast(true);
				if (!ir.process(data) && ir.is_valid())
					ft = ft_art_ini_ts;
				else
				{
					Cmap_td_ini_reader ir;
					if (!ir.process(data) && ir.is_valid())
						ft = ft_map_td;
					else
					{
						Cmap_ra_ini_reader ir;
						if (!ir.process(data) && ir.is_valid())
							ft = ft_map_ra;
						else
						{
							Cmap_ts_ini_reader ir;
							ir.fast(true);
							if (!ir.process(data) && ir.is_valid())
								ft = ft_map_ts;
							else
							{
								Cpkt_ts_ini_reader ir;
								ir.fast(true);
								if (!ir.process(data) && ir.is_valid())
									ft = ft_pkt_ts;
								else
								{
									Crules_ts_ini_reader ir;
									ir.fast(true);
									if (!ir.process(data) && ir.is_valid())
										ft = ft_rules_ini_ts;
									else
									{
										Csound_ts_ini_reader ir;
										ir.fast(true);
										if (!ir.process(data) && ir.is_valid())
											ft = ft_sound_ini_ts;
										else
										{
											Ctheme_ts_ini_reader ir;
											if (!ir.process(data) && ir.is_valid())
												ft = ft_theme_ini_ts;
											else
												ft = ft_ini;
										}
									}
								}
							}
						}
					}
				}
			}
			else
				ft = ft_text;
		}
	}
	else if (tga_f.load(data, m_size), tga_f.is_valid())
		ft = ft_tga;
	else if (tmp_f.load(data, m_size), tmp_f.is_valid())
		ft = ft_tmp;
	else if (tmp_ra_f.load(data, m_size), tmp_ra_f.is_valid())
		ft = ft_tmp_ra;
	else if (tmp_ts_f.load(data, m_size), tmp_ts_f.is_valid())
		ft = ft_tmp_ts;
	else if (voc_f.load(data, m_size), voc_f.is_valid())
		ft = ft_voc;
	else if (vqa_f.load(data, m_size), vqa_f.is_valid())
		ft = ft_vqa;
	else if (vqp_f.load(data, m_size), vqp_f.is_valid())
		ft = ft_vqp;
	else if (vxl_f.load(data, m_size), vxl_f.is_valid())
		ft = ft_vxl;
	else if (wsa_dune2_f.load(data, m_size), wsa_dune2_f.is_valid())
		ft = ft_wsa_dune2;
	else if (wsa_f.load(data, m_size), wsa_f.is_valid())
		ft = ft_wsa;
	else if (xcc_f.load(data, m_size), xcc_f.is_valid())
	{
		switch (xcc_f.get_ft())
		{
		case xcc_ft_lmd:
			ft = ft_xcc_lmd;
			break;
		default:
			ft = ft_xcc_unknown;
		}
	}
	else if (xif_f.load(data, m_size), xif_f.is_valid())
		ft = ft_xif;
	else if (mix_f.load(data, m_size), mix_f.is_valid())
		ft = ft_mix;
	else if (mix_rg_f.load(data, m_size), mix_rg_f.is_valid())
		ft = ft_mix_rg;
	else if (pak_f.load(data, m_size), pak_f.is_valid())
		ft = ft_pak;
	else if (w3d_f.load(data, m_size), w3d_f.is_valid())
		ft = ft_w3d;
	return ft;
}
#endif
#endif

int Ccc_file::read()
{
	seek(0);
	return read(m_data.write_start(get_size()), get_size());
}

int Ccc_file::read(void* data, int size)
{
	if (get_p() < 0 || get_p() + size > get_size())
		return 1;
	if (get_data())
	{
		memcpy(data, m_data.data() + m_p, size);
		skip(size);
		return 0;
	}
	assert(is_open());
    int res = 0;
	if (m_mix_f)
    {
        m_mix_f->seek(m_offset + m_p);
        res = m_mix_f->read(data, size);
    }
    else
    {
        m_f.seek(m_p);
        res = m_f.read(data, size);
    }
    if (!res)
        skip(size);
    return res;
}

int Ccc_file::extract(const string& name)
{
	assert(is_open());
	if (get_data())
		return get_vdata().save(name);
	seek(0);
	Cfile32 f;
	int error = f.open_write(name);
	if (error)
		return error;
	Cvirtual_binary data;
	for (int size = get_size(); size; )
	{
		int cb_write = min(size, 1 << 20);
		if (error = read(data.write_start(cb_write), cb_write))
			return error;
		size -= cb_write;
	}
	return 0;
}

void Ccc_file::close()
{
	m_data.clear();
	m_f.close();
	m_is_open = false;
}
