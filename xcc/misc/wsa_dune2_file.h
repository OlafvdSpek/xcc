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
		if (sizeof(t_wsa_dune2_header) + 4 > size || header.c_frames < 1 || header.c_frames > 1000 || sizeof(t_wsa_dune2_header) + 4 * (get_header()->c_frames + 2) > size)
			return false;
		return get_offset(get_c_frames() + has_loop()) == size;
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

	/*
	int get_delta() const
	{
		return get_header()->delta;
	}
	*/

	const byte* get_frame(int i) const
	{
		return get_data() + get_offset(i);
	}

	int get_cb_ofs() const
	{
		return get_index16()[1] ? 2 : 4;
	}

	int get_ofs(int i) const
	{
		if (get_cb_ofs() == 2)
			return get_index16()[i];
		else
			return get_index32()[i];
	}

	const __int16* get_index16() const
	{
		return reinterpret_cast<const __int16*>(get_data() + sizeof(t_wsa_dune2_header));
	}

	const __int32* get_index32() const
	{
		return reinterpret_cast<const __int32*>(get_data() + sizeof(t_wsa_dune2_header));
	}

    int get_offset(int i) const
    {
		return get_ofs(i);
    }

	bool has_loop() const
	{
		return get_ofs(get_c_frames() + 1);
	}
};

#endif // !defined(AFX_WSA_DUNE2_FILE_H__4AE5F9E0_704F_11D4_B606_0000B4936994__INCLUDED_)
