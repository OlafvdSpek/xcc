// seed_decoder.h: interface for the Cseed_decoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEED_DECODER_H__34E4BABD_CF9B_49F7_9EC2_E4142DFF369D__INCLUDED_)
#define AFX_SEED_DECODER_H__34E4BABD_CF9B_49F7_9EC2_E4142DFF369D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Cseed_decoder  
{
public:
	static void decode(int seed, byte* map);
};

#endif // !defined(AFX_SEED_DECODER_H__34E4BABD_CF9B_49F7_9EC2_E4142DFF369D__INCLUDED_)
