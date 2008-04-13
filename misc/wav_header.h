#pragma once

#include "wav_structures.h"

void wav_fill_header(t_wav_header& header, int samplesize, int samplerate, int cbits_sample, int c_channels);
