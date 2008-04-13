#pragma once

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

int compute_crc(const void* d, int cb_d);
