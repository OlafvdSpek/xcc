#include <cassert>
#include <cstdio>
#ifdef _MSC_VER
#include <fcntl.h>
#include <io.h>
#endif
#include <iostream>
#include <string>
#include "wol/game_result.h"
#include "wol/ra2_names.h"
#include "db_config.h"
#include "string_conversion.h"
#include "virtual_binary.h"
#include "xcl_database.h"

using namespace std;

static string get_env(const string& name)
{
	const char* p = getenv(name.c_str());
	return p ? p : "";
}

void process(const Cvirtual_binary& s)
{
	try
	{
		Cxcl_database database;
		Cxcc_error error;
		if (error = database.open("localhost", "xccu", "Zo30zr6", "xccu"))
			throw error;
		{
			Csql_query q(database);
			q.write("insert into xcl_input (d, ipa) values (%s, %s)");
			q.pe(s);
			q.pe(get_env("REMOTE_ADDR"));
			q.execute();
			Cgame_result gr;
			if (gr.write(s) && gr.get_int("dura") > 90)
				database.insert_game(gr);
		}
	}
	catch (Cxcc_error error)
	{
	}
}

int main()
{
	cout << "Content-type: text/html" << endl
		<< endl;
	int cb_s = atoi(get_env("CONTENT_LENGTH").c_str());
	if (cb_s < 1 || cb_s > 16 << 10)
		return 0;
#ifdef _MSC_VER
	_setmode(fileno(stdin), _O_BINARY);
#endif
	Cvirtual_binary s;
	if (cb_s != fread(reinterpret_cast<char*>(s.write_start(cb_s)), 1, cb_s, stdin))
		return 0;
	process(s);
	return 0;
}