// cc_file_small.h: interface for the Ccc_file_small class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CC_FILE_SMALL_H__307FE923_D574_11D3_A718_0000F81AF8CC__INCLUDED_)
#define AFX_CC_FILE_SMALL_H__307FE923_D574_11D3_A718_0000F81AF8CC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <cc_file.h>

class Ccc_file_small: public Ccc_file  
{
public:
	Ccc_file_small():
		Ccc_file(true)
	{
	}
};

#endif // !defined(AFX_CC_FILE_SMALL_H__307FE923_D574_11D3_A718_0000F81AF8CC__INCLUDED_)
