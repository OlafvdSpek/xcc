// database.cpp: implementation of the Cdatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "database.h"

#include <fstream>

/*
Cxcc_error Cdatabase::open()
{
	ifstream f("c:/temp/mysql_password.txt");
	string password;
	f >> password;
	return open(NULL, "xcc", password.c_str(), "xcc");
}
*/

Cxcc_error Cdatabase::open(const char* host, const char* user, const char* password, const char* database)
{
	return !mysql_init(&m_handle)
		|| !mysql_real_connect(&m_handle, host, user, password, database, MYSQL_PORT, NULL, 0)
		? Cxcc_error(mysql_error(&m_handle)) : Cxcc_error();
}

Cxcc_error Cdatabase::open(string host, string user, string password, string database)
{
	return open(host.c_str(), user.c_str(), password.c_str(), database.c_str());
}

Csql_result Cdatabase::query(const char* q)
{
	static ofstream f("c:/temp/mysql_query_log.txt");
	f << q << endl;
	if (mysql_query(&m_handle, q))
		throw Cxcc_error(mysql_error(&m_handle));
	return Csql_result(mysql_store_result(&m_handle));
}

Csql_result Cdatabase::query(const string& q)
{
	return query(q.c_str());
}

void Cdatabase::close()
{
	mysql_close(&m_handle);
}

int Cdatabase::insert_id()
{
	return mysql_insert_id(&m_handle);
}