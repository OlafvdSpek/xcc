#pragma once

#include "cc_structures.h"
#include "palet.h"
#include "video_file.h"
#include "virtual_file.h"
#include "virtual_image.h"

template <class T>
class Cimage_file : public Cvideo_file<T>
{
public:
	virtual void decode(void*) const = 0;
	
	virtual Cvirtual_image vimage() const
	{
		Cvirtual_binary image;
		decode(image.write_start(this->cb_image()));
		return Cvirtual_image(image, this->cx(), this->cy(), this->cb_pixel(), this->palet());
	}
	
	int cf() const override
	{
		return 1;
	}
};

int image_file_write(Cvirtual_file&, t_file_type, const byte* image, const t_palet_entry*, int cx, int cy);
Cvirtual_file image_file_write(t_file_type, const byte* image, const t_palet_entry*, int cx, int cy);
int image_file_write(const string& name, t_file_type, const byte* image, const t_palet_entry*, int cx, int cy);
