// crc.h: interface for the Ccrc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRC_H__41310302_D0B7_11D3_B604_0000B4936994__INCLUDED_)
#define AFX_CRC_H__41310302_D0B7_11D3_B604_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Ccrc
{
public:
	void do_block(const void* data, int size);

	void init()
	{
		m_crc = 0;
	}

	int get_crc() const
	{
		return m_crc;
	}
private:
	unsigned int m_crc;
};

#endif // !defined(AFX_CRC_H__41310302_D0B7_11D3_B604_0000B4936994__INCLUDED_)
