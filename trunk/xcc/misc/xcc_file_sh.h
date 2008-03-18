#pragma once

#include "xcc_file.h"

template <class T>
class Cxcc_file_sh: public Cxcc_file
{
public:
    const T* get_header() const
    {
        return reinterpret_cast<const T*>(get_data() + sizeof(t_xcc_header));
    }
};
