// XSTE.h: interface for the CXSTE class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XSTE_H__67A1E720_C57B_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XSTE_H__67A1E720_C57B_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "csf_file.h"
#include "file32.h"

class CXSTE  
{
public:
	Ccsf_file& csf_f();
	int open(t_game game);
	int write();
	void close();
private:
	Ccsf_file m_csf_f;
	Cfile32 m_f;
};

#endif // !defined(AFX_XSTE_H__67A1E720_C57B_11D4_B606_0000B4936994__INCLUDED_)
