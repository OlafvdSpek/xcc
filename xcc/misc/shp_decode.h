#if !defined(AFX_SHP_DECODE_H__1C510AE3_D61B_11D2_99E5_FB3955DC2E06__INCLUDED_)
#define AFX_SHP_DECODE_H__1C510AE3_D61B_11D2_99E5_FB3955DC2E06__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "vartypes.h"

int decode2(const byte* s, byte* d, int cb_s);
int decode3(const byte* s, byte* d, int cx, int cy);
int encode3(const byte* s, byte* d, int cx, int cy);
int decode5(const byte* s, byte* d, int cb_s);
int encode5(const byte* s, byte* d, int cb_s);
int decode5s(const byte* s, byte* d, int cb_s);
int encode5s(const byte* s, byte* d, int cb_s);
int decode64(const byte* s, byte* d);
int encode64(const byte* s, byte* d, int cb_s);
int decode40(const byte image_in[], byte image_out[]);
int decode80(const byte image_in[], byte image_out[]);
int decode80c(const byte image_in[], byte image_out[], int cb_in);
int decode80r(const byte image_in[], byte image_out[]);
int encode40(const byte* last_s, const byte* s, byte* d, int cb_s);
int encode80(const byte* s, byte* d, int cb_s);
int get_run_length(const byte* r, const byte* s_end);

#endif // !defined(AFX_SHP_DECODE_H__1C510AE3_D61B_11D2_99E5_FB3955DC2E06__INCLUDED_)
