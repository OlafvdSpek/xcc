#pragma once

#include <virtual_binary.h>

int decode2(const byte* s, byte* d, int cb_s, const byte* reference_palet);
int decode3(const byte* s, byte* d, int cx, int cy);
int encode3(const byte* s, byte* d, int cx, int cy);
int decode5(const byte* s, byte* d, int cb_s, int format);
int encode5(const byte* s, byte* d, int cb_s, int format);
int decode5s(const byte* s, byte* d, int cb_s);
int encode5s(const byte* s, byte* d, int cb_s);
int decode64(const byte* s, byte* d);
Cvirtual_binary decode64(const_memory_range);
Cvirtual_binary encode64(const_memory_range);
int decode40(const byte image_in[], byte image_out[]);
int decode80(const byte image_in[], byte image_out[]);
int decode80c(const byte image_in[], byte image_out[], int cb_in);
int decode80r(const byte image_in[], byte image_out[]);
int encode40(const byte* last_s, const byte* s, byte* d, int cb_s);
int encode80(const byte* s, byte* d, int cb_s);
int get_run_length(const byte* r, const byte* s_end);
