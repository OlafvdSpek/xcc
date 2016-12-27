#pragma once

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
		return get_size() >= 4 && *reinterpret_cast<const __int32*>(data()) == ' SDD';
	}

	const DDSURFACEDESC2& ddsd() const
	{
		return *reinterpret_cast<const DDSURFACEDESC2*>(data() + 4);
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
