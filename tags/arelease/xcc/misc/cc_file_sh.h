// cc_file_sh.h: interface for the Ccc_file_sh class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CC_FILE_SH_H__F2C6DDC1_D33C_11D3_867E_0000F81AF605__INCLUDED_)
#define AFX_CC_FILE_SH_H__F2C6DDC1_D33C_11D3_867E_0000F81AF605__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <cc_file_small.h>

template <class T>
class Ccc_file_sh: public Ccc_file_small
{
public:
    const T* get_header() const
    {
        return reinterpret_cast<const T*>(get_data());
    }
};

#endif // !defined(AFX_CC_FILE_SH_H__F2C6DDC1_D33C_11D3_867E_0000F81AF605__INCLUDED_)
