#include "stdafx.h"
#include "wsa_file.h"

#include "image_file.h"
#include "shp_decode.h"
#include "string_conversion.h"

class Cwsa_decoder: public Cvideo_decoder
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
		return m_f.palet();
	}

	int seek(int f)
	{
		if (f == m_frame_i)
			return 0;
		for (m_frame_i = 0; m_frame_i < f && !decode(NULL); )
			;
		return 0;
	}

	Cwsa_decoder(const Cwsa_file& f)
	{
		m_f.load(f);
		m_frame_i = 0;
	}
private:
	Cwsa_file m_f;
	Cvirtual_binary m_frame;
	int m_frame_i;
};

Cvideo_decoder* Cwsa_file::decoder()
{
	return new Cwsa_decoder(*this);
}

bool Cwsa_file::is_valid() const
{
	const t_wsa_header& h = header();
	int size = get_size();
	if (sizeof(t_wsa_header) > size || h.c_frames < 1 || h.c_frames > 1000 || sizeof(t_wsa_header) + get_cb_index() > size)
		return false;
	if (get_offset(cf() + has_loop()) != size)
		return false;
	return true;
}

void Cwsa_file::decode(void* d) const
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

Cvirtual_image Cwsa_file::vimage() const
{
	Cvirtual_binary image;
	decode(image.write_start(cb_video()));
	return Cvirtual_image(image, cx(), cf() * cy(), cb_pixel(), palet(), true);
}
