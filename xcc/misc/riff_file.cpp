// riff_file.cpp: implementation of the Criff_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "riff_file.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int Criff_file::process()
{
	seek(0);
	t_riff_header header;
	if (read(&header, sizeof(t_riff_header)))
		return 1;
	else
		return process_chunk(header);
}

int Criff_file::process_chunk(const t_riff_header& header)
{
	if (m_validating)
	{
		if (header.id != riff_id || header.size != get_size() - sizeof(t_riff_header))
			return 1;
	}
	skip(header.size);
	return 0;
}