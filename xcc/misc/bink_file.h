// bink_file.h: interface for the Cbink_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINK_FILE_H__9E041AC3_AF84_11D4_B606_E89F6F40146F__INCLUDED_)
#define AFX_BINK_FILE_H__9E041AC3_AF84_11D4_B606_E89F6F40146F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_small.h"

class Cbink_file: public Ccc_file_small
{
public:
	bool is_valid() const
	{
		int size = get_size();
		if (4 > size)
			return false;
		return *reinterpret_cast<const __int32*>(get_data()) == *reinterpret_cast<const __int32*>("BIKi");
	}
};

#endif // !defined(AFX_BINK_FILE_H__9E041AC3_AF84_11D4_B606_E89F6F40146F__INCLUDED_)
