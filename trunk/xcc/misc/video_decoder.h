// video_decoder.h: interface for the Cvideo_decoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEO_DECODER_H__19F569DD_C810_4315_9AD7_6AE2CAD1CE1F__INCLUDED_)
#define AFX_VIDEO_DECODER_H__19F569DD_C810_4315_9AD7_6AE2CAD1CE1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "palet.h"

class Cvideo_decoder  
{
public:
	virtual int cb_pixel() const = 0;
	virtual int cf() const = 0;
	virtual int cx() const = 0;
	virtual int cy() const = 0;
	virtual int decode(void* d) = 0;
	virtual const t_palet_entry* palet() const;
	virtual int seek(int f) = 0;
	virtual ~Cvideo_decoder();

	int cb_image() const
	{
		return cb_pixel() * cx() * cy();
	}

};

#endif // !defined(AFX_VIDEO_DECODER_H__19F569DD_C810_4315_9AD7_6AE2CAD1CE1F__INCLUDED_)
