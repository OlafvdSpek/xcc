// XSTE.cpp: implementation of the CXSTE class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XSTE.h"
#include "mix_file.h"
#include "xcc_dirs.h"

Ccsf_file& CXSTE::csf_f()
{
	return m_csf_f;
}

int CXSTE::open()
{
	int error = m_f.open_edit(xcc_dirs::get_ra2_dir() + "ra2.csf");
	if (!error)
	{
		if (!m_f.get_size())
		{
			Cmix_file language;
			error = language.open(xcc_dirs::get_ra2_dir() + "language.mix");
			if (!error)
			{
				Ccsf_file f;
				error = f.open("ra2.csf", language);
				if (!error)
				{
					error = m_f.write(f.get_data(), f.get_size());
					f.close();
				}
				language.close();
			}
		}
		if (!error)
			error = m_csf_f.attach(m_f.handle());
		if (error)
			m_f.close();
	}
	return error;
}

int CXSTE::write()
{
	m_f.seek(0);
	int cb_d = m_csf_f.get_write_size();
	byte* d = new byte[cb_d];
	m_csf_f.write(d);
	int error = m_f.write(d, cb_d);
	delete[] d;
	if (!error)
		error = m_f.set_eof();
	return error;
}

void CXSTE::close()
{
	if (m_csf_f.is_attached())
		m_csf_f.detach();
	m_f.close();
}