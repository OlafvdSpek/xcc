// 3ds2vxl_fe_ini_reader.cpp: implementation of the C3ds2vxl_fe_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include "3DS2VXL FE.h"
#include "3ds2vxl_fe_ini_reader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3ds2vxl_fe_ini_reader::C3ds2vxl_fe_ini_reader()
{
	m_options.destination = "";
	m_options.estimate_origin = false;
	m_options.flip_x = false;
	m_options.flip_y = false;
	m_options.sgal = false;
	m_options.sgn = false;
	m_options.size = 255;
	m_options.skybox = "";
	m_options.source = "";
	m_options.swap_xy = false;
	m_options.textures = true;
}

int C3ds2vxl_fe_ini_reader::process_section_start(const string& name)
{
	return 0;
}

bool C3ds2vxl_fe_ini_reader::process_section() const
{
	return true;
}

int C3ds2vxl_fe_ini_reader::process_key(const string& name, const string& value)
{
	int value_int = atoi(value.c_str());
	if (name == "destination")
		m_options.destination = value;
	else if (name == "estimate_origin")
		m_options.estimate_origin = value_int;
	else if (name == "flip_x")
		m_options.flip_x = value_int;
	else if (name == "flip_y")
		m_options.flip_y = value_int;
	else if (name == "sgal")
		m_options.sgal = value_int;
	else if (name == "sgn")
		m_options.sgn = value_int;
	else if (name == "size")
		m_options.size = value_int;
	else if (name == "skybox")
		m_options.skybox = value;
	else if (name == "source")
		m_options.source = value;
	else if (name == "swap_xy")
		m_options.swap_xy = value_int;
	else if (name == "textures")
		m_options.textures = value_int;
	else
		return 1;
	return 0;
}

ostream& write_ini(t_options options, ostream& os)
{
	os << "destination=" << options.destination << endl
		<< "estimate_origin=" << options.estimate_origin << endl
		<< "flip_x=" << options.flip_x << endl
		<< "flip_y=" << options.flip_y << endl
		<< "sgal=" << options.sgal << endl
		<< "sgn=" << options.sgn << endl
		<< "size=" << options.size << endl
		<< "skybox=" << options.skybox << endl
		<< "source=" << options.source << endl
		<< "swap_xy=" << options.swap_xy << endl
		<< "textures=" << options.textures << endl;
	return os;
}