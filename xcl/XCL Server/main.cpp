#include <cassert>
#include <cstdio>
#ifdef _MSC_VER
#include <fcntl.h>
#include <io.h>
#endif
#include <iostream>
#include <string>
#include "db_config.h"
#include "xcl_database.h"

using namespace std;

static string get_env(const string& name)
{
	const char* p = getenv(name.c_str());
	return p ? p : "";
}

static void send_mail(const string& from, const string& to, const string& subject, const string& body)
{
#ifndef _MSC_VER
	FILE* mail = popen("/usr/sbin/sendmail -oi -t", "w");
	if (mail)
	{
		fprintf(mail, "Content-Type: text/html\n");
		fprintf(mail, "From: %s\n", from.c_str());
		fprintf(mail, "To: %s\n", to.c_str());
		fprintf(mail, "Subject: %s\n", subject.c_str());
		fputs(body.c_str(), mail);
		pclose(mail);
	}
#endif
}

void process(const Cvirtual_binary& s)
{
	try
	{
		Cxcl_database database;
		Cxcc_error error;
		if (error = database.open(mysql_host, mysql_user, mysql_pass, mysql_db))
			throw error;
		Csql_query q(database);
		q.write("insert into xcl_input (d, ipa) values (%s, %s)");
		q.pe(s);
		q.pe(get_env("REMOTE_ADDR"));
		q.execute();
		database.insert_game(s);
	}
	catch (Cxcc_error error)
	{
		send_mail("XCL@XCC.TMFWeb.NL", "PHP@XCC.TMFWeb.NL", "Error in XCL server", error.message());
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