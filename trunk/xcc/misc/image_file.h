// image_file.h: interface for the Cimage_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_FILE_H__0D511341_D7FA_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_IMAGE_FILE_H__0D511341_D7FA_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "cc_file_sh.h"
#include "cc_structures.h"
#include "palet.h"
#include "virtual_file.h"

using namespace std;

class Cimage_file  
{
public:
};

int image_file_write(Cvirtual_file& f, t_file_type ft, const byte* image, const t_palet_entry* palet, int cx, int cy);
int image_file_write(const string& name, t_file_type ft, const byte* image, const t_palet_entry* palet, int cx, int cy);

#endif // !defined(AFX_IMAGE_FILE_H__0D511341_D7FA_11D4_A95D_0050042229FC__INCLUDED_)
