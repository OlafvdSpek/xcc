// xap.h: interface for the Cxap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XAP_H__4137CC42_CA2A_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XAP_H__4137CC42_CA2A_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mmsystem.h>
#include <dsound.h>

class Cxap  
{
public:
	Cxap();
	virtual ~Cxap();
	bool busy();
	int load(const byte* s, int cb_s);
	int play(bool start_thread = true);
	void ds(LPDIRECTSOUND ds);
private:
	static unsigned int play(void* p);

	byte* m_s;
	int mcb_s;
	LPDIRECTSOUND m_ds;
};

#endif // !defined(AFX_XAP_H__4137CC42_CA2A_11D4_B606_0000B4936994__INCLUDED_)
