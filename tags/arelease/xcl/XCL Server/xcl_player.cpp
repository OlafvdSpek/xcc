// xcl_player.cpp: implementation of the Cxcl_player class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xcl_player.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cxcl_player::Cxcl_player()
{
}

Cxcl_player::Cxcl_player(const Csql_row& row)
{
	pid = row.f_int(0);
	name = row.f(1);
	rank = row.f_int(2);
	win_count = row.f_int(3);
	loss_count = row.f_int(4);
	points = row.f_int(5);
}