#include "stdafx.h"
#include <minmax.h>
#include "cgi.h"
#include "multi_line.h"
#include "string_conversion.h"
#include "web_tools.h"

bool web_is_protocol_name(string v)
{
	v = to_lower(v);
	if (v != "ftp" && v != "http")
		return false;
	return true;
}

bool web_is_server_name(const string& v)
{
	int c_parts = 0;
	Cmulti_line l = v;
	while (!l.empty())
	{
		if (l.get_next_line('.').empty())
			return false;
		c_parts++;
	}
	return c_parts >= 2;
}

bool web_is_mail(const string& v)
{
	int a = v.find('@');
	if (a < 1 || v.length() - a < 1)
		return false;
	a++;
	if (!web_is_server_name(v.substr(a)))
		return false;
	return true;
}

bool web_is_link(const string& v)
{
	Cmulti_line l = v;
	if (!web_is_protocol_name(l.get_next_line("://")))
		return false;
	if (!web_is_server_name(l.get_next_line('/')))
		return false;
	return true;
}

Chtml web_name(const string& name, const string& mail)
{
	if (name.empty())
		return web_is_mail(mail) ? a("Anonymous", "href=\"mailto:Anonymous <" + web_encode(mail) + ">\"") : "Anonymous";
	return web_is_mail(mail) ? a(web_encode(name), "href=\"mailto:" + web_encode(name) + " <" + web_encode(mail) + ">\"") : static_cast<Chtml>(web_encode(name));
}

Chtml web_link(const string& link_title, const string& link)
{
	return a(web_encode(link_title.empty() ? link : link_title), "target=_top href=\"" + web_encode(link) + "\"");
}

Chtml web_magic_anchors(const string& v, bool keep_protocol, const string& protocol)
{
	string r;
	int l = 0;
	while (l < v.length())
	{
		int p = v.find(protocol, l);
		if (p == string::npos)
		{
			r += v.substr(l);
			break;
		}
		r += v.substr(l, p - l);
		int q = p;
		while (q < v.length())
		{
			char c = v[q];
			if (c == '\n' || c == ' ' || c == '<' || c == '&')
				break;
			q++;
		}
		if (v[q - 1] == ',' || v[q - 1] == '.')
			q--;
		if (v[q - 1] == ')')
			q--;
		string href = v.substr(p, q - p);
		r += web_link(keep_protocol ? href : href.substr(protocol.length()), href);
		l = q;
	}
	return r;
}

Chtml web_magic_anchors(const string& v)
{
	return web_magic_anchors(web_magic_anchors(web_magic_anchors(v, true, "ftp://"), true, "http://"), false, "mailto:");
}