#pragma once

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "xif_key.h"

class Cxif_file: public Ccc_file_sh<t_xif_header_old>
{
public:
	bool is_valid() const
	{
		const t_xif_header_old& h = header();
		return !(sizeof(t_xif_header_old) > size() ||
			h.id != file_id ||
			h.version != file_version_old && h.version != file_version_new && h.version != file_version_fast);
	}

	int decode(Cxif_key& key)
	{
		return key.load_key(data(), size());
	}
};
