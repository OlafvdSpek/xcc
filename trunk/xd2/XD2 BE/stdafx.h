#pragma once

#include <SDL.h>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <boost/smart_ptr.hpp>
#include <cassert>
#include <ctime>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <windows.h>
#include <xbt/find_ptr.h>
#include <xbt/virtual_binary.h>
#include "sdl_color.h"
#include "sdl_rect.h"
#include "sdl_surface.h"

using namespace std;
using boost::trim_copy;

template <class T, class U>
const typename T::mapped_type& find_ref(const T& c, U v, typename const T::mapped_type& z)
{
	auto i = find_ptr(c, v);
	return i ? *i : z;
}

template <class T, class U>
int find_ref(const T& c, U v, int z)
{
	auto i = find_ptr(c, v);
	return i ? atoi(i->c_str()) : z;
}
