#pragma once

#include <mmsystem.h>
#include <dsound.h>
#include <virtual_binary.h>

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
