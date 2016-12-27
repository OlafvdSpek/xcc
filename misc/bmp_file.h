#pragma once

#include "cc_file_small.h"

class Cbmp_file: public Ccc_file_small
{
public:
	bool is_valid() const;
};
