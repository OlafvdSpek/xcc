// rml_file.h: interface for the Crml_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RML_FILE_H__D03FDA13_E0B0_4F0C_8A10_ECC872136663__INCLUDED_)
#define AFX_RML_FILE_H__D03FDA13_E0B0_4F0C_8A10_ECC872136663__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <virtual_binary.h>
#include "xif_key.h"

Cxif_key encode_rmlf(const string& fname, bool binary_diff_compression, bool tga_compression);
Cvirtual_binary decode_rmlf(const string& fname);

#endif // !defined(AFX_RML_FILE_H__D03FDA13_E0B0_4F0C_8A10_ECC872136663__INCLUDED_)
