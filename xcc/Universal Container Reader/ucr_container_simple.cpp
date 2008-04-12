#include "stdafx.h"
#include "ucr_container_simple.h"

#include "string_conversion.h"

Cucr_container_simple::Cucr_container_simple(const Cucr_format& format):
	m_format(format)
{
}

int Cucr_container_simple::open(const Cvirtual_binary& d)
{
	if (!m_objects.empty())
		close();
	if (!d)
		return 1;
	Cstream_reader sr(d);
	int c = 0;
	{
		vector<int> block_offsets;
		map<int, int> forward_block_offsets;
		int object_offset_delta_block = 0;
		for (Cucr_format::t_blocks::const_iterator i = m_format.blocks().begin(); i != m_format.blocks().end(); i++)
		{
			if (i->offset)
				sr.seek(i->offset > 0 ? i->offset : d.size() + i->offset);
			else
			{
				map<int, int>::const_iterator j = forward_block_offsets.find(i - m_format.blocks().begin());
				if (j != forward_block_offsets.end())
					sr.seek(j->second);
			}
			block_offsets.push_back(sr.r() - sr.d());

			int k = i->count == Cucr_format::ct_once ? 1 : c;
			int object_i = 0;
			while (k--)
			{
				int block_offset = sr.r() - sr.d();
				string name;
				int offset = 0;
				int size = 0;
				map<int, int> forward_var_sizes;
				Cucr_object temp_object;
				if (i->update_object)
					temp_object = m_objects[object_i];
				for (Cucr_format::t_vars::const_iterator j = i->vars.begin(); j != i->vars.end(); j++)
				{
					if (j->offset)
						sr.seek(block_offset + j->offset);
					map<int, int>::const_iterator k = forward_var_sizes.find(j - i->vars.begin());
					int var_size = k == forward_var_sizes.end() ? j->size >> 3 : k->second;
					switch (j->id)
					{
					case Cucr_format::vi_block_offset:
						forward_block_offsets[j->block] = j->read_int(sr);
						break;
					case Cucr_format::vi_object_count:
						c = j->read_int(sr);
						break;
					case Cucr_format::vi_object_id:
						name = nh(j->size >> 2, j->read_int(sr));
						break;
					case Cucr_format::vi_object_name:
						if (i->update_object)
							temp_object.name(j->read_string(sr, var_size));
						else
							name = j->read_string(sr, var_size);
						break;
					case Cucr_format::vi_object_offset:
						offset = j->read_int(sr);
						if (j->block)
							object_offset_delta_block = j->block;
						break;
					case Cucr_format::vi_object_size:
						size = j->read_int(sr);
						break;
					case Cucr_format::vi_literal:
						switch (j->type)
						{
						case Cucr_format::vt_int:
							if (j->read_int(sr) != j->int_value)
							{
								close();
								return 1;
							}
							break;
						case Cucr_format::vt_string:
							if (j->read_string(sr) != j->string_value)
							{
								close();
								return 1;
							}
							break;
						default:
							assert(false);
						}
						break;
					case Cucr_format::vi_var_size:
						forward_var_sizes[j->var] = j->read_int(sr);
						break;
					case Cucr_format::vi_custom:
						switch (j->type)
						{
						case Cucr_format::vt_float:
							j->read_float(sr);
							break;
						case Cucr_format::vt_int:
							j->read_int(sr);
							break;
						case Cucr_format::vt_string:
							j->read_string(sr);
							break;
						case Cucr_format::vt_wstring:
							j->read_wstring(sr, var_size);
							break;
						default:
							assert(false);
						}
						break;
					default:
						assert(false);
					}
				}
				if (i->add_object)
				{
					if (offset < 0)
					{
						close();
						return 1;
					}
					m_objects.push_back(Cucr_object(d, name, offset, size));
				}
				else if (i->update_object)
					m_objects[object_i] = temp_object;
				object_i++;
				if (i->size)
					sr.seek(block_offset + i->size);
			}
		}
		if (object_offset_delta_block)
		{
			int object_offset_delta = block_offsets[object_offset_delta_block];
			for (t_objects::iterator i = m_objects.begin(); i != m_objects.end(); i++)
				i->offset(i->offset() + object_offset_delta);
		}

	}
	return 0;
}