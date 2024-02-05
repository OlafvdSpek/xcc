/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include "shp_decode.h"
#include "shp_images.h"
#include "xcc_mixs.h"

static t_theater_id g_theater = static_cast<t_theater_id>(-1);

int shp_images::load_shp(const Cshp_file& f, shp_images::t_image_data*& data)
{
	data = new t_image_data;
	data->cx = f.cx();
	data->cy = f.cy();
	data->cf = f.cf();
	int cb_data = f.get_offset(data->cf) - f.get_offset(0);
	data->data = new byte[cb_data];
	memcpy(data->data, f.get_image(0), cb_data);
	data->index = new t_image_index_entry[data->cf];
	for (int i = 0; i < data->cf; i++)
	{
		data->index[i].data_in = data->data + f.get_offset(i) - f.get_offset(0);
		data->index[i].data_out = NULL;
		data->index[i].format = f.get_format(i) << 28;
		if (f.get_format(i) == 2)
			data->index[i].format |= i - 1;
		else if (f.get_format(i) == 4)
		{
			for (int j = 0; j < data->cf; j++)
			{
				if (f.get_ref_offset(i) == f.get_offset(j))
				{
					data->index[i].format |= j;
					break;
				}
			}
		}
	}
	return 0;
}

int load_shp(const string& name, Cmix_file& mix, shp_images::t_image_data*& p)
{
	Cshp_file f;
	return f.open(name, mix) || shp_images::load_shp(f, p);
}

int shp_images::load_shp(const string& name, t_image_data*& p)
{
	return load_shp(name + Cxcc_mixs::theater_fext(g_theater), Cxcc_mixs::theater(g_theater), p) && load_shp(name + ".shp", Cxcc_mixs::conquer(), p);
}

const byte* shp_images::t_image_data::get(int f, int& cx0, int& cy0)
{
	if (this)
	{
		cx0 = cx;
		cy0 = cy;
		return get(f);
	}
	cx0 = 0;
	cy0 = 0;
	return NULL;
}

void shp_images::destroy_shp(t_image_data*& p)
{
	if (!p)
		return;
	delete[] p->data;
	for (int j = 0; j < p->cf; j++)
		delete[] p->index[j].data_out;
	delete[] p->index;
	delete p;
	p = NULL;
};

void shp_images::set_theater(t_theater_id v)
{
	g_theater = v;
};

const byte* shp_images::t_image_data::get(int f)
{
	if (!index[f].data_out && cx && cy)
	{
		int cb_out = cx * cy;
		index[f].data_out = new byte[cb_out];
		if (index[f].format & 8 << 28)
			decode80(index[f].data_in, index[f].data_out);
		else
		{
			memcpy(index[f].data_out, get(index[f].format & shp_o_mask), cb_out);
			decode40(index[f].data_in, index[f].data_out);
		}
	}
	return index[f].data_out;
}
