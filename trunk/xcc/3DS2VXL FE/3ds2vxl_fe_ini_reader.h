#pragma once

#include "ini_reader.h"

struct t_options
{
	string destination;
	bool estimate_origin;
	bool flip_x;
	bool flip_y;
	bool flip_z;
	bool sgal;
	bool sgn;
	int size;
	string skybox;
	string source;
	bool swap_xy;
	bool swap_yz;
	bool swap_zx;
	bool materials;
	bool textures;
	int resolution;
	float scale;
	bool enable_viewer;
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
