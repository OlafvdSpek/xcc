// riff_file.h: interface for the Criff_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIFF_FILE_H__310B5360_F770_11D3_B605_0000B4936994__INCLUDED_)
#define AFX_RIFF_FILE_H__310B5360_F770_11D3_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file.h"
#include "riff_structures.h"

class Criff_file: public Ccc_file
{
public:
	virtual int process();
	virtual int process_chunk(const t_riff_header& header);

	bool is_valid()
	{
		m_validating = true;
		int error = process();
		m_validating = false;
		return !error;
	}

	Criff_file():
	    Ccc_file(false)
	{
		m_validating = false;
	}
protected:
	bool m_validating;
};

#endif // !defined(AFX_RIFF_FILE_H__310B5360_F770_11D3_B605_0000B4936994__INCLUDED_)
