// vqp_file.h: interface for the Cvqp_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VQP_FILE_H__2FC66020_06EE_11D4_B605_0000B4936994__INCLUDED_)
#define AFX_VQP_FILE_H__2FC66020_06EE_11D4_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #include "cc_file.h"
#include "cc_structures.h"

class Cvqp_file: public Ccc_file_sh<t_vqp_header>    
{
public:
	bool is_valid() const
	{
		const t_vqp_header& header = *get_header();
		int size = get_size();
		return !(sizeof(t_vqp_header) > size || 
			sizeof(t_vqp_header) + 32896 * header.c_tables != size);
	}
};

#endif // !defined(AFX_VQP_FILE_H__2FC66020_06EE_11D4_B605_0000B4936994__INCLUDED_)
