// blowfish.h: interface for the Cblowfish class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOWFISH_H__5CA851E0_D67C_11D3_B604_0000B4936994__INCLUDED_)
#define AFX_BLOWFISH_H__5CA851E0_D67C_11D3_B604_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vartypes.h>

typedef dword t_bf_p[18];
typedef dword t_bf_s[4][256];

class Cblowfish  
{
public:
	void set_key(const byte* key, int cb_key);
	void encipher(dword& xl, dword& xr) const;
	void encipher(const void* s, void* d, int size) const;
	void decipher(dword& xl, dword& xr) const;
	void decipher(const void* s, void* d, int size) const;
private:
	inline dword Cblowfish::S(dword x, int i) const;
	inline dword Cblowfish::bf_f(dword x) const;
	inline void Cblowfish::ROUND(dword& a, dword b, int n) const;

	t_bf_p m_p;
	t_bf_s m_s;
};

#endif // !defined(AFX_BLOWFISH_H__5CA851E0_D67C_11D3_B604_0000B4936994__INCLUDED_)
