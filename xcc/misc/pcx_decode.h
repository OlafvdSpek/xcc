#if !defined(AFX_PCX_DECODE_H__335E3B20_CFFF_11D3_B604_0000B4936994__INCLUDED_)
#define AFX_PCX_DECODE_H__335E3B20_CFFF_11D3_B604_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cc_structures.h>
#include <vartypes.h>

void pcx_decode(const byte* s, byte* d, const t_pcx_header& header);
int pcx_encode(const byte* s, byte* d, int cx, int cy, int c_planes);

#endif // !defined(AFX_PCX_DECODE_H__335E3B20_CFFF_11D3_B604_0000B4936994__INCLUDED_)
