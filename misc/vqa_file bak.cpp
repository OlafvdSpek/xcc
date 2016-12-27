#include "stdafx.h"
#include <vector>
#include <vfw.h>
#include "pcx_decode.h"
#include "pcx_file_write.h"
#include "string_conversion.h"
#include "vqa_decode.h"
#include "vqa_file.h"
#include "wav_structures.h"

int Cvqa_file::post_open()
{
	int error;
	error = read(&m_header, sizeof(t_vqa_header));
	if (!error)
		error = read_chunk_header();
	return error;
}

int Cvqa_file::extract_as_avi(const string& name)
{
	int error = 0;
	Cvqa_decode vqa_d;
	vqa_d.start_decode(header());
	int cx = get_cx();
	int cy = get_cy();
	AVIFileInit();
	PAVIFILE f;
	if (AVIFileOpen(&f, name.c_str(), OF_CREATE | OF_WRITE, NULL))
		error = 1;
	else
	{
		PAVISTREAM v;
		AVISTREAMINFO vi;
		memset(&vi, 0, sizeof(AVISTREAMINFO));
		vi.fccType = streamtypeVIDEO; 
		vi.fccHandler = 0; 
		vi.dwFlags = 0; 
		vi.dwScale = 1; 
		vi.dwRate = 15; 
		vi.dwLength = get_c_frames();
		SetRect(&vi.rcFrame, 0, 0, cx, cy);
		if (AVIFileCreateStream(f, &v, &vi))
			error = 2;
		else
		{	
			AVICOMPRESSOPTIONS* vco = new AVICOMPRESSOPTIONS;
			PAVISTREAM vc;
			if (!AVISaveOptions(AfxGetMainWnd()->m_hWnd, 0, 1, &v, &vco))
				error = 5;
			else 
			{
				if (AVIMakeCompressedStream(&vc, v, vco, NULL))
					error = 6;
				else				
				{
					BITMAPINFOHEADER vf;
					memset(&vf, 0, sizeof(BITMAPINFOHEADER));
					vf.biSize = sizeof(BITMAPINFOHEADER); 
					vf.biWidth = cx; 
					vf.biHeight = -cy; 
					vf.biPlanes = 1;
					vf.biBitCount = get_cbits_pixel() == 8 ? 8 : 24;
					vf.biCompression = BI_RGB ;
					vf.biSizeImage = 0; 
					if (AVIStreamSetFormat(vc, 0, &vf, sizeof(BITMAPINFOHEADER)))
						error = 3;
					else if (get_cbits_pixel() == 8)
					{
						t_palet palet;
						byte* frame = new byte[cx * cy];
						for (int i = 0; i < get_c_frames(); i++)
						{
							while (!is_video_chunk())
								skip_chunk();
							int cb_data = get_chunk_size();
							byte* data = new byte[cb_data];
							read_chunk(data);
							vqa_d.decode_vqfr_chunk(data, frame, palet);
							delete[] data;
							if (AVIStreamWrite(vc, i, 1, frame, cx * cy, 0, NULL, NULL))
							{
								error = 4;
								break;
							}
						}
						delete[] frame;
					}
					else
					{
						DDPIXELFORMAT pf;
						pf.dwRGBAlphaBitMask = 0;
						pf.dwRBitMask = 0xff0000;
						pf.dwGBitMask = 0x00ff00;
						pf.dwBBitMask = 0x0000ff;
						vqa_d.set_pf(pf, 3);
						byte* frame = new byte[3 * cx * cy];
						for (int i = 0; i < get_c_frames(); i++)
						{
							if (get_chunk_id() == vqa_vqfl_id)
							{
								int cb_data = get_chunk_size();
								byte* data = new byte[cb_data];
								read_chunk(data);
								vqa_d.decode_vqfl_chunk(data, cb_data);
								delete[] data;
							}
							while (!is_video_chunk())
								skip_chunk();
							int cb_data = get_chunk_size();
							byte* data = new byte[cb_data];
							read_chunk(data);
							vqa_d.decode_vqfr_chunk(data, frame, NULL);
							delete[] data;
							if (AVIStreamWrite(vc, i, 1, frame, 3 * cx * cy, 0, NULL, NULL))
							{
								error = 4;
								break;
							}
						}
						delete[] frame;
					}
					AVIStreamRelease(vc);
				}
				AVISaveOptionsFree(1, &vco);
				delete vco;
			}
			AVIStreamRelease(v);
		}
		AVIFileRelease(f);
	}
	AVIFileExit();
	return error;
}

