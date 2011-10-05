#include "stdafx.h"
#include "XSTE.h"

#include "mix_file.h"
#include "xcc_dirs.h"

Ccsf_file& CXSTE::csf_f()
{
	return m_csf_f;
}

int CXSTE::open(t_game game)
{
	int error = m_f.open_edit(xcc_dirs::get_dir(game) + xcc_dirs::get_csf_fname(game));
	if (!error)
	{
		if (!m_f.size())
		{
			Cmix_file language;
			error = language.open(xcc_dirs::get_language_mix(game));
			if (!error)
			{
				Ccsf_file f;
				error = f.open(xcc_dirs::get_csf_fname(game), language);
				if (!error)
					error = m_f.write(f);
			}
		}
		if (!error)
			error = m_csf_f.open(m_f.h());
		if (error)
			m_f.close();
	}
	return error;
}

int CXSTE::write()
{
	m_f.seek(0);
	Cvirtual_binary d = m_csf_f.write();
	int error = m_f.write(d);
	if (!error)
		error = m_f.set_eof();
	return error;
}
