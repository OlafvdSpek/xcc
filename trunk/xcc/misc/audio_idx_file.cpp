// audio_idx_file.cpp: implementation of the Caudio_idx_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include "audio_idx_file.h"

int audio_idx_file_get_write_size(int c_sounds)
{
	return sizeof(t_audio_idx_header) + sizeof(t_audio_idx_entry) * c_sounds;
}

int audio_idx_file_write_header(void* w, int c_sounds)
{
	t_audio_idx_header& header = *reinterpret_cast<t_audio_idx_header*>(w);
	header.id = audio_idx_id;
	header.two = 2;
	header.c_sounds = c_sounds;
	return sizeof(t_audio_idx_header);
}

int audio_idx_file_write_entry(void* w, string fname, int offset, int size, int samplerate, int flags, int chunk_size)
{
	t_audio_idx_entry& entry = *reinterpret_cast<t_audio_idx_entry*>(w);
	assert(fname.length() < 16);
	strcpy(entry.fname, fname.c_str());
	entry.offset = offset;
	entry.size = size;
	entry.samplerate = samplerate;
	entry.flags = flags;
	entry.chunk_size = chunk_size;
	return sizeof(t_audio_idx_entry);
}
