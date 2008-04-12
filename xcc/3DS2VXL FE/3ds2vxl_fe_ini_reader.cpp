#include "stdafx.h"
// #include "3DS2VXL FE.h"
#include "3ds2vxl_fe_ini_reader.h"

C3ds2vxl_fe_ini_reader::C3ds2vxl_fe_ini_reader()
{
	m_options.destination = "";
	m_options.estimate_origin = false;
	m_options.flip_x = false;
	m_options.flip_y = false;
	m_options.flip_z = false;
	m_options.sgal = false;
	m_options.sgn = false;
	m_options.size = 255;
	m_options.skybox = "";
	m_options.source = "";
	m_options.swap_xy = false;
	m_options.swap_yz = false;
	m_options.swap_zx = false;
	m_options.materials = true;
	m_options.textures = true;
	m_options.resolution = 0;
	m_options.scale = 1;
	m_options.enable_viewer = true;
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
	else if (name == "flip_z")
		m_options.flip_z = value_int;
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
	else if (name == "swap_yz")
		m_options.swap_yz = value_int;
	else if (name == "swap_zx")
		m_options.swap_zx = value_int;
	else if (name == "materials")
		m_options.materials = value_int;
	else if (name == "textures")
		m_options.textures = value_int;
	else if (name == "resolution")
		m_options.resolution = value_int;
	else if (name == "scale")
		m_options.scale = atof(value.c_str());
	else if (name == "enable_viewer")
		m_options.enable_viewer = value_int;
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
		<< "flip_z=" << options.flip_z << endl
		<< "sgal=" << options.sgal << endl
		<< "sgn=" << options.sgn << endl
		<< "size=" << options.size << endl
		<< "skybox=" << options.skybox << endl
		<< "source=" << options.source << endl
		<< "swap_xy=" << options.swap_xy << endl
		<< "swap_yz=" << options.swap_yz << endl
		<< "swap_zx=" << options.swap_zx << endl
		<< "materials=" << options.materials << endl
		<< "textures=" << options.textures << endl
		<< "resolution=" << options.resolution << endl
		<< "scale=" << options.scale << endl
		<< "enable_viewer=" << options.enable_viewer << endl;
	return os;
}