// wav_header.h: interface for the wav_header class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAV_HEADER_H__7BAA68C3_CBCF_11D2_99E5_AC7708C14908__INCLUDED_)
#define AFX_WAV_HEADER_H__7BAA68C3_CBCF_11D2_99E5_AC7708C14908__INCLUDED_

#include "wav_structures.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

void wav_fill_header(t_wav_header &header, long samplesize, long samplerate, long cbits_sample, long c_channels);

#endif // !defined(AFX_WAV_HEADER_H__7BAA68C3_CBCF_11D2_99E5_AC7708C14908__INCLUDED_)
