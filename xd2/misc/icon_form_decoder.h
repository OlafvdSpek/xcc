#pragma once

class Cicon_form_decoder  
{
public:
	int do_form_chunk(const byte* s);
	int do_form_sub_chunk(const byte* s);
	void icon(int i, byte* w) const;
	Cicon_form_decoder(const Cvirtual_binary& s);

	int c_icons() const
	{
		return mc_icons;
	}
private:
	const Cvirtual_binary m_s;
	const byte* m_sset;
	const byte* m_rpal;
	const byte* m_rtbl;
	int mcb_sset;
	int mcb_rpal;
	int mcb_rtbl;
	int mc_icons;
};
