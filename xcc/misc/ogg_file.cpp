// ogg_file.cpp: implementation of the Cogg_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ogg_file.h"

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"
#include "wav_file.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cogg_file::Cogg_file()
{
}

Cogg_file::~Cogg_file()
{
}

#ifdef OGG_SUPPORT

size_t null_read(void *ptr, size_t size, size_t nmemb, void* datasource)
{
	return 0;
}

int null_seek(void* datasource, ogg_int64_t offset, int whence)
{
	return -1;
}

int null_close(void* datasource)
{
	return 0;
}

long null_tell(void* datasource)
{
	return -1;
} 

int ogg_test()
{
	int error = 0;
	FILE* g = fopen("c:/temp/bp.ogg", "rb");
	fseek(g, 0, SEEK_END);
	int cb_d = ftell(g);
	rewind(g);
	char* d = new char[cb_d];
	fread(d, 1, cb_d, g);
	fclose(g);
	FILE* f = tmpfile();
	OggVorbis_File vf;
	if (!f)
		error = 1;
	else
	{
		if (ov_open(f, &vf, d, cb_d) < 0)
			error = 0x100;
		else
		{		
			vorbis_info* vi = ov_info(&vf, -1);
			
			int cb_d = 4 << 20;
			byte* d = new byte[cb_d];
			byte* w = d;
			
			const int cb_b = 16 << 10;
			char b[cb_b];
			while (!error)
			{
				int current_section;
				int cb_read = ov_read(&vf, b, cb_b, 0, 2, 1, &current_section);
				if (!cb_read) 
					break;
				else if (cb_read < 0) 
					error = 1;
				else 
				{
					if (w - d + cb_read > cb_d)
					{
						cb_d <<= 1;
						byte* t = new byte[cb_d];
						memcpy(t, d, w - d);
						w = w - d + t;
						delete[] d;
						d = t;
					}
					memcpy(w, b, cb_read);
					w += cb_read;
				}
			}
			if (!error)
			{
				cb_d = w - d;
				// audio.load(d, cb_d / (vi->channels << 1), vi->rate, 2, vi->channels);
			}
			delete[] d;
			ov_clear(&vf);
		}
	}
	return error;
}

int Cogg_file::decode(Cvirtual_audio& audio)
{
	// ogg_test();
	int error = 0;
	ov_callbacks cbs;
	cbs.read_func = null_read;
	cbs.seek_func = null_seek;
	cbs.close_func = null_close;
	cbs.tell_func = null_tell;
	OggVorbis_File vf;
	{
		if (ov_open_callbacks(NULL, &vf, const_cast<char*>(reinterpret_cast<const char*>(get_data())), get_size(), cbs) < 0) 
			error = 0x100;
		else
		{		
			vorbis_info* vi = ov_info(&vf, -1);
			
			int cb_d = 4 << 20;
			byte* d = new byte[cb_d];
			byte* w = d;
			
			const int cb_b = 16 << 10;
			char b[cb_b];
			while (!error)
			{
				int current_section;
				int cb_read = ov_read(&vf, b, cb_b, 0, 2, 1, &current_section);
				if (!cb_read) 
					break;
				else if (cb_read < 0) 
					error = 1;
				else 
				{
					if (w - d + cb_read > cb_d)
					{
						cb_d <<= 1;
						byte* t = new byte[cb_d];
						memcpy(t, d, w - d);
						w = w - d + t;
						delete[] d;
						d = t;
					}
					memcpy(w, b, cb_read);
					w += cb_read;
				}
			}
			if (!error)
			{
				cb_d = w - d;
				audio.load(d, cb_d / (vi->channels << 1), vi->rate, 2, vi->channels);
			}
			delete[] d;
			ov_clear(&vf);
		}
	}
	return error;
}
#endif

