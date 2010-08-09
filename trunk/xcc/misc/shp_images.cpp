#include "stdafx.h"
#include "shp_decode.h"
#include "shp_images.h"
#include "xcc_mixs.h"

struct t_image_index_entry
{
	byte* data_in;
	byte* data_out;
	int format;
};

struct t_image_data
{
	int cx;
	int cy;
	int c_images;
	byte* data;
	t_image_index_entry* index;
};

int shp_images::load_shp(const Cshp_file& f, void*& p)
{
	t_image_data* data = new t_image_data;
	data->cx = f.get_cx();
	data->cy = f.get_cy();
	data->c_images = f.get_c_images();
	int cb_data = f.get_offset(data->c_images) - f.get_offset(0);
	data->data = new byte[cb_data];
	memcpy(data->data, f.get_image(0), cb_data);
	data->index = new t_image_index_entry[data->c_images];
	for (int i = 0; i < data->c_images; i++)
	{
		data->index[i].data_in = data->data + f.get_offset(i) - f.get_offset(0);
		data->index[i].data_out = NULL;
		data->index[i].format = f.get_format(i) << 28;
		if (f.get_format(i) == 2)
			data->index[i].format |= i - 1;
		else if (f.get_format(i) == 4)
		{
			for (int j = 0; j < data->c_images; j++)
			{
				if (f.get_ref_offset(i) == f.get_offset(j))
				{
					data->index[i].format |= j;
					break;
				}
			}
		}
	}
	p = data;
	return 0;
}

int shp_images::load_shp(const string& name, Cmix_file& mix, void*& p)
{
	Cshp_file f;
	return f.open(name, mix) || load_shp(f, p);
}

int shp_images::load_shp(const string& name, void*& p)
{
	return load_shp(name + ".shp", Cxcc_mixs::conquer(), p);
}

const byte* shp_images::get_shp(void* p, int index)
{
	const t_image_data* data = static_cast<const t_image_data*>(p);
	if (!data->index[index].data_out && data->cx && data->cy)
	{
		int cb_out = data->cx * data->cy;
		data->index[index].data_out = new byte[cb_out];
		// decompress image
		if (data->index[index].format & 8 << 28)
			decode80(data->index[index].data_in, data->index[index].data_out);
		else
		{
			memcpy(data->index[index].data_out, get_shp(p, data->index[index].format & shp_o_mask), cb_out);
			decode40(data->index[index].data_in, data->index[index].data_out);
		}
	}
	return data->index[index].data_out;
}

const byte* shp_images::get_shp(void* p, int index, int& cx, int& cy)
{
	const t_image_data* data = static_cast<const t_image_data*>(p);
	cx = data->cx;
	cy = data->cy;
	return get_shp(p, index);
}

int shp_images::get_shp_c_images(void* p)
{
	return static_cast<t_image_data*>(p)->c_images;
}

static void destroy_shp(t_image_data* p)
{
	delete[] p->data;
	for (int j = 0; j < p->c_images; j++)
		delete[] p->index[j].data_out;
	delete[] p->index;
	delete p;
}

void shp_images::destroy_shp(void*& p)
{
	::destroy_shp(static_cast<t_image_data*>(p));
	p = NULL;
};
