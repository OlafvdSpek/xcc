#pragma once

#include <span>

template <class T, class U>
class data_ref_base : public std::span<T>
{
private:
	using base_t = std::span<T>;
public:
	data_ref_base() = default;

	template<class V>
	data_ref_base(const V& v, typename std::enable_if_t<std::is_class<V>::value>* = 0)
	{
		if (v.end() != v.begin())
			assign(&*v.begin(), v.end() - v.begin() + &*v.begin());
	}

	template<class V>
	data_ref_base(V& v, typename std::enable_if<std::is_class<V>::value>* = 0)
	{
		if (v.end() != v.begin())
			assign(&*v.begin(), v.end() - v.begin() + &*v.begin());
	}

	data_ref_base(U begin, U end)
	{
		assign(begin, end);
	}

	data_ref_base(U begin, size_t size)
	{
		assign(begin, size);
	}

	void assign(U begin, U end)
	{
		static_cast<base_t&>(*this) = base_t(reinterpret_cast<T*>(begin), reinterpret_cast<T*>(end));
	}

	void assign(U begin, size_t size)
	{
		assign(begin, reinterpret_cast<T*>(begin) + size);
	}
};

using data_ref = data_ref_base<const unsigned char, const void*>;
