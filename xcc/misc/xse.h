// xse.h: interface for the Cxse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XSE_H__37982120_CEE0_11D4_A95D_0050042229FC__INCLUDED_)
#define AFX_XSE_H__37982120_CEE0_11D4_A95D_0050042229FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "audio_idx_file.h"
#include "file32.h"
#include "virtual_file.h"
#include "wav_file.h"

class Cxse  
{
public:
	struct t_map_entry
	{
		int offset;
		int size;
		int samplerate;
		int flags;
		int chunk_size;
	};

	typedef map<string, t_map_entry> t_map;

	int open();
	void read_idx_file(const Caudio_idx_file& f);
	int extract(string fname, Cvirtual_file& f);
	int insert(string fname, Cwav_file& f);
	int write_idx_file();
	int write();
	void close();

	const t_map& map() const
	{
		return m_map;
	}
private:
	Cfile32 m_bag_f;
	Cfile32 m_idx_f;
	t_map m_map;
};

#endif // !defined(AFX_XSE_H__37982120_CEE0_11D4_A95D_0050042229FC__INCLUDED_)
