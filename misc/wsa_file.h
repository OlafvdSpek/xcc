#pragma once

#include "cc_structures.h"
#include "fname.h"
#include "palet.h"
#include "video_file.h"
#include "virtual_image.h"

class Cwsa_file: public Cvideo_file<t_wsa_header>
{
public:
	void decode(void* d) const;
	Cvideo_decoder* decoder();
	bool is_valid() const;
	Cvirtual_image vimage() const;

	int cb_pixel() const
	{
		return 1;
	}

	int cf() const
	{
		return header().c_frames;
	}

	int cx() const
	{
		return header().cx;
	}

	int cy() const
	{
		return header().cy;
	}

	int get_x() const
	{
		return header().x;
	}

	int get_y() const
	{
		return header().y;
	}

	int get_delta() const
	{
		return header().delta;
	}

    int get_cb_index() const
    {
        return 4 * (header().c_frames + 2);
    }

	int get_cb_palet() const
	{
		return palet() ? sizeof(t_palet) : 0;
	}

	const byte* get_frame(int i) const
	{
		return data() + get_offset(i);
	}

    const int* get_index() const
    {
        return reinterpret_cast<const int*>(data() + sizeof(t_wsa_header));
    }

    int get_offset(int i) const
    {
		return get_index()[i] + get_cb_palet();
    }

    const t_palet_entry* palet() const
    {
        return get_index()[cf() + has_loop()] != get_size() 
			? reinterpret_cast<const t_palet_entry*>(data() + sizeof(t_wsa_header) + get_cb_index()) 
			: NULL;
    }

	bool has_loop() const
	{
		return get_index()[cf() + 1];
	}
};
