// hva_file.h: interface for the Chva_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HVA_FILE_H__B17E6760_DC97_11D3_B604_0000B4936994__INCLUDED_)
#define AFX_HVA_FILE_H__B17E6760_DC97_11D3_B604_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cc_file_sh.h>
#include <cc_structures.h>

class Chva_file: public Ccc_file_sh<t_hva_header>
{
public:
	int extract_as_csv(const string& name) const;
	bool is_valid() const;

	int get_c_frames() const
	{
		return get_header()->c_frames;
	}

	int get_c_sections() const
	{
		return get_header()->c_sections;
	}

	const char* get_section_id(int i) const
	{
		return reinterpret_cast<const char*>(get_data() + sizeof(t_hva_header) + 16 * i);
	}

	const float* get_transform_matrix(int i, int j) const
	{
		return reinterpret_cast<const float*>(get_data() + sizeof(t_hva_header) + 16 * get_c_sections() + (get_c_frames() * i + j) * sizeof(t_hva_transform_matrix));
	}
};

Cvirtual_binary hva_file_write(const byte* s, int cb_s);

#endif // !defined(AFX_HVA_FILE_H__B17E6760_DC97_11D3_B604_0000B4936994__INCLUDED_)
