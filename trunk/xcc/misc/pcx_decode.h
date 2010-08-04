#pragma once

#include <cc_structures.h>

void pcx_decode(const byte* s, byte* d, const t_pcx_header& header);
int pcx_encode(const byte* s, byte* d, int cx, int cy, int c_planes);
