// cgi_input.cpp: implementation of the Ccgi_input class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <iostream>
#include "cgi.h"
#include "crc.h"
#include "multi_line.h"
#include "string_conversion.h"

const char* cgi_error_text[] = {
	"Error: none",
	"Error: unsupported request method",
	"Error: unsupported content type",
	"Error: unsupported content length",
	"Error: unable to read content",
	"Error: server name unavailable",
	"Error: script name unavailable"};

string get_env(const string& name)
{
	const char* p = getenv(name.c_str());
	return p ? p : "";
}

static t_request_method get_request_method()
{
	const string v = to_lower(get_env("REQUEST_METHOD"));
	if (v == "get")
		return rm_get;
	else if (v == "post")
		return rm_post;
	return rm_unknown;
}

static t_content_type get_content_type()
{
	const string v = to_lower(get_env("CONTENT_TYPE"));
	if (v == "application/x-www-form-urlencoded")
		return ct_application;
	/*
	Cmulti_line l = v;
	if (l.get_next_line(';') == "multipart/form-data")
		return ct_multipart;
	*/
	return ct_unknown;
}

static string get_boundary()
{
	Cmulti_line l = to_lower(get_env("CONTENT_TYPE"));;
	l.get_next_line("boundary=");
	return l.get_next_line(';');
}

static int hex_decode(char v)
{
	v = tolower(v);
	if (v < 'a')
	{
		if (v < '0')
		{
			return -1;			
		}
		else
		{
			v -= '0';
			return v < 10 ? v : -1;
		}
		
	}
	else
	{
		v -= 'a';
		return v < 6 ? 10 + v : -1;
	}
};

static string hex_encode(int l, int v)
{
	string r;
	while (l--)
	{
		char c = v & 0xf;
		v >>= 4;
		c += c < 10 ? '0' : 'a' - 10;
		r = c + r;
	}
	return r;
};

string uri_encode(const string v)
{
	string r;
	int i = 0;
	while (i < v.length())
	{
		char c = v[i++];
		if (isalpha(c) || isdigit(c))
			r += c;
		else
		{
			switch (c)
			{
			case ' ':
				r += '+';
				break;
			case '-':
			case ',':
			case '.':
			case '@':
			case '_':
				r += c;
				break;
			default:
				r += "%" + hex_encode(2, c);
			}
		}
	}
	return r;
};

string uri_decode(const string& v)
{
	string r;
	int i = 0;
	while (i < v.length())
	{
		char c = v[i++];
		switch (c)
		{
		case '%':
			{
				if (i + 2 > v.length())
					return "";
				int l = v[i++];
				r += hex_decode(l) << 4 | hex_decode(v[i++]);
				break;
			}
		case '+':
			r += ' ';
			break;
		default:
			r += c;
		}
	}
	return r;
};

string web_encode(const string& v, bool add_br)
{
	string r;
	int i = 0;
	while (i < v.length())
	{
		char c = v[i++];
		switch (c)
		{
		case '\r':
			break;
		case '\n':
			if (add_br)
				r += "<br>";
			r += '\n';
			break;
		case '<':
			r += "&lt;";
			break;
		case '>':
			r += "&gt;";
			break;
		case '&':
			r += "&amp;";
			break;
		case '"':
			r += "&quot;";
			break;
		default:
			r += c;
		}
	}
	return r;
}

string web_decode(const string& v)
{
	string r;
	r = v;
	return r;
}

t_cgi_input get_cgi_pairs(const string& pairs)
{
	t_cgi_input r;
	int i = 0;
	while (i < pairs.length())
	{
		int p = pairs.find('&', i);
		string v;
		if (p != string::npos)
		{
			v = pairs.substr(i, p - i);
			i = p + 1;
		}
		else
		{
			v = pairs.substr(i);
			i = pairs.length();
		}
		p = v.find('=');
		if (p == string::npos)
			r[uri_decode(v)] = "";
		else
			r[uri_decode(v.substr(0, p))] = uri_decode(v.substr(p + 1));
	}
	return r;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ccgi_input::Ccgi_input()
{
}

t_cgi_error Ccgi_input::read()
{
	const string server_name = get_env("SERVER_NAME");
	const string script_name = get_env("SCRIPT_NAME");
	if (server_name.empty())
		return cgi_error_server_name_unavailable;
	if (script_name.empty())
		return cgi_error_script_name_unavailable;
	m_url = "http://" + server_name + script_name;
	t_request_method rm = get_request_method();
	if (rm == rm_get)
		m_input = get_cgi_pairs(get_env("QUERY_STRING"));
	else if (rm == rm_post)
	{
		int cb_data = atoi(get_env("CONTENT_LENGTH").c_str());
		if (!cb_data)
			return cgi_error_unsupported_content_length;		
		t_content_type ct = get_content_type();
		if (ct == ct_application)
		{
			if (cb_data > 64 << 10)
				return cgi_error_unsupported_content_length;
			char* data = new char[cb_data + 1];
			cin.read(data, cb_data);
			if (cin.good())
			{
				data[cb_data] = 0;
				m_input = get_cgi_pairs(data);
				delete[] data;
			}
			else
			{
				delete[] data;
				return cgi_error_unable_to_read_content;
			}
		}
		else if (ct == ct_multipart)
		{
			if (cb_data > 1 << 20)
				return cgi_error_unsupported_content_length;
			t_cgi_error error = cgi_error_none;
			char* data = new char[cb_data];
			cin.read(data, cb_data);
			if (cin.good())
			{
			}
			else
				error = cgi_error_unable_to_read_content;
			delete[] data;
			return error;
		}
		else
			return cgi_error_unsupported_content_type;
	}
	else
		return cgi_error_unsupported_request_method;
	return cgi_error_none;
}

string Ccgi_input::get_cookie()
{
	return get_env("HTTP_COOKIE");
}

string Ccgi_input::get_value(const string& name) const
{
	t_cgi_input::const_iterator i = m_input.find(name);
	return i == m_input.end() ? "" : i->second;
}

int Ccgi_input::get_value_int(const string& name) const
{
	return atoi(get_value(name).c_str());
}

bool Ccgi_input::has_name(const string& name) const
{
	t_cgi_input::const_iterator i = m_input.find(name);
	return i != m_input.end();
}

bool Ccgi_input::has_value(const string& name) const
{
	t_cgi_input::const_iterator i = m_input.find(name);
	return i != m_input.end() && !i->second.empty();
}

int get_hash(const string& v)
{
	Ccrc crc;
	crc.init();
	crc.do_block(v.c_str(), v.length());
	return crc.get_crc();
}

string xor_encode(const string& v)
{
	string r;
	for (int i = 0; i < v.length(); i++)
	{
		unsigned char c = v[i] ^ 0x99;
		r += 'A' + (c >> 4);
		r += 'A' + (c & 0xf);
	}
	return r;
}

string xor_decode(const string& v)
{
	string r;
	char l;
	for (int i = 0; i < v.length(); i++)
	{
		char c = (v[i] - 'A') & 0xf;
		if (i & 1)
			r += (l | c) ^ 0x99;
		else
			l = c << 4;
	}
	return r;
}