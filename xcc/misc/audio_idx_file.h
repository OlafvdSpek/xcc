// audio_idx_file.h: interface for the Caudio_idx_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDIO_IDX_FILE_H__10CE2E06_B67A_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_AUDIO_IDX_FILE_H__10CE2E06_B67A_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_sh.h"
#include "cc_structures.h"

class Caudio_idx_file: public Ccc_file_sh<t_audio_idx_header>
{
public:
	bool is_valid() const
	{
		const t_audio_idx_header& header = *get_header();
		int size = get_size();
		return !(sizeof(t_audio_idx_header) > size || 
			header.id != audio_idx_id ||
			header.two != 2 ||
			sizeof(t_audio_idx_header) + sizeof(t_audio_idx_entry) * header.c_sounds != size);
	}

	int c_sounds() const
	{
		return get_header()->c_sounds;
	}

	const t_audio_idx_entry& sound_entry(int i) const
	{
		return reinterpret_cast<const t_audio_idx_entry*>(get_data() + sizeof(t_audio_idx_header))[i];
	}
};

int audio_idx_file_get_write_size(int c_sounds);
int audio_idx_file_write_header(void* w, int c_sounds);
int audio_idx_file_write_entry(void* w, string fname, int offset, int size, int samplerate, int flags, int chunk_size);

#endif // !defined(AFX_AUDIO_IDX_FILE_H__10CE2E06_B67A_11D4_B606_0000B4936994__INCLUDED_)
