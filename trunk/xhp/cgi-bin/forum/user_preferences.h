// user_preferences.h: interface for the Cuser_preferences class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USER_PREFERENCES_H__365CB8A1_C528_11D4_B3F5_0000F81AF9BE__INCLUDED_)
#define AFX_USER_PREFERENCES_H__365CB8A1_C528_11D4_B3F5_0000F81AF9BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cgi.h"
#include "cookie.h"

class Cuser_preferences  
{
public:
	Cuser_preferences();
	void load(const Ccookie& cookie);
	void process(const Ccgi_input& cgi, Ccookie& cookie);

	int newest_limit;
	bool show_signatures;
	bool show_smilies;
	bool show_c_posts;
	bool show_date;
	bool show_updated_by;
	bool show_updated_on;
	bool show_top_links;
	bool show_bottom_links;
};

#endif // !defined(AFX_USER_PREFERENCES_H__365CB8A1_C528_11D4_B3F5_0000F81AF9BE__INCLUDED_)
