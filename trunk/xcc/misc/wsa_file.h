// wsa_file.h: interface for the Cwsa_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WSA_FILE_H__9F7E1F31_D406_11D3_8684_0000F81AF605__INCLUDED_)
#define AFX_WSA_FILE_H__9F7E1F31_D406_11D3_8684_0000F81AF605__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "fname.h"
#include "palet.h"
#include "video_file.h"
#include "virtual_image.h"

class Cwsa_file: public Cvideo_file<t_wsa_header>
{
public:
	void decode(void* d) const;
	int extract_as_pcx(const Cfname& name, t_file_type ft) const;
	Cvirtual_image vimage() const;

	bool is_valid() const
	{
		const t_wsa_header& header = *get_header();
		int size = get_size();
		if (sizeof(t_wsa_header) > size || header.c_frames < 1 || header.c_frames > 1000 || sizeof(t_wsa_header) + get_cb_index() > size)
			return false;
		if (get_offset(cf() + has_loop()) != size)
			return false;
		return true;
	}

	int cb_pixel() const
	{
		return 1;
	}

	int cf() const
	{
		return get_header()->c_frames;
	}

	int cx() const
	{
		return get_header()->cx;
	}

	int cy() const
	{
		return get_header()->cy;
	}

	int get_x() const
	{
		return get_header()->x;
	}

	int get_y() const
	{
		return get_header()->y;
	}

	int get_delta() const
	{
		return get_header()->delta;
	}

    int get_cb_index() const
    {
        return 4 * (get_header()->c_frames + 2);
    }

	int get_cb_palet() const
	{
		return palet() ? sizeof(t_palet) : 0;
	}

	const byte* get_frame(int i) const
	{
		return get_data() + get_offset(i);
	}

    const int* get_index() const
    {
        return reinterpret_cast<const int*>(get_data() + sizeof(t_wsa_header));
    }

    int get_offset(int i) const
    {
		return get_index()[i] + get_cb_palet();
    }

    const t_palet_entry* palet() const
    {
        return get_index()[cf() + has_loop()] != get_size() 
			? reinterpret_cast<const t_palet_entry*>(get_data() + sizeof(t_wsa_header) + get_cb_index()) 
			: NULL;
    }

	bool has_loop() const
	{
		return get_index()[cf() + 1];
	}
};

#endif // !defined(AFX_WSA_FILE_H__9F7E1F31_D406_11D3_8684_0000F81AF605__INCLUDED_)
