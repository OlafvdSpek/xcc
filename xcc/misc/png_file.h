// png_file.h: interface for the Cpng_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PNG_FILE_H__B98B88C0_BBF8_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_PNG_FILE_H__B98B88C0_BBF8_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "cc_file_sh.h"
#include "cc_structures.h"
#include "palet.h"
#include "virtual_image.h"

using namespace std;

class Cpng_file: public Ccc_file_sh<t_png_header>
{
public:
	int decode(Cvirtual_image& d) const;

	bool is_valid() const
	{
		return !(get_size() < sizeof(t_png_header) || memcmp(get_header(), png_id, sizeof(t_png_header)));
	}
};

int png_file_write(Cvirtual_file& f, const byte* image, const t_palet_entry* palet, int cx, int cy);
int png_file_write(const string& name, const byte* image, const t_palet_entry* palet, int cx, int cy);

#endif // !defined(AFX_PNG_FILE_H__B98B88C0_BBF8_11D4_B606_0000B4936994__INCLUDED_)
