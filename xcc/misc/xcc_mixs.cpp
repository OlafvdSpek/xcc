#include "stdafx.h"
#include "xcc_mixs.h"

#include "xcc_log.h"

bool is_open = false;
static Cmix_file mixf[c_mix];
static int mix_rc[c_mix];

int Cxcc_mixs::open()
{
	if (is_open)
		return 0;
	is_open = true;
	int error = mixf[conquer_mix].open("conquer.mix");
	if (!error)
		error = mixf[desert_mix].open("desert.mix");
	if (!error)
		error = mixf[general_mix].open("general.mix");
	if (!error)
		error = mixf[temperate_mix].open("temperat.mix");
	if (!error)
		error = mixf[winter_mix].open("winter.mix");
	if (error)
		close();
	return error;
}

int Cxcc_mixs::close()
{
	if (!is_open)
		return 0;
	for (int i = 0; i < c_mix; i++)
	{
		if (mixf[i].is_open())
			mixf[i].close();
	}
	return 0;
}

Cmix_file& Cxcc_mixs::open_mix(t_mix t)
{
	mix_rc[t]++;
	return mixf[t];
}

void Cxcc_mixs::close_mix(t_mix t)
{
	mix_rc[t]--;
}

Cmix_file& Cxcc_mixs::get_conquer_mix()
{
	assert(is_open);
	return mixf[conquer_mix];
}

Cmix_file& Cxcc_mixs::get_general_mix()
{
	assert(is_open);
	return mixf[general_mix];
}

Cmix_file& Cxcc_mixs::get_theater_mix(t_theater_id theater)
{
	assert(is_open);
	switch (theater)
	{
	case t_desert:
		return mixf[desert_mix];
	case t_temperate:
		return mixf[temperate_mix];
	case t_winter:
		return mixf[winter_mix];
	};
	assert(false);
	return mixf[temperate_mix];
}

string Cxcc_mixs::get_theater_fname(t_theater_id theater)
{
	switch (theater)
	{
	case t_desert:
		return "desert";
	case t_temperate:
		return "temperat";
	case t_winter:
		return "winter";
	};
	assert(false);
	return "temperat";
}
