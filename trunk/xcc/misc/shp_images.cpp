#include "stdafx.h"
#include <vector>
#include "shp_decode.h"
#include "shp_images.h"

struct t_image_index_entry
{
	byte* data_in;
	byte* data_out;
	dword format;
};

struct t_image_data
{
	dword cx;
	dword cy;
	dword c_images;
	byte* data;
	t_image_index_entry* index;
};

typedef std::vector<t_image_data*> t_image_list;

t_image_list image_list;

int shp_images::load_shp(const Cshp_file& f, void*& p)
{
	const byte* fdata = f.get_data();
	const t_shp_header* header = f.get_header();
	t_image_data* data = new t_image_data;
	data->cx = header->cx;
	data->cy = header->cy;
	data->c_images = header->c_images;
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
	image_list.push_back(data);
	p = data;
	return 0;
}

const byte* shp_images::get_shp(void* p, dword index)
{
	const t_image_data* data = reinterpret_cast<const t_image_data*>(p);
	if (!data->index[index].data_out && data->cx && data->cy)
	{
		dword cb_out = data->cx * data->cy;
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

const byte* shp_images::get_shp(void* p, dword index, int& cx, int& cy)
{
	const t_image_data* data = reinterpret_cast<const t_image_data*>(p);
	cx = data->cx;
	cy = data->cy;
	return get_shp(p, index);
}

int shp_images::get_shp_c_images(void* p)
{
	t_image_data* data = reinterpret_cast<t_image_data*>(p);
	return data->c_images;
}

static void destroy_shp(t_image_data* p)
{
	delete[] p->data;
	for (dword j = 0; j < p->c_images; j++)
		delete[] p->index[j].data_out;
	delete[] p->index;
	delete p;
}

void shp_images::destroy_shp(void*& p)
{
	for (t_image_list::iterator i = image_list.begin(); i != image_list.end(); i++)
	{
		if (*i == p)
		{
			::destroy_shp(static_cast<t_image_data*>(p));
			p = 0;
			image_list.erase(i);
			break;
		}
	}
};

void shp_images::destroy()
{
	for (t_image_list::iterator i = image_list.begin(); i != image_list.end(); i++)
		::destroy_shp(*i);
	image_list.clear();
}