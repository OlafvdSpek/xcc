#pragma once

#include <cc_file_small.h>
#include <palet.h>

class Cpal_file: public Ccc_file_small
{
public:
	ostream& extract_as_pal_jasc(ostream&, bool shift_left = true) const;
	bool is_valid() const;

	void decode(t_palet& palet) const
	{
		convert_palet_18_to_24(get_palet(), palet);
	}

    const t_palet_entry* get_palet() const
    {
        return reinterpret_cast<const t_palet_entry*>(data());
    }
};
