// mix_rg_file.cpp: implementation of the Cmix_rg_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mix_rg_file.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cmix_rg_file::Cmix_rg_file():
	Ccc_file(false)
{
}

bool Cmix_rg_file::is_valid()
{
	if (get_size() < sizeof(t_mix_rg_header))
		return false;
	t_mix_rg_header header;
	seek(0);
	if (read(&header, sizeof(t_mix_rg_header))
		|| header.id != mix_rg_id
		|| header.index_offset + 4 > header.tailer_offset
		|| header.tailer_offset + 4 > get_size()
		|| header.zero)
		return false;
	return true;
}

int Cmix_rg_file::post_open()
{
	m_index.clear();
	m_old_index.clear();
	if (!is_valid())
		return 1;
	if (get_data() && get_vdata().size() != get_size())
		return 0;
	t_mix_rg_header header;
	seek(0);
	int error = read(&header, sizeof(t_mix_rg_header));
	Cvirtual_binary index, tailer;
	if (!error)
	{
		index.write_start(header.tailer_offset - header.index_offset);
		seek(header.index_offset);
		error = read(index.data_edit(), index.size());
	}
	if (!error)
	{
		tailer.write_start(get_size() - header.tailer_offset);
		seek(header.tailer_offset);
		error = read(tailer.data_edit(), tailer.size());
	}
	if (!error)
	{
		int size = *reinterpret_cast<const __int32*>(index.data());
		assert(*reinterpret_cast<const __int32*>(tailer.data()) == size);
		const t_mix_rg_index_entry* r_index = reinterpret_cast<const t_mix_rg_index_entry*>(index.data() + 4);
		const byte* r_tailer = tailer.data() + 4;
		while (size--)
		{
			int cb_v = *r_tailer++;
			string v = reinterpret_cast<const char*>(r_tailer);
			r_tailer += cb_v;
			m_index[v] = *r_index++;
			m_old_index.push_back(v);

		}
	}
	return error;
}