#pragma once

#include "cc_file.h"
#include "riff_structures.h"

class Criff_file : public Ccc_file
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
