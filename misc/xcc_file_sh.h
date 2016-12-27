#pragma once

#include "xcc_file.h"

template <class T>
class Cxcc_file_sh: public Cxcc_file
{
public:
    const T& header() const
    {
        return *reinterpret_cast<const T*>(data() + sizeof(t_xcc_header));
    }
};
