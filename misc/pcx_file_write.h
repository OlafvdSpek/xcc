#pragma once

#include "cc_structures.h"
#include "file32.h"
#include "palet.h"
#include "virtual_file.h"

class Cpcx_file_write : public Cfile32  
{
public:
	void set_size(int cx, int cy, int c_planes);
	int write_header();
	int write_image(const void* data, int size);
	int write_palet(const t_palet palet);
private:
	int m_cx;
	int m_cy;
	int mc_planes;
};

Cvirtual_binary pcx_file_write(const byte* image, const t_palet_entry* palet, int cx, int cy);
void pcx_file_write(Cvirtual_file& f, const byte* image, const t_palet_entry* palet, int cx, int cy);
int pcx_file_write(const string& name, const byte* image, const t_palet_entry* palet, int cx, int cy);
