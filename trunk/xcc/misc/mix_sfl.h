#if !defined(AFX_MIX_SFL_H__CD423641_907C_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_MIX_SFL_H__CD423641_907C_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_structures.h"

namespace mix_sfl
{
	void clear(t_game game);
	bool contains(t_game game, int id);
	void erase(t_game game, int id);
	void insert(t_game game, int id);
	int load();
	int save();
};

#endif // !defined(AFX_MIX_SFL_H__CD423641_907C_11D4_B606_0000B4936994__INCLUDED_)
