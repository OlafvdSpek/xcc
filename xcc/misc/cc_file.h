// cc_file.h: interface for the Ccc_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CC_FILE_H__DB898AD2_D338_11D3_867E_0000F81AF605__INCLUDED_)
#define AFX_CC_FILE_H__DB898AD2_D338_11D3_867E_0000F81AF605__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "file32.h"
#include "virtual_binary.h"

enum t_file_type
{
	ft_ai_ini_ts, ft_ai_ini_ra2, ft_art_ini_ts, ft_art_ini_ra2, ft_aud, ft_avi, ft_bin, ft_bink, ft_bmp, ft_clipboard, ft_cps, ft_csv, ft_dds, ft_dir, ft_drive, ft_fnt, ft_html, ft_hva, ft_ini,
	ft_jpeg, ft_map_dune2, ft_map_td, ft_map_ra, ft_map_ts, ft_map_ts_preview, ft_map_ra2, ft_mix, ft_mix_rg, ft_mng, ft_mp3, ft_mrf, 
	ft_ogg, ft_pak, ft_pal, ft_pal_jasc, ft_pcx_single, ft_pcx, ft_png_single, ft_png, ft_pkt_ts, ft_riff, ft_rules_ini_ts, ft_rules_ini_ra2, ft_shp_dune2, ft_shp, ft_shp_ts, 
	ft_sound_ini_ts, ft_sound_ini_ra2, ft_st, ft_text, ft_theme_ini_ts, ft_theme_ini_ra2, ft_tmp, ft_tmp_ra, ft_tmp_ts, ft_voc, ft_vpl, ft_vqa, ft_vqp, ft_vxl, ft_w3d, ft_wav, 
	ft_wav_ima_adpcm, ft_wav_pcm, ft_wsa_dune2, ft_wsa, ft_xcc_lmd, ft_xcc_unknown, ft_xif, ft_zip, ft_unknown, ft_count
};

const char* ft_name[];

class Cmix_file;

class Ccc_file  
{
public:
	HANDLE handle();
	int attach(HANDLE handle);
	void detach();
    int open(unsigned int id, Cmix_file& mix_f);
    int open(const string& name, Cmix_file& mix_f);
    int open(const string& name);
	// void load(const byte* data, int size);
	void load(const Cvirtual_binary d, int size = -1);
	void load(const Ccc_file& f);
	t_file_type get_file_type(bool fast = true);
	int read();
    int read(void* data, int size);
	int extract(const string& name);
    virtual void close();
	Ccc_file(bool read_on_open);
	~Ccc_file();

    const byte* get_data() const
    {
        return m_data.data();
    }

    Cvirtual_binary get_vdata() const
    {
        return m_data;
    }

	int get_p() const
    {
        return m_p;
    }

    int get_size() const
	{
		return m_size;
	}

    bool is_attached() const
    {
        return m_attached;
    }

    bool is_open() const
    {
        return m_is_open;
    }

    void seek(int p)
    {
        m_p = p;
    }

    void skip(int p)
    {
        m_p += p;
    }

    virtual int post_open()
    {
        return 0;
    }
protected:
	bool m_data_loaded;
private:
    void clean_up();

	bool m_attached;
    Cvirtual_binary m_data;
    Cfile32 m_f;
    Cmix_file* m_mix_f;
    bool m_is_open;
    int m_offset;
    int m_p;
    const bool m_read_on_open;
    int m_size;
};

#endif // !defined(AFX_CC_FILE_H__DB898AD2_D338_11D3_867E_0000F81AF605__INCLUDED_)
