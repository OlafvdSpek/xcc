// xcl_database.h: interface for the Cxcl_database class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCL_DATABASE_H__96E5131C_1A7C_4A26_9DE5_0CC56ECD5139__INCLUDED_)
#define AFX_XCL_DATABASE_H__96E5131C_1A7C_4A26_9DE5_0CC56ECD5139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sql/database.h"
#include "wol/game_result.h"
#include "xcl_player.h"

class Cxcl_database: public Cdatabase
{
public:
	void drop_tables();
	void create_tables();
	Cxcl_player player(int pid);
	Cxcl_player player(int lid, const string& name);
	Cxcl_player player(int lid, int cid);
	void insert_game(const Cgame_result& gr);
	void insert_game(const Cvirtual_binary&);
	int pid(int lid, const string& name);
	int update_player(int cmp, int cty, const Cxcl_player& a, const Cxcl_player& b);
	void update_ranks();
};

#endif // !defined(AFX_XCL_DATABASE_H__96E5131C_1A7C_4A26_9DE5_0CC56ECD5139__INCLUDED_)
