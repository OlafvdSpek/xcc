// user_preferences.cpp: implementation of the Cuser_preferences class.
//
//////////////////////////////////////////////////////////////////////

#include "multi_line.h"
#include "string_conversion.h"
#include "user_preferences.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cuser_preferences::Cuser_preferences()
{
	newest_limit = 12;
	show_signatures = true;
	show_smilies = true;
	show_c_posts = true;
	show_date = true;
	show_updated_by = false;
	show_updated_on = false;
	show_top_links = true;
	show_bottom_links = true;
}

static void load_bool(Cmulti_line& l, bool& value)
{
	if (!l.empty())
		value = l.get_next_int();
}

static void load_int(Cmulti_line& l, int& value)
{
	if (!l.empty())
		value = l.get_next_int();
}

void Cuser_preferences::load(const Ccookie& cookie)
{
	Cmulti_line l = cookie.get_value("user_preferences");
	load_bool(l, show_signatures);
	load_bool(l, show_smilies);
	load_bool(l, show_c_posts);
	load_bool(l, show_date);
	load_bool(l, show_updated_by);
	load_bool(l, show_updated_on);
	load_bool(l, show_top_links);
	load_bool(l, show_bottom_links);
	load_int(l, newest_limit);
}

void Cuser_preferences::process(const Ccgi_input& cgi, Ccookie& cookie)
{
	newest_limit = cgi.get_value_int("newest_limit");
	show_signatures = cgi.has_value("show_signatures");
	show_smilies = cgi.has_value("show_smilies");
	show_c_posts = cgi.has_value("show_c_posts");
	show_date = cgi.has_value("show_date");
	show_updated_by = cgi.has_value("show_updated_by");
	show_updated_on = cgi.has_value("show_updated_on");
	cookie.set_value("user_preferences", n(show_signatures) + ',' + n(show_smilies) + ',' + n(show_c_posts) 
		+ ',' + n(show_date) + ',' + n(show_updated_by) + ',' + n(show_updated_on) + ',' + n(show_top_links) 
		+ ',' + n(show_bottom_links) + ',' + n(newest_limit));
}