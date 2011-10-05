#include "stdafx.h"
#include "wsa_dune2_file.h"

#include "image_file.h"
#include "shp_decode.h"
#include "string_conversion.h"

class Cwsa_dune2_decoder: public Cvideo_decoder
{
public:
	int cb_pixel() const
	{
		return m_f.cb_pixel();
	}

	int cf() const
	{
		return m_f.cf();
	}

	int cx() const
	{
		return m_f.cx();
	}

	int cy() const
	{
		return m_f.cy();
	}

	int decode(void* d)
	{
		if (m_frame_i >= cf())
			return 1;
		m_frame.write_start(cb_image());
		if (!m_frame_i)
			memset(m_frame.data_edit(), 0, cb_image());
		if (m_f.get_offset(m_frame_i))
		{
			Cvirtual_binary s;
			decode80(m_f.get_frame(m_frame_i), s.write_start(64 << 10));
			decode40(s.data(), m_frame.data_edit());
		}
		if (d)
			m_frame.read(d);
		m_frame_i++;
		return 0;
	}

	const t_palet_entry* palet() const
	{
		return m_palet;
	}

	int seek(int f)
	{
		if (f == m_frame_i)
			return 0;
		for (m_frame_i = 0; m_frame_i < f && !decode(NULL); )
			;
		return 0;
	}

	Cwsa_dune2_decoder(const Cwsa_dune2_file& f, const t_palet_entry* palet)
	{
		m_f.load(f);
		m_frame_i = 0;
		memcpy(m_palet, palet, sizeof(t_palet));
	}
private:
	Cwsa_dune2_file m_f;
	Cvirtual_binary m_frame;
	int m_frame_i;
	t_palet m_palet;
};

Cvideo_decoder* Cwsa_dune2_file::decoder(const t_palet_entry* palet)
{
	return new Cwsa_dune2_decoder(*this, palet);
}

int Cwsa_dune2_file::cb_pixel() const
{
	return 1;
}

int Cwsa_dune2_file::cf() const
{
	return header().c_frames;
}

int Cwsa_dune2_file::cx() const
{
	return header().cx;
}

int Cwsa_dune2_file::cy() const
{
	return header().cy;
}

/*
int Cwsa_dune2_file::get_delta() const
{
	return header().delta;
}
*/

const byte* Cwsa_dune2_file::get_frame(int i) const
{
	return get_data() + get_offset(i);
}

int Cwsa_dune2_file::get_cb_ofs() const
{
	return get_index16()[get_index16()[cf() + 1] ? cf() + 1 : cf()] == get_size() ? 2 : 4;
}

int Cwsa_dune2_file::get_offset(int i) const
{
	return get_cb_ofs() == 2 ? get_index16()[i] : get_index32()[i];
}

const __int16* Cwsa_dune2_file::get_index16() const
{
	return reinterpret_cast<const __int16*>(get_data() + sizeof(t_wsa_dune2_header));
}

const __int32* Cwsa_dune2_file::get_index32() const
{
	return reinterpret_cast<const __int32*>(get_data() + sizeof(t_wsa_dune2_header) + 2);
}

bool Cwsa_dune2_file::has_loop() const
{
	return get_offset(cf() + 1);
}


bool Cwsa_dune2_file::is_valid() const
{
	const t_wsa_dune2_header& h = header();
	int size = get_size();
	if (sizeof(t_wsa_dune2_header) + 4 > size || h.c_frames < 1 || h.c_frames > 1000 || sizeof(t_wsa_dune2_header) + 4 * (h.c_frames + 2) > size)
		return false;
	return get_offset(cf() + has_loop()) == size;
}

void Cwsa_dune2_file::decode(void* d) const
{
	memset(d, 0, cb_image());
	Cvirtual_binary s;
	byte* w = reinterpret_cast<byte*>(d);
	for (int i = 0; i < cf(); i++)
	{
		if (i)
			memcpy(w, w - cb_image(), cb_image());
		if (get_offset(i))
		{
			decode80(get_frame(i), s.write_start(64 << 10));
			decode40(s.data(), w);
		}
		w += cb_image();
	}
}

Cvirtual_image Cwsa_dune2_file::vimage() const
{
	Cvirtual_binary image;
	decode(image.write_start(cb_video()));
	return Cvirtual_image(image, cx(), cf() * cy(), cb_pixel(), palet(), true);
}

int Cwsa_dune2_file::extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet _palet) const
{
	t_palet palet;
	convert_palet_18_to_24(_palet, palet);
	Cvirtual_binary frame;
	Cvirtual_binary s;
	memset(frame.write_start(cb_image()), 0, cb_image());
	Cfname t = name;
	for (int i = 0; i < cf(); i++)
	{
		if (get_offset(i))
		{
			decode80(get_frame(i), s.write_start(64 << 10));
			decode40(s.data(), frame.data_edit());
		}
		t.set_title(name.get_ftitle() + " " + nwzl(4, i));
		if (int error = image_file_write(t, ft, frame.data(), palet, cx(), cy()))
			return error;
	}
	return 0;
}