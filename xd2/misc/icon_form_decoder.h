// icon_form_decoder.h: interface for the Cicon_form_decoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICON_FORM_DECODER_H__31D6E515_F86D_4870_97D9_FD1C755B4E41__INCLUDED_)
#define AFX_ICON_FORM_DECODER_H__31D6E515_F86D_4870_97D9_FD1C755B4E41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "virtual_binary.h"

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

#endif // !defined(AFX_ICON_FORM_DECODER_H__31D6E515_F86D_4870_97D9_FD1C755B4E41__INCLUDED_)
