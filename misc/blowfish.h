#pragma once

#include <vartypes.h>

class Cblowfish
{
public:
	using t_bf_p = uint32_t[18];
	using t_bf_s = uint32_t[4][256];

	void set_key(data_ref);
	void encipher(const void* s, void* d, int size) const;
	void decipher(const void* s, void* d, int size) const;
private:
	void encipher(uint32_t& xl, uint32_t& xr) const;
	void decipher(uint32_t& xl, uint32_t& xr) const;
	uint32_t S(uint32_t x, int i) const;
	uint32_t bf_f(uint32_t x) const;
	void ROUND(uint32_t& a, uint32_t b, int n) const;

	t_bf_p m_p;
	t_bf_s m_s;
};
