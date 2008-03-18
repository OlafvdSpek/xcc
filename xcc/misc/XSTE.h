#pragma once

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
