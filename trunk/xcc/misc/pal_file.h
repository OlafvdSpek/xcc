// pal_file.h: interface for the Cpal_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAL_FILE_H__307FE924_D574_11D3_A718_0000F81AF8CC__INCLUDED_)
#define AFX_PAL_FILE_H__307FE924_D574_11D3_A718_0000F81AF8CC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <cc_file_small.h>
#include <palet.h>

class Cpal_file: public Ccc_file_small
{
public:
	ostream& extract_as_pal_jasc(ostream&) const;
	bool is_valid() const;

	void decode(t_palet& palet) const
	{
		convert_palet_18_to_24(get_palet(), palet);
	}

    const t_palet_entry* get_palet() const
    {
        return reinterpret_cast<const t_palet_entry*>(get_data());
    }
};

#endif // !defined(AFX_PAL_FILE_H__307FE924_D574_11D3_A718_0000F81AF8CC__INCLUDED_)
