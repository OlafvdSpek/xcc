// wsa_dune2_file.h: interface for the Cwsa_dune2_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WSA_DUNE2_FILE_H__4AE5F9E0_704F_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_WSA_DUNE2_FILE_H__4AE5F9E0_704F_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "fname.h"
#include "palet.h"

class Cwsa_dune2_file: public Ccc_file_sh<t_wsa_dune2_header>  
{
public:
	int extract_as_pcx(const Cfname& name, const t_palet _palet) const;

	bool is_valid() const
	{
		const t_wsa_dune2_header& header = *get_header();
		int size = get_size();
		if (sizeof(t_wsa_dune2_header) + 4 > size || header.c_frames < 1 || header.c_frames > 1000 || sizeof(t_wsa_dune2_header) + get_cb_index() > size)
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

	const byte* get_frame(int i) const
	{
		return get_data() + get_offset(i);
	}

    const int* get_index() const
    {
        return reinterpret_cast<const int*>(get_data() + sizeof(t_wsa_dune2_header));
    }

    int get_offset(int i) const
    {
		return get_index()[i];
    }

	bool has_loop() const
	{
		return get_index()[get_c_frames() + 1];
	}
};

#endif // !defined(AFX_WSA_DUNE2_FILE_H__4AE5F9E0_704F_11D4_B606_0000B4936994__INCLUDED_)
