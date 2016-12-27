#include "stdafx.h"
#include "mix_file.h"

int main(int argc, char* argv[])
{
	cerr << " XCC MIX CLT, Copyright (C) Olaf van der Spek 2002         OlafvdSpek@GMail.Com" << endl
		<< endl;
	if (argc < 2)
	{
		cerr << "Syntax:" << endl
			<< "  xcc_mix_clt <mixfile> <file>" << endl;
		return 1;
	}
	Cmix_file mix;
	if (mix.open(argv[1]))
		return cerr << "Unable to open " << argv[1] << endl, 1;
	int error = 0;
	for (int i = 2; i < argc; i++)
	{
		Cvirtual_binary d = mix.get_vdata(argv[i]);
		if (!d.data())
			cerr << "Unable to open " << argv[i] << endl, error = 1;
		else if (d.export(argv[i]))
			cerr << "Unable to save " << argv[i] << endl, error = 1;
	}
	mix.close();
	return error;
}
