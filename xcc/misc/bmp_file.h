// bmp_file.h: interface for the Cbmp_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMP_FILE_H__4DE458D0_601C_47B2_AD08_4C0F13358D8B__INCLUDED_)
#define AFX_BMP_FILE_H__4DE458D0_601C_47B2_AD08_4C0F13358D8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_small.h"

class Cbmp_file: public Ccc_file_small
{
public:
	bool is_valid() const;
};

#endif // !defined(AFX_BMP_FILE_H__4DE458D0_601C_47B2_AD08_4C0F13358D8B__INCLUDED_)
