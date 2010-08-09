#include "stdafx.h"
#include "xcc_mixs.h"

#include "xcc_log.h"

static Cmix_file conquer_mix;
static Cmix_file desert_mix;
static Cmix_file general_mix;
static Cmix_file temperate_mix;
static Cmix_file winter_mix;

int Cxcc_mixs::open()
{
	int error = conquer_mix.open("conquer.mix");
	if (!error)
		error = desert_mix.open("desert.mix");
	if (!error)
		error = general_mix.open("general.mix");
	if (!error)
		error = temperate_mix.open("temperat.mix");
	if (!error)
		error = winter_mix.open("winter.mix");
	return error;
}

Cmix_file& Cxcc_mixs::conquer()
{
	return conquer_mix;
}

Cmix_file& Cxcc_mixs::general()
{
	return general_mix;
}

Cmix_file& Cxcc_mixs::theater(t_theater_id theater)
{
	switch (theater)
	{
	case t_desert:
		return desert_mix;
	case t_temperate:
		return temperate_mix;
	case t_winter:
		return winter_mix;
	};
	assert(false);
	return temperate_mix;
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

string Cxcc_mixs::theater_fext(t_theater_id theater)
{
	return '.' + theater_fname(theater).substr(0, 3);
}
