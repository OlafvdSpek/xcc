#pragma once

#include "riff_file.h"

class Cavi_file: public Criff_file    
{
public:
	int process_chunk(const t_riff_header& header);
};
