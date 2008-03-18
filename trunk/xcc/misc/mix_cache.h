#pragma once

namespace mix_cache
{
	int load();
	int save();
	const void* get_data(int crc);
	void set_data(int crc, const void* data, int size);
};
