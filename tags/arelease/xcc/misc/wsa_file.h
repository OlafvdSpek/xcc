// wsa_file.h: interface for the Cwsa_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WSA_FILE_H__9F7E1F31_D406_11D3_8684_0000F81AF605__INCLUDED_)
#define AFX_WSA_FILE_H__9F7E1F31_D406_11D3_8684_0000F81AF605__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <cc_file_sh.h>
#include <cc_structures.h>
#include <palet.h>
#include "fname.h"

class Cwsa_file: public Ccc_file_sh<t_wsa_header>
{
public:
	int extract_as_pcx(const Cfname& name) const;

	bool is_valid() const
	{
		const t_wsa_header& header = *get_header();
		int size = get_size();
		if (sizeof(t_wsa_header) > size || header.c_frames < 1 || header.c_frames > 1000 || sizeof(t_wsa_header) + get_cb_index() > size)
			return false;
		int c_frames = get_c_frames();
		if (has_loop())
		{ 
			if (get_offset(c_frames + 1) != size)
				return false;
		}
		else if (get_offset(c_frames) != size)
			return false;
		return true;
	}

	int get_c_frames() const
	{
		return get_header()->c_frames;
	}

	int get_x() const
	{
		return get_header()->x;
	}

	int get_y() const
	{
		return get_header()->y;
	}

	int get_cx() const
	{
		return get_header()->cx;
	}

	int get_cy() const
	{
		return get_header()->cy;
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
		return has_palet() ? sizeof(t_palet) : 0;
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

    const t_palet_entry* get_palet() const
    {
        return reinterpret_cast<const t_palet_entry*>(get_data() + sizeof(t_wsa_header) + get_cb_index());
    }

	bool has_loop() const
	{
		return get_index()[get_c_frames() + 1];
	}

	bool has_palet() const
	{
		return get_index()[get_c_frames() + has_loop()] != get_size();
	}
};

#endif // !defined(AFX_WSA_FILE_H__9F7E1F31_D406_11D3_8684_0000F81AF605__INCLUDED_)
