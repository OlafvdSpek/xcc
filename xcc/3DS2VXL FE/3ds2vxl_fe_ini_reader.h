// 3ds2vxl_fe_ini_reader.h: interface for the C3ds2vxl_fe_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DS2VXL_FE_INI_READER_H__3A4E0185_F08E_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_3DS2VXL_FE_INI_READER_H__3A4E0185_F08E_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ini_reader.h"

struct t_options
{
	string destination;
	bool estimate_origin;
	bool flip_x;
	bool flip_y;
	bool sgal;
	bool sgn;
	int size;
	string skybox;
	string source;
	bool swap_xy;
	bool textures;
};

class C3ds2vxl_fe_ini_reader: public Cini_reader
{
public:
	C3ds2vxl_fe_ini_reader();
	virtual int process_section_start(const string& name);
	virtual bool process_section() const;
	virtual int process_key(const string& name, const string& value);

	t_options options() const
	{
		return m_options;
	}
private:
	t_options m_options;
};

ostream& write_ini(t_options options, ostream& os);

#endif // !defined(AFX_3DS2VXL_FE_INI_READER_H__3A4E0185_F08E_11D4_B606_0000B4936994__INCLUDED_)
