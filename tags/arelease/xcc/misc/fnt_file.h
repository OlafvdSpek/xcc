// fnt_file.h: interface for the Cfnt_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FNT_FILE_H__B17E6761_DC97_11D3_B604_0000B4936994__INCLUDED_)
#define AFX_FNT_FILE_H__B17E6761_DC97_11D3_B604_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cc_file_sh.h>
#include <cc_structures.h>

class Cfnt_file: public Ccc_file_sh<t_fnt_header>
{
public:
	bool is_valid() const
	{
		const t_fnt_header& header = *get_header();
		int size = get_size();
		if (sizeof(t_fnt_header) > size || 
			header.size != size ||
			header.id2 != 0x000e ||
			header.id3 != 0x0014 ||
			header.zero)
			return false;
		return get_version() == game_td ? 
			header.id1 == 0x0500 && header.id4 == 0x1012 : 
			header.id1 == 0x0002 && !header.id4;
	}

	t_game get_version() const
	{
		return get_header()->id1 == 0x0500 ? game_td : game_ts;
	}

	int get_c_chars() const
	{
		return get_header()->c_chars + 1;
	}

	int get_cmax_x() const
	{
		return get_header()->cmax_x;
	}

	int get_cy() const
	{
		return get_header()->cy;
	}

	int get_y(int i) const
	{
		return reinterpret_cast<const word*>(get_data() + get_header()->cy_ofs)[i] & 0xff;
	}

	int get_cx(int i) const
	{
		return (get_data() + get_header()->cx_ofs)[i];
	}

	int get_cy(int i) const
	{
		return reinterpret_cast<const word*>(get_data() + get_header()->cy_ofs)[i] >> 8;
	}

	const byte* get_image(int i) const
	{
		return get_data() + reinterpret_cast<const word*>(get_data() + sizeof(t_fnt_header))[i];
	}
};

#endif // !defined(AFX_FNT_FILE_H__B17E6761_DC97_11D3_B604_0000B4936994__INCLUDED_)
