// avi_file.h: interface for the Cavi_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AVI_FILE_H__AB80E740_51B1_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_AVI_FILE_H__AB80E740_51B1_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "riff_file.h"

class Cavi_file: public Criff_file    
{
public:
	int process_chunk(const t_riff_header& header);
};

#endif // !defined(AFX_AVI_FILE_H__AB80E740_51B1_11D4_B606_0000B4936994__INCLUDED_)
