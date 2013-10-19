#include "icon_form_decoder.h"

struct t_form_chunk_header
{
	__int32 id;
	__int32 m_size;

	string id_text() const
	{
		return string(reinterpret_cast<const char*>(&id), 4);
	}

	int size() const
	{
		return ntohl(m_size);
	}
};

Cicon_form_decoder::Cicon_form_decoder(const shared_data& s):
	m_s(s)
{
	m_sset = NULL;
	m_rpal = NULL;
	m_rtbl = NULL;
	do_form_chunk(s.data());
	assert(m_sset);
	assert(m_rpal);
	assert(m_rtbl);
	mc_icons = mcb_rtbl;
	assert(mcb_sset == 8 + 128 * mc_icons);
}

int Cicon_form_decoder::do_form_chunk(const byte* s)
{
	const byte* r = s;
	const t_form_chunk_header& h = *reinterpret_cast<const t_form_chunk_header*>(r);
	r += sizeof(t_form_chunk_header);
	assert(ntohl(h.id) == 'FORM');
	assert(ntohl(*reinterpret_cast<const __int32*>(r)) == 'ICON');
	r += 4;
	while (r < s + sizeof(t_form_chunk_header) + h.size())
		r += do_form_sub_chunk(r);
	return r - s;
}

int Cicon_form_decoder::do_form_sub_chunk(const byte* s)
{
	const byte* r = s;
	const t_form_chunk_header& h = *reinterpret_cast<const t_form_chunk_header*>(r);
	r += sizeof(t_form_chunk_header);
	switch (ntohl(h.id))
	{
	case 'SSET':
		m_sset = r;
		mcb_sset = h.size();
		r += h.size();
		break;
	case 'RPAL':
		m_rpal = r;
		mcb_rpal = h.size();
		r += h.size();
		break;
	case 'RTBL':
		m_rtbl = r;
		mcb_rtbl = h.size();
		r += h.size();
		break;
	default:
		r += h.size();
	}
	return r - s;
}

void Cicon_form_decoder::icon(int i, byte* w) const
{
	assert(i < mc_icons);
	int k = m_rtbl[i] << 4;
	assert(k + 16 <= mcb_rpal);
	const byte* t = m_rpal + k;
	const byte* r = m_sset + 8 + (i << 7);
	for (int j = 0; j < 0x80; j++)
	{
		int v = *r++;
		*w++ = t[v >> 4];
		*w++ = t[v & 0xf];
	}
}
