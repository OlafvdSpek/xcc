// authentication.h: interface for the Cauthentication class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTHENTICATION_H__874F0100_7F50_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_AUTHENTICATION_H__874F0100_7F50_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <set>
#include "file31.h"

using namespace std;

class Clogin_entry
{
public:
	Clogin_entry(string name, string password);

	string name() const
	{
		return m_name;
	}

	string password() const
	{
		return m_password;
	}
private:
	string m_name;
	string m_password;
};

enum t_group_flags
{
	gf_none,
	gf_may_activate_user = 1,
	gf_may_deactivate_user = 2,
	gf_may_enable_user = 4,
	gf_may_disable_user = 8,
	gf_may_update_user = 0x10,
	gf_may_list_users = 0x20
};

class Cgroup
{
public:
	Cgroup();
	void name(string v);
	void owner(int v);
	void flags(int v);

	string name() const
	{
		return m_name;
	}

	int owner() const
	{
		return m_owner;
	}
	
	int flags() const
	{
		return m_flags;
	}
private:
	string m_name;
	int m_owner;
	int m_flags;
};

enum t_user_flags
{
	uf_none,
	uf_uin = 1,
	uf_link_title = 2,
	uf_link = 4,
	uf_active = 8,
	uf_enabled = 0x10,
	uf_may_create_group = 0x20,
	uf_may_create_user = 0x40,
	uf_may_update_user_gl = 0x80,
	uf_may_update_group = 0x100
};

class Cuser
{
public:
	typedef set<int> t_gl;

	Cuser();
	void name(string v);
	void mail(string v);
	void password_hash(int v);
	void uin(int v);
	void link_title(string v);
	void link(string v);
	void activate_code(int v);
	void flags(int v);
	void gl(t_gl v);
	void add_flag(int v);
	void remove_flag(int v);
	void add_group(int v);
	void remove_group(int v);

	string name() const
	{
		return m_name;
	}

	string mail() const
	{
		return m_mail;
	}

	int password_hash() const
	{
		return m_password_hash;
	}

	int uin() const
	{
		return m_uin;
	}

	string link_title() const
	{
		return m_link_title;
	}

	string link() const
	{
		return m_link;
	}

	int activate_code() const
	{
		return m_activate_code;
	}

	int flags() const
	{
		return m_flags;
	}

	t_gl gl() const
	{
		return m_gl;
	}
private:
	string m_name;
	string m_mail;
	int m_password_hash;
	int m_uin;
	string m_link_title;
	string m_link;
	int m_activate_code;
	int m_flags;
	t_gl m_gl;
};

class Cauthentication  
{
public:
	enum t_error 
	{
		e_none, 
		e_forbidden, 
		e_unknown,
		e_name_in_use, 
		e_mail_in_use, 
		e_uin_in_use,
		e_invalid_name, 
		e_invalid_mail, 
		e_invalid_password, 
		e_invalid_uin, 
		e_invalid_link_title, 
		e_invalid_link, 
		e_invalid_gl, 
		e_invalid_slot,
		e_unknown_user,
		e_user_deactive, 
		e_user_disabled,
		e_read_failed,
		e_write_failed,
		e_invalid_activate_code
	};

	static const char* e_text[];
	typedef map<int, Cgroup> t_gl;
	typedef map<int, Cuser> t_ul;

	Cauthentication();
	t_error activate_user(Clogin_entry e, int activate_code);
	t_error activate_user(int slot);
	t_error deactivate_user(int slot);
	t_error enable_user(int slot);
	t_error disable_user(int slot);
	t_error add_user_to_group(int user_slot, int group_slot);
	t_error remove_user_from_group(int user_slot, int group_slot);
	t_error create_group(Cgroup e);
	t_error create_user(Cuser e);
	t_error update_user(int slot, Cuser e);
	t_error login(Clogin_entry e);
	t_error logout();
	int find_group_by_name(string v) const;
	int find_user_by_name(string v) const;
	int find_user_by_mail(string v) const;
	int find_user_by_uin(int v) const;
	static int password_hash(string v);
	int open_log(string fname);
	int read(Cfile31& f);
	int write(Cfile31& f);

	t_gl gl() const
	{
		return m_gl;
	}

	t_ul ul() const
	{
		return m_ul;
	}

	bool is_valid_group(int slot) const
	{
		return slot && m_gl.find(slot) != m_gl.end();
	}
	
	bool is_valid_user(int slot) const
	{
		return slot && m_ul.find(slot) != m_ul.end();
	}	

	Cuser current_user() const
	{
		return user(m_current_user);
	}

	Cgroup group(int slot) const
	{
		t_gl::const_iterator i = m_gl.find(slot);
		return i == m_gl.end() ? Cgroup() : i->second;
	}

	Cuser user(int slot) const
	{
		t_ul::const_iterator i = m_ul.find(slot);
		return i == m_ul.end() ? Cuser() : i->second;
	}
protected:
	void group(int i, Cgroup e);
	void user(int i, Cuser e);
	t_error error(t_error v, const char* fn, string t);
	bool find_gf(Cuser e, int v) const;
	void log(string v);
private:
	int m_current_user;
	t_gl m_gl;
	t_ul m_ul;
	ofstream m_log;
};

#endif // !defined(AFX_AUTHENTICATION_H__874F0100_7F50_11D4_B606_0000B4936994__INCLUDED_)
