#include "stdafx.h"
#include "crc.h"

int compute_crc(const void* d, int cb_d)
{
  boost::crc_32_type crc;
  crc.process_bytes(d, cb_d);
	return crc();
}
