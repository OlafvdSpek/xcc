#if !defined(AFX_CC_STRUCTURES_H__D7232160_169C_11D4_A955_0050042229FC__INCLUDED_)
#define AFX_CC_STRUCTURES_H__D7232160_169C_11D4_A955_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "palet.h"

enum t_game {game_td, game_ra, game_ts, game_dune2, game_dune2000, game_ra2, game_unknown};

const char* game_name[];

#pragma pack(push, 1)

struct t_aud_header
{
	unsigned __int16 samplerate;
	unsigned __int32 size_in;
	unsigned __int32 size_out;
	__int8 flags;
	__int8 compression;
};

struct t_aud_chunk_header
{
	unsigned __int16 size_in;
	unsigned __int16 size_out;
	__int32 id;
};

const __int32 aud_chunk_id = 0x0000deaf;

struct t_audio_idx_header
{
	__int32 id;
	__int32 two;
	__int32 c_sounds;
};

struct t_audio_idx_entry
{
	char fname[16];
	__int32 offset;
	__int32 size;
	__int32 samplerate;
	__int32 flags;
	__int32 chunk_size;
};

const __int32 audio_idx_id = *(__int32*)"GABA";

struct t_cps_header
{
	unsigned __int16 size;
	__int16 unknown;
	unsigned __int16 image_size;
	__int16 zero;
	__int16 palet_size;
};

struct t_csf_header
{
	__int32 id;
	__int32 flags1;
	__int32 count1;
	__int32 count2;
	__int32 zero;
	__int32 flags2;
};

const __int32 csf_file_id = 'CSF ';
const __int32 csf_label_id = 'LBL ';
const __int32 csf_string_id = 'STR ';
const __int32 csf_string_w_id = 'STRW';

struct t_fnt_header
{
	unsigned __int16 size;
	__int16 id1;
	__int16 id2;
	__int16 id3;
	unsigned __int16 cx_ofs;
	unsigned __int16 image_ofs;
	unsigned __int16 cy_ofs;
	__int16 id4;
	__int8 zero;
	unsigned __int8 c_chars;
	__int8 cy;
	__int8 cmax_x;
};

struct t_hva_header
{
	char id[16];
	__int32 c_frames;
	__int32 c_sections;
};

typedef float t_hva_transform_matrix[3][4];

union t_mix_header
{
	struct 
	{
		__int16 c_files;
		__int32 size;
	};
	__int32 flags;
};

const int mix_checksum = 0x00010000;
const int mix_encrypted = 0x00020000;
const int cb_mix_key = 56;
const int cb_mix_key_source = 80;
const int cb_mix_checksum = 20;

struct t_mix_index_entry
{
    unsigned __int32 id;
    __int32 offset;
    __int32 size;
};

struct t_iso_map_pack_entry
{
	unsigned __int16 x;
	unsigned __int16 y;
	unsigned __int16 ground;
	unsigned __int8 unknown1;
	unsigned __int8 unknown2;
	unsigned __int8 unknown3;
	unsigned __int8 height;
	unsigned __int8 unknown4;
};

struct t_pack_section_header
{
	unsigned __int16 size_in;
	unsigned __int16 size_out;
};

struct t_pcx_header
{
	__int8		manufacturer;
	__int8		version;
	__int8		encoding;
	__int8		cbits_pixel;
	__int16		xmin;
	__int16		ymin;
	__int16		xmax;
	__int16		ymax;
	__int16		cx_inch;
	__int16		cy_inch;
	__int8		colorpap[16][3];
	__int8		reserved;
	__int8		c_planes;
	__int16		cb_line;
	__int8		filler[60];
};

struct t_png_header
{
	__int8 id[8];
};

const char png_id[] = "\x89PNG\r\n\x1A\n";

struct t_shp_dune2_header
{
    __int16 c_images;
};

struct t_shp_dune2_image_header
{
	__int16 compression;
    unsigned __int8 cy;
    unsigned __int16 cx;
	unsigned __int8 cy2;
	unsigned __int16 size_in;
	unsigned __int16 size_out;
};

struct t_shp_header
{
    __int16 c_images;
    __int16 unknown1;
    __int16 unknown2;
    __int16 cx;
    __int16 cy;
    __int32 unknown3;
};

struct t_shp_ts_header
{
    __int16 zero;
    __int16 cx;
    __int16 cy;
    __int16 c_images;
};

struct t_shp_ts_image_header
{
	__int16 x;
	__int16 y;
    __int16 cx;
    __int16 cy;
    __int32 compression;
	__int32 unknown;
	__int32 zero;
	__int32 offset;
};

struct t_tmp_header
{
	__int16 cx;
	__int16 cy;
	__int16 c_tiles;
	__int16 zero1;
	__int32 size;
	__int32 image_offset;
	__int32 zero2;
	__int32 id;
	__int32 index2;
	__int32 index1;
};

