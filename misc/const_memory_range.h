/*
    XCC Utilities and Library
    Copyright (C) 2008  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <boost/array.hpp>
#include <string>
#include <vector>

template <class T>
class memory_range_base
{
public:
	memory_range_base()
	{
		begin = NULL;
		end = NULL;
	}

	template<class U>
	memory_range_base(const memory_range_base<U>& v)
	{
		assign(v.begin, v.end);
	}

	memory_range_base(void* begin_, void* end_)
	{
		assign(begin_, end_);
	}

	memory_range_base(void* begin_, size_t size)
	{
		assign(begin_, size);
	}

	template<size_t U>
	memory_range_base(boost::array<char, U>& v)
	{
		assign(&v.front(), v.size());
	}

	template<size_t U>
	memory_range_base(boost::array<unsigned char, U>& v)
	{
		assign(&v.front(), v.size());
	}

	memory_range_base(std::vector<char>& v)
	{
		assign(&v.front(), v.size());
	}

	memory_range_base(std::vector<unsigned char>& v)
	{
		assign(&v.front(), v.size());
	}

	memory_range_base assign(void* begin_, void* end_)
	{
		begin = reinterpret_cast<T>(begin_);
		end = reinterpret_cast<T>(end_);
		return *this;
	}
	
	memory_range_base assign(void* begin_, size_t size)
	{
		begin = reinterpret_cast<T>(begin_);
		end = begin + size;
		return *this;
	}
	
	void clear()
	{
		begin = end = NULL;
	}
	
	bool empty() const
	{
		return begin == end;
	}

	size_t size() const
	{
		return end - begin;
	}

	std::string string() const
	{
		return std::string(reinterpret_cast<const char*>(begin), size());
	}

	memory_range_base sub_range(size_t o, size_t s)
	{
		return memory_range_base(begin + o, s);
	}

	operator T() const
	{
		return begin;
	}

	memory_range_base operator++(int)
	{
		memory_range_base t = *this;
		begin++;
		return t;
	}

	memory_range_base operator+=(size_t v)
	{
		begin += v;
		return *this;
	}

	T begin;
	T end;
};

typedef memory_range_base<unsigned char*> memory_range;

template <class T>
class const_memory_range_base
{
public:
	const_memory_range_base()
	{
		begin = NULL;
		end = NULL;
	}

	template<class U>
	const_memory_range_base(const const_memory_range_base<U>& v)
	{
		assign(v.begin, v.end);
	}

	template<class U>
	const_memory_range_base(const memory_range_base<U>& v)
	{
		assign(v.begin, v.end);
	}

	const_memory_range_base(const void* begin_, const void* end_)
	{
		assign(begin_, end_);
	}

	const_memory_range_base(const void* begin_, size_t size)
	{
		assign(begin_, size);
	}

	const_memory_range_base(const std::string& v)
	{
		assign(v.data(), v.size());
	}

	template<size_t U>
	const_memory_range_base(const boost::array<char, U>& v)
	{
		assign(&v.front(), v.size());
	}

	template<size_t U>
	const_memory_range_base(const boost::array<unsigned char, U>& v)
	{
		assign(&v.front(), v.size());
	}

	const_memory_range_base(const std::vector<char>& v)
	{
		assign(&v.front(), v.size());
	}

	const_memory_range_base(const std::vector<unsigned char>& v)
	{
		assign(&v.front(), v.size());
	}

	const_memory_range_base assign(const void* begin_, const void* end_)
	{
		begin = reinterpret_cast<T>(begin_);
		end = reinterpret_cast<T>(end_);
		return *this;
	}
	
	const_memory_range_base assign(const void* begin_, size_t size)
	{
		begin = reinterpret_cast<T>(begin_);
		end = begin + size;
		return *this;
	}
	
	void clear()
	{
		begin = end = NULL;
	}
	
	bool empty() const
	{
		return begin == end;
	}

	size_t size() const
	{
		return end - begin;
	}

	std::string string() const
	{
		return std::string(reinterpret_cast<const char*>(begin), size());
	}

	const_memory_range_base sub_range(size_t o, size_t s)
	{
		return const_memory_range_base(begin + o, s);
	}

	operator T() const
	{
		return begin;
	}

	const_memory_range_base operator++(int)
	{
		const_memory_range_base t = *this;
		begin++;
		return t;
	}

	const_memory_range_base operator+=(size_t v)
	{
		begin += v;
		return *this;
	}

	T begin;
	T end;
};

typedef const_memory_range_base<const unsigned char*> const_memory_range;
