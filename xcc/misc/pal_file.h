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
	int extract_as_pal_jasc(const string& name) const;

	bool is_valid() const
	{
		if (get_size() != sizeof(t_palet))
			return false;
		const t_palet& p = *get_palet();
		for (int i = 0; i < 256; i++)
		{
			if ((p[i].r | p[i].g | p[i].b) & 0xc0)
				return false;
		}
		return true;
	}

    const t_palet* get_palet() const
    {
        return reinterpret_cast<const t_palet*>(get_data());
    }
};

#endif // !defined(AFX_PAL_FILE_H__307FE924_D574_11D3_A718_0000F81AF8CC__INCLUDED_)
