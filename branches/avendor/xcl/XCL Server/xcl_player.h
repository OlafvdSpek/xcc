// xcl_player.h: interface for the Cxcl_player class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCL_PLAYER_H__20806A94_588B_4031_B860_81F208B29211__INCLUDED_)
#define AFX_XCL_PLAYER_H__20806A94_588B_4031_B860_81F208B29211__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sql/sql_result.h"

class Cxcl_player  
{
public:

	int pid;
	string name;
	int rank;
	int win_count;
	int loss_count;
	int points;

	Cxcl_player();
	Cxcl_player(const Csql_row& row);	
};

#endif // !defined(AFX_XCL_PLAYER_H__20806A94_588B_4031_B860_81F208B29211__INCLUDED_)
