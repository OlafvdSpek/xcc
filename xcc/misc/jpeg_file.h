// jpeg_file.h: interface for the Cjpeg_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JPEG_FILE_H__8F62B5C0_D730_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_JPEG_FILE_H__8F62B5C0_D730_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "cc_file_sh.h"
#include "cc_structures.h"
#include "palet.h"
#include "virtual_image.h"

using namespace std;

#pragma comment(lib, "libjpeg.lib")

class Cjpeg_file: public Ccc_file_sh<t_jpeg_header>
{
public:
	int decode(Cvirtual_image& d) const;
	Cjpeg_file();
	~Cjpeg_file();

	bool is_valid() const
	{
		return !(get_size() < sizeof(t_jpeg_header) || memcmp(get_header()->id, jpeg_id, 4));
	}
};

int jpeg_file_write(Cvirtual_file& f, const byte* image, const t_palet_entry* palet, int cx, int cy, int q = -1);
int jpeg_file_write(const string& name, const byte* image, const t_palet_entry* palet, int cx, int cy, int q = -1);

#endif // !defined(AFX_JPEG_FILE_H__8F62B5C0_D730_11D4_A95D_0050042229FC__INCLUDED_)
