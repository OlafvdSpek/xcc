#pragma once

#include "cc_file_sh.h"
#include "palet.h"
#include "video_decoder.h"

template <class T>
class Cvideo_file: public Ccc_file_sh<T>
{
public:
	virtual int cb_pixel() const = 0;
	virtual int cf() const = 0;
	virtual int cx() const = 0;
	virtual int cy() const = 0;

	int cb_image() const
	{
		return cb_pixel() * cx() * cy();
	}

	int cb_video() const
	{
		return cf() * cb_image();
	}

	virtual Cvideo_decoder* decoder(const t_palet_entry*)
	{
		return NULL;
	}

	virtual const t_palet_entry* palet() const
	{
		return NULL;
	}
};
