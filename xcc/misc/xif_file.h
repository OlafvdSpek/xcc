#pragma once

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "xif_key.h"

class Cxif_file: public Ccc_file_sh<t_xif_header_old>
{
public:
	bool is_valid() const
	{
 		int size = get_size();
		const t_xif_header_old& header = *get_header();
		return !(sizeof(t_xif_header_old) > size ||
			header.id != file_id ||
			header.version != file_version_old && header.version != file_version_new && header.version != file_version_fast);
	}

	int decode(Cxif_key& key)
	{
		return key.load_key(get_data(), get_size());
	}
};
