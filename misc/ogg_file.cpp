#include "stdafx.h"
#include "ogg_file.h"

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"
#include "wav_file.h"

size_t null_read(void* ptr, size_t size, size_t nmemb, void* datasource)
{
	if (!size || !nmemb)
		return 0;
	Cogg_file& f = *reinterpret_cast<Cogg_file*>(datasource);
	nmemb = min<size_t>((f.get_size() - f.get_p()) / size, nmemb);
	assert(nmemb >= 0);
	int error = f.read(ptr, nmemb * size);
	assert(!error);
	return nmemb;
}

int null_seek(void* datasource, ogg_int64_t offset, int whence)
{
	Cogg_file& f = *reinterpret_cast<Cogg_file*>(datasource);
	switch (whence)
	{
	case SEEK_SET:
		f.seek(offset);
		break;
	case SEEK_CUR:
		f.skip(offset);
		break;
	case SEEK_END:
		f.seek(f.get_size() + offset);
		break;
	default:
		return 1;
	}
	return 0;
}

int null_close(void* datasource)
{
	return 0;
}

long null_tell(void* datasource)
{
	Cogg_file& f = *reinterpret_cast<Cogg_file*>(datasource);
	return f.get_p();
} 

static ov_callbacks cbs = 
{
	null_read,
	null_seek,
	null_close,
	null_tell
};

int Cogg_file::get_c_channels()
{
	OggVorbis_File vf;
	seek(0);
	if (ov_open_callbacks(this, &vf, NULL, 0, cbs) < 0) 
		return 0;
	int r = ov_info(&vf, -1)->channels;
	ov_clear(&vf);
	return r;
}

int Cogg_file::get_c_samples()
{
	OggVorbis_File vf;
	seek(0);
	if (ov_open_callbacks(this, &vf, NULL, 0, cbs) < 0) 
		return 0;
	int r = ov_pcm_total(&vf, -1);
	ov_clear(&vf);
	return r;
}

int Cogg_file::get_samplerate()
{
	OggVorbis_File vf;
	seek(0);
	if (ov_open_callbacks(this, &vf, NULL, 0, cbs) < 0) 
		return 0;
	int r = ov_info(&vf, -1)->rate;
	ov_clear(&vf);
	return r;
}

int Cogg_file::decode(Cvirtual_audio& audio)
{
	int error = 0;
	OggVorbis_File vf;
	seek(0);
	if (ov_open_callbacks(this, &vf, NULL, 0, cbs) < 0) 
		error = 0x100;
	else
	{		
		vorbis_info* vi = ov_info(&vf, -1);
		Cvirtual_binary b;
		char* w = reinterpret_cast<char*>(b.write_start(vi->channels * ov_pcm_total(&vf, -1) << 1));
		while (!error)
		{
			int current_section;
			int cb_read = ov_read(&vf, w, b.size(), 0, 2, 1, &current_section);
			if (!cb_read) 
				break;
			else if (cb_read < 0) 
				error = 1;
			else 
				w += cb_read;
		}
		if (!error)
			audio.load(b, b.size() / (vi->channels << 1), vi->rate, 2, vi->channels);
		ov_clear(&vf);
	}
	return error;
}
