// vxl_file.h: interface for the Cvxl_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VXL_FILE_H__C1E67081_DBD8_11D3_B604_0000B4936994__INCLUDED_)
#define AFX_VXL_FILE_H__C1E67081_DBD8_11D3_B604_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "fname.h"
#ifndef NO_XIF_SUPPORT
#include "xif_key.h"
#endif

class Cvxl_file: public Ccc_file_sh<t_vxl_header>
{
public:
	int extract_as_pcx(const Cfname& name, const t_palet _palet) const;
	int extract_as_xif(const string& name) const;
	
	bool is_valid() const
	{
 		int size = get_size();
		const t_vxl_header& header = *get_header();
		if (sizeof(t_vxl_header) > size ||
			strcmp(header.id, vxl_id) ||
			header.one != 1 ||
			header.c_section_headers != header.c_section_tailers ||
			header.size != size - sizeof(t_vxl_header) - header.c_section_headers * sizeof(t_vxl_section_header) - header.c_section_tailers * sizeof(t_vxl_section_tailer) ||
			header.unknown != 0x1f10)
			return false;
		/*
		for (int i = 0; i < header.c_section_headers; i++)
		{
			const t_vxl_section_header& section_header = *get_section_header(i);
			const t_vxl_section_tailer& section_tailer = *get_section_tailer(i);
			if (section_header.one != 1 ||
				section_header.zero ||
				section_tailer.span_end_ofs - section_tailer.span_start_ofs != section_tailer.span_data_ofs - section_tailer.span_end_ofs)
				return false;			
		}
		*/
		return true;
	}

	int get_c_section_headers() const
	{
		return get_header()->c_section_headers;
	}

	int get_c_spans(int i) const
	{
		return get_section_tailer(i)->span_end_ofs - get_section_tailer(i)->span_start_ofs >> 2;
	}

	int get_c_section_tailers() const
	{
		return get_header()->c_section_tailers;
	}

	const t_palet_entry* get_palet() const
	{
		return get_header()->palet;
	}

	const byte* get_section_body() const
	{
		return get_data() + sizeof(t_vxl_header) + sizeof(t_vxl_section_header) * get_c_section_tailers();
	}

	const t_vxl_section_header* get_section_header(int i) const
	{
		return reinterpret_cast<const t_vxl_section_header*>(get_data() + sizeof(t_vxl_header) + sizeof(t_vxl_section_header) * i);
	}

	const t_vxl_section_tailer* get_section_tailer(int i) const
	{
		return reinterpret_cast<const t_vxl_section_tailer*>(get_data() + get_size() + sizeof(t_vxl_section_tailer) * (i - get_c_section_tailers()));
	}

	const byte* get_span_data(int i, int j) const
	{
		if (get_span_start_list(i)[j] == -1)
			return NULL;
		return get_section_body() + get_section_tailer(i)->span_data_ofs + get_span_start_list(i)[j];
	}

	int get_span_size(int i, int j) const
	{
		return get_span_end_list(i)[j] - get_span_start_list(i)[j] + 1;
	}

	const int* get_span_start_list(int i) const
	{
		return reinterpret_cast<const int*>(get_section_body() + get_section_tailer(i)->span_start_ofs);
	}

	const int* get_span_end_list(int i) const
	{
		return reinterpret_cast<const int*>(get_section_body() + get_section_tailer(i)->span_end_ofs);
	}
};

#ifndef NO_XIF_SUPPORT
int vxl_file_write(const byte* s, byte* d, int cx, int cy, int cz);
int vxl_file_write(const Cxif_key& s, byte* d);
#endif

#endif // !defined(AFX_VXL_FILE_H__C1E67081_DBD8_11D3_B604_0000B4936994__INCLUDED_)
