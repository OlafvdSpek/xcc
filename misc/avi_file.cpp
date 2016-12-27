#include "stdafx.h"
#include "avi_file.h"

int Cavi_file::process_chunk(const t_riff_header& header)
{
	if (m_validating)
	{
		if (header.id != riff_id || header.size != get_size() - sizeof(t_riff_header))
			return 1;
	}
	switch (header.id)
	{
	case riff_id:
		{
			t_riff_chunk chunk;
			if (read(&chunk, sizeof(t_riff_chunk)))
				return 1;
			if (m_validating)
				return chunk.id != riff_avi_id;
		}
	}
	skip(header.size);
	return 0;
}