// dds_file.h: interface for the Cdds_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDS_FILE_H__9BF3E0A0_32BC_11D6_B861_0000B4936994__INCLUDED_)
#define AFX_DDS_FILE_H__9BF3E0A0_32BC_11D6_B861_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ddraw.h>
#include "cc_file_small.h"
#include "virtual_image.h"

class Cdds_file: public Ccc_file_small
{
public:
	Cvirtual_binary decode() const;
	Cvirtual_image vimage() const;

	bool is_valid() const
	{
		return get_size() >= 4 && *reinterpret_cast<const __int32*>(get_data()) == ' SDD';
	}

	const DDSURFACEDESC2& ddsd() const
	{
		return *reinterpret_cast<const DDSURFACEDESC2*>(get_data() + 4);
	}

	int cx() const
	{
		return ddsd().dwWidth;
	}

	int cy() const
	{
		return ddsd().dwHeight;
	}

	const byte* image() const
	{
		return reinterpret_cast<const byte*>(&ddsd() + 1);
	}	
};

#endif // !defined(AFX_DDS_FILE_H__9BF3E0A0_32BC_11D6_B861_0000B4936994__INCLUDED_)
