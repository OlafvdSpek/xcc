#include "stdafx.h"
#include "cps_file.h"
#include "shp_decode.h"
#include "pcx_decode.h"
#include "pcx_file_write.h"

int Ccps_file::extract_as_pcx(const string& name, const t_palet _palet) const
{
	t_palet palet;
	if (has_palet())
		memcpy(palet, get_palet(), sizeof(t_palet));
	else
		memcpy(palet, _palet, sizeof(t_palet));
	convert_palet_18_to_24(palet);
	byte* image = new byte[320 * 200];
	decode80(get_image(), image);
	byte* d = new byte[320 * 200 * 2];
	int cb_d = pcx_encode(image, d, 320, 200, 1);
	Cpcx_file_write f;
	int error = f.open_write(name);
	if (!error)
	{
		f.set_size(320, 200, 1);
		error = f.write_header();
	}
	if (!error)
		error = f.write_image(d, cb_d);
	if (!error)
		error = f.write_palet(palet);
	f.close();
	delete[] d;
	delete[] image;
	return error;
}

int cps_file_write(const byte* s, byte* d, const t_palet_entry* palet)
{
	byte* w = d;
	t_cps_header& header = *reinterpret_cast<t_cps_header*>(w);
	header.unknown = 4;
	header.image_size = 320 * 200;
	header.zero = 0;
	header.palet_size = palet ? sizeof(t_palet) : 0;
	w += sizeof(t_cps_header);
	if (palet)
	{
		memcpy(w, palet, sizeof(t_palet));
		w += sizeof(t_palet);
	}
	w += encode80(s, w, 320 * 200);
	header.size = w - d - 2;
	return w - d;
}