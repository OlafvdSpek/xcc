// xcc_file_sh.h: interface for the Cxcc_file_sh class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCC_FILE_SH_H__5C6F2864_FDAB_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_XCC_FILE_SH_H__5C6F2864_FDAB_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xcc_file.h"

template <class T>
class Cxcc_file_sh: public Cxcc_file
{
public:
    const T* get_header() const
    {
        return reinterpret_cast<const T*>(get_data() + sizeof(t_xcc_header));
    }
};

#endif // !defined(AFX_XCC_FILE_SH_H__5C6F2864_FDAB_11D3_B605_0000B4936994__INCLUDED_)
