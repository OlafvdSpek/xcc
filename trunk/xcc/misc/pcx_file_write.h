// pcx_file_write.h: interface for the Cpcx_file_write class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCX_FILE_WRITE_H__3B5769C0_FC3F_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_PCX_FILE_WRITE_H__3B5769C0_FC3F_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_structures.h"
#include "file32.h"
#include "palet.h"

class Cpcx_file_write: public Cfile32  
{
public:
	void set_size(int cx, int cy, int c_planes);
	int write_header();
	int write_image(const void* data, int size);
	int write_palet(const t_palet palet);
private:
	int m_cx;
	int m_cy;
	int mc_planes;
};

int pcx_file_write(const string& name, const byte* image, t_palet_entry* paletn, int cx, int cy);

#endif // !defined(AFX_PCX_FILE_WRITE_H__3B5769C0_FC3F_11D3_B605_0000B4936994__INCLUDED_)