int Cvqa_file::extract_as_pcx(const Cfname& name)
{
	int error = 0;
	Cvqa_decode vqa_d;
	vqa_d.start_decode(header());
	int cx = get_cx();
	int cy = get_cy();
	if (get_cbits_pixel() == 8)
	{
		t_palet palet;
		byte* frame = new byte[cx * cy];
		byte* d = new byte[2 * cx * cy];
		for (int i = 0; i < get_c_frames(); i++)
		{
			while (!is_video_chunk())
				skip_chunk();
			int cb_data = get_chunk_size();
			byte* data = new byte[cb_data];
			read_chunk(data);
			vqa_d.decode_vqfr_chunk(data, frame, palet);
			delete[] data;
			int cb_d = pcx_encode(frame, d, cx, cy, 1);
			Cpcx_file_write f;
			Cfname t = name;
			t.set_title(name.get_ftitle() + " " + nwzl(4, i));
			error = f.open_write(t);
			if (error)
				break;
			f.set_size(get_cx(), get_cy(), 1);
			error = f.write_header();
			if (!error)
				error = f.write_image(d, cb_d);
			if (!error)
				error = f.write_palet(palet);
			f.close();
			if (error)
				break;
		}
		delete[] d;
		delete[] frame;
	}
	else
	{
		DDPIXELFORMAT pf;
		pf.dwRGBAlphaBitMask = 0;
		pf.dwRBitMask = 0x0000ff;
		pf.dwGBitMask = 0x00ff00;
		pf.dwBBitMask = 0xff0000;
		vqa_d.set_pf(pf, 3);
		byte* frame = new byte[3 * cx * cy];
		byte* d = new byte[6 * cx * cy];
		for (int i = 0; i < get_c_frames(); i++)
		{
			if (get_chunk_id() == vqa_vqfl_id)
			{
				int cb_data = get_chunk_size();
				byte* data = new byte[cb_data];
				read_chunk(data);
				vqa_d.decode_vqfl_chunk(data, cb_data);
				delete[] data;
			}
			while (!is_video_chunk())
				skip_chunk();
			int cb_data = get_chunk_size();
			byte* data = new byte[cb_data];
			read_chunk(data);
			vqa_d.decode_vqfr_chunk(data, frame, NULL);
			delete[] data;
			int cb_d = pcx_encode(frame, d, cx, cy, 3);
			Cpcx_file_write f;
			Cfname t = name;
			t.set_title(name.get_ftitle() + " " + nwzl(4, i));
			error = f.open_write(t);
			if (error)
				break;
			f.set_size(get_cx(), get_cy(), 3);
			error = f.write_header();
			if (!error)
				error = f.write_image(d, cb_d);
			f.close();
			if (error)
				break;
		}
		delete[] d;
		delete[] frame;
	}
	return error;
}

struct t_list_entry
{
	int c_samples;
	short* audio;
};

int Cvqa_file::extract_as_wav(const string& name)
{
	int error = 0;
	typedef vector<t_list_entry> t_list;
	t_list list;
	int cs_remaining = 0;	
	Cvqa_decode vqa_d;
	vqa_d.start_decode(header());
	for (int i = 0; i < get_c_frames(); i++)
	{
		while (1)
		{
			if (is_audio_chunk())
			{
				t_list_entry e;
				int size = get_chunk_size();
				if (get_chunk_id() >> 24 == '0')
				{
					e.c_samples = size >> 1;
					e.audio = new short[size / 2];
					read_chunk(e.audio);
					size /= 4;
				}
				else
				{
					e.c_samples = size << 1;
					e.audio = new short[2 * size];
					byte* aud_in = new byte[size];
					read_chunk(aud_in);
					vqa_d.decode_snd2_chunk(aud_in, size, e.audio);
					delete[] aud_in;
				}
				cs_remaining += e.c_samples;
				list.push_back(e);				
			}
			else if (is_video_chunk())
				break;				
			else
				skip_chunk();
		}
		skip_chunk();
	}
	Cfile32 f;
	error = f.open(name, GENERIC_WRITE);
	if (!error)
	{
		t_wav_header header;
		memset(&header, 0, sizeof(t_wav_header));
		header.file_header.id = wav_file_id;
		header.file_header.size = sizeof(header) - sizeof(header.file_header) + cs_remaining;
		header.form_type = wav_form_id;
		header.format_chunk.header.id = wav_format_id;
		header.format_chunk.header.size = sizeof(header.format_chunk) - sizeof(header.format_chunk.header);
		header.format_chunk.formattag = 1;
		header.format_chunk.c_channels = get_c_channels();
		header.format_chunk.samplerate = get_samplerate();
		header.format_chunk.byterate = 2 * get_c_channels() * get_samplerate();
		header.format_chunk.blockalign = 2 * get_c_channels();
		header.format_chunk.cbits_sample = 16;
		header.data_chunk_header.id = wav_data_id;
		header.data_chunk_header.size = cs_remaining << 1;
		error = f.write(&header, sizeof(t_wav_header));
		if (!error)
		{
			for (t_list::iterator i = list.begin(); i != list.end(); i++)
			{
				f.write(i->audio, 2 * i->c_samples);
				delete[] i->audio;
			}
		}
		f.close();
	}
	return error;
}

int Cvqa_file::read_chunk_header()
{
	int error;
	if (get_p() & 1)
		skip(1);
	error = read(&m_chunk_header, sizeof(t_vqa_chunk_header));
	m_chunk_header.size = reverse(m_chunk_header.size);
	return error;
}

int Cvqa_file::read_chunk(void* data)
{
	int error;
	error = read(data, get_chunk_size());
	if (!error)
		read_chunk_header();	
	return error;
}

void Cvqa_file::set_empty_chunk()
{
	m_chunk_header.size = 0;
}

int Cvqa_file::skip_chunk()
{
	skip(get_chunk_size());
	return read_chunk_header();	
}