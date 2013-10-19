#pragma once

#include <SDL.h>
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>
#include <boost/utility.hpp>
#include <cassert>
#include <ctime>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <windows.h>
#include <xbt/find_ptr.h>
#include <xbt/shared_data.h>
#include "sdl_color.h"
#include "sdl_rect.h"
#include "sdl_surface.h"

using namespace std;
using boost::trim_copy;

template <class T, class U>
int find_ref(const T& c, U v, int z)
{
	auto i = find_ptr(c, v);
	return i ? to_int(*i) : z;
}
