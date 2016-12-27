#pragma once

#include <cc_file_small.h>

template <class T>
class Ccc_file_sh: public Ccc_file_small
{
public:
    const T& header() const
    {
        return *reinterpret_cast<const T*>(data());
    }
};
