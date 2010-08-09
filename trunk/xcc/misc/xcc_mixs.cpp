#include "stdafx.h"
#include "xcc_mixs.h"

#include "xcc_log.h"

enum t_mix
{
	conquer_mix,
	desert_mix,
	general_mix,
	temperate_mix,
	winter_mix
};

static array<Cmix_file, winter_mix + 1> mixf;

int Cxcc_mixs::open()
{
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

void Cxcc_mixs::close()
{
	BOOST_FOREACH(auto& i, mixf)
		i.close();
}

Cmix_file& Cxcc_mixs::conquer()
{
	return mixf[conquer_mix];
}

Cmix_file& Cxcc_mixs::general()
{
	return mixf[general_mix];
}

Cmix_file& Cxcc_mixs::theater(t_theater_id theater)
{
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

string Cxcc_mixs::theater_fname(t_theater_id theater)
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
