// xif_key.cpp: implementation of the Cxif_key class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "file32.h"
#include "xif_key.h"

#include "string_conversion.h"

static void dump_spaces(ostream& os, int count)
{
	while (count--)
		os << ' ';
}

void Cxif_key::dump_ratio(ostream& os, Cvirtual_binary* t) const
{
	int cb_s = get_size();
	unsigned long cb_z = cb_s + (cb_s + 999) / 1000 + 12;
	if (!t->data())
		t->write_start(cb_s + cb_z);
	assert(t->size() >= cb_s + cb_z);
	byte* w = t->data_edit();
	save(w);
	if (Z_OK == compress(t->data_edit() + cb_s, &cb_z, t->data(), cb_s))
		os << " (" << cb_z << '/' << cb_s << ')';
}

void Cxif_key::dump(ostream& os, bool show_ratio, int depth, Cvirtual_binary* t) const
{
	bool own_t = !t;
	if (own_t)
	{
		t = new Cvirtual_binary;
		os << "K\\";
		dump_ratio(os, t);
		os << ':' << endl;
		depth++;
	}
	{
		for (t_xif_key_map::const_iterator i = m_keys.begin(); i != m_keys.end(); i++)
		{
			dump_spaces(os, depth << 1);
			os << 'K' << nh(8, i->first);
			int cb_s = i->second.get_size();
			if (show_ratio && cb_s > 64)
				i->second.dump_ratio(os, t);
			/*
			{
				byte* s = new byte[cb_s];
				byte* w = s;
				i->second.save(w);
				unsigned long cb_z = cb_s + (cb_s + 999) / 1000 + 12;
				byte* z = new byte[cb_z];
				compress(z, &cb_z, s, cb_s);
				delete[] z;
				os << " (" << cb_z << '/' << cb_s << ')';
				delete[] s;
			}
			*/
			os << ':' << endl;
			i->second.dump(os, show_ratio, depth + 1, t);
		}
	}
	{
		for (t_xif_value_map::const_iterator i = m_values.begin(); i != m_values.end(); i++)
		{
			dump_spaces(os, depth << 1);
			os << 'V' << nh(8, i->first);
			int cb_s = i->second.get_size();
			if (show_ratio && cb_s > 64)
			{
				unsigned long cb_z = t->size();
				if (Z_OK == compress(t->data_edit(), &cb_z, i->second.get_data(), cb_s))
					os << " (" << cb_z << '/' << cb_s << ')';
			}
			os << ": ";
			i->second.dump(os, depth + 1);
		}
	}
	if (own_t)
		delete t;
}

/*
int Cxif_key::save(string fname)
{
	int error = save_start();
	if (!error)
	{
		error = file32_write(fname, key_data(), key_size());
		save_finish();
	}
	return error;
}
*/

Cvirtual_binary Cxif_key::vdata() const
{
	Cvirtual_binary d;
	Cvirtual_binary s;
	byte* w = s.write_start(get_size());;
	save(w);
	unsigned long cb_d = s.size() + (s.size() + 999) / 1000 + 12;
	t_xif_header& header = *reinterpret_cast<t_xif_header*>(d.write_start(sizeof(t_xif_header) + cb_d));
	header.id = file_id;
	header.version = file_version_new;		
	header.size_uncompressed = s.size();
	compress(d.data_edit() + sizeof(t_xif_header), &cb_d, s.data(), s.size());
	d.size(sizeof(t_xif_header) + cb_d);
	return d;
}