struct t_tmp_ra_header
{
	__int16 cx;
	__int16 cy;
	__int16 c_tiles;
	__int16 zero1;
	__int16 cblocks_x;
	__int16 cblocks_y;
	__int32 size;
	__int32 image_offset;
	__int32 zero2;
	__int32 unknown1;
	__int32 index2;
	__int32 unknown2;
	__int32 index1;
};

struct t_tmp_ts_header
{
	__int32 cblocks_x;
	__int32 cblocks_y;
	__int32 cx;
	__int32 cy;
};

struct t_tmp_image_header
{
	__int32 x;
	__int32 y;
	__int32 unknown1[3];
	__int32 x_extra;
	__int32 y_extra;
	__int32 cx_extra;
	__int32 cy_extra;
	__int32 flags;
	__int8 height;
	__int8 terraintype;
	__int8 direction; // or probably just ramp_type
	__int8 unknown2;
	__int32 unknown3[2];
};

struct t_voc_header
{
	char id[20];
	__int16 offset;
	__int32 version;
};

struct t_voc_sound_data_header
{
	unsigned __int8 samplerate;
	__int8 compression;
};

const char voc_id[] = "Creative Voice File\x1a";

struct t_vqa_chunk_header
{
	__int32 id;
	__int32 size;
};

struct t_vqa_header
{
	t_vqa_chunk_header file_header;
	// 'FORM'
	__int64 id;
	// 'WVQAVQHD'
	__int32 startpos;
	__int16 version;
	__int16 video_flags;
	__int16 c_frames;
	__int16 cx;
	__int16 cy;
	__int8 cx_block;
	__int8 cy_block;
	__int16 unknown3;
	__int16 c_colors;
	__int16 cb_max_cbp_chunk;
	__int32 unknown4;
	__int16 unknown5;
	unsigned __int16 samplerate;
	__int8 c_channels;
	__int8 cbits_sample;
	__int8 unknown6[14];
};

const __int32 vqa_c_mask = 0xff000000;
const __int32 vqa_t_mask = 0x00ffffff;
const __int32 vqa_file_id = *(__int32*)"FORM";
const __int64 vqa_form_id = {*(__int64*)"WVQAVQHD"};
const __int32 vqa_cbf_id = *(__int32*)"CBF\0";
const __int32 vqa_cbp_id = *(__int32*)"CBP\0";
const __int32 vqa_cpl_id = *(__int32*)"CPL\0";
const __int32 vqa_finf_id = *(__int32*)"FINF";
const __int32 vqa_sn2j_id = *(__int32*)"SN2J";
const __int32 vqa_snd_id = *(__int32*)"SND\0";
const __int32 vqa_vpt_id = *(__int32*)"VPT\0";
const __int32 vqa_vpr_id = *(__int32*)"VPR\0";
const __int32 vqa_vqfl_id = *(__int32*)"VQFL";
const __int32 vqa_vqfr_id = *(__int32*)"VQFR";

struct t_vqp_header
{
    unsigned __int32 c_tables;
};

struct t_vxl_header
{
	char id[16];
	__int32 one;
	unsigned __int32 c_section_headers;
	unsigned __int32 c_section_tailers;
	unsigned __int32 size;
	__int16 unknown;
	t_palet palet;
};

struct t_vxl_section_header
{
	char id[16];
	__int32 section_i;
	__int32 one;
	__int32 zero;
};

struct t_vxl_section_tailer
{
    __int32 span_start_ofs;
    __int32 span_end_ofs;
    __int32 span_data_ofs;
	float scale;
	float transform[3][4];
	float x_min_scale;
	float y_min_scale;
	float z_min_scale;
	float x_max_scale;
	float y_max_scale;
	float z_max_scale;
	unsigned __int8 cx;
	unsigned __int8 cy;
	unsigned __int8 cz;
	__int8 unknown;
};

const char vxl_id[] = "Voxel Animation";

struct t_wsa_dune2_header
{
    __int16 c_frames;
    __int16 cx;
    __int16 cy;
	__int32 delta;
};

struct t_wsa_header
{
    __int16 c_frames;
    __int16 x;
    __int16 y;
    __int16 cx;
    __int16 cy;
    __int32 delta;
};

struct t_xcc_header
{
	char id[32];
	__int32 size;
	__int32 type;
	__int32 version;
};

const char xcc_id[] = "XCC by Olaf van der Spek\x1a\x04\x17\x27\x10\x19\x80";

struct t_xcc_lmd_header
{
	__int32 game;
	__int32 c_fnames;
};

#pragma pack(pop)

inline __int32 reverse(__int32 v)
{
	_asm
	{
		mov		eax, v
		xchg	al, ah
		rol		eax, 16
		xchg	al, ah
		mov		v, eax
	}
	return v;
}

#endif // !defined(AFX_CC_STRUCTURES_H__D7232160_169C_11D4_A955_0050042229FC__INCLUDED_)
