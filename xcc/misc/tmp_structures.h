#pragma once

#include "vartypes.h"

#pragma pack(push, 1)

struct t_tmp_header
{
	word cx;
	//always 24
	word cy;
	//always 24
	word c_tiles;
	word zero1;
	//always 0
	dword size;
	dword image_start;
	dword zero2;
	//always 0
	dword id;
	//always 0x0d1affff
	dword ofs2;
	dword ofs1;

};
           
#pragma pack(pop)