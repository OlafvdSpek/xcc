// wsa_dune2_file.h: interface for the Cwsa_dune2_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WSA_DUNE2_FILE_H__4AE5F9E0_704F_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_WSA_DUNE2_FILE_H__4AE5F9E0_704F_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "fname.h"
#include "palet.h"
#include "video_file.h"
#include "virtual_image.h"

class Cwsa_dune2_file: public Cvideo_file<t_wsa_dune2_header>  
{
public:
	void decode(void* d) const;
	int extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet _palet) const;
	bool is_valid() const;
	Cvirtual_image vimage() const;
	int cb_pixel() const;
	int cf() const;
	int cx() const;
	int cy() const;
	const byte* get_frame(int i) const;
	int get_offset(int i) const;
	bool has_loop() const;
private:
	int get_cb_ofs() const;
	const __int16* get_index16() const;
	const __int32* get_index32() const;
};

#endif // !defined(AFX_WSA_DUNE2_FILE_H__4AE5F9E0_704F_11D4_B606_0000B4936994__INCLUDED_)
