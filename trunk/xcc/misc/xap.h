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
#include "virtual_binary.h"

class Cxap  
{
public:
	bool busy();
	int load(const Cvirtual_binary s);
	int play(bool start_thread = true);
	void ds(LPDIRECTSOUND ds);
private:
	static unsigned int play(void* p);

	Cvirtual_binary m_s;
	LPDIRECTSOUND m_ds;
};

#endif // !defined(AFX_XAP_H__4137CC42_CA2A_11D4_B606_0000B4936994__INCLUDED_)
