// authentication.cpp: implementation of the Cauthentication class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "authentication.h"
#include "multi_line.h"

Clogin_entry::Clogin_entry(string name, string password)
{
	m_name = name;
	m_password = password;
}

Cgroup::Cgroup()
{
	m_name = "_no group_";
	m_owner = 0;
	m_flags = gf_none;
}

void Cgroup::name(string v)
{
	m_name = v;
}

void Cgroup::owner(int v)
{
	m_owner = v;
}

void Cgroup::flags(int v)
{
	m_flags = v;
}

Cuser::Cuser()
{
	m_name = "_no user_";
	m_password_hash = 0;
	m_uin = 0;
	m_activate_code = 0;
	m_flags = uf_enabled;
}

void Cuser::name(string v)
{
	m_name = v;
}

void Cuser::mail(string v)
{
	m_mail = v;
}

void Cuser::password_hash(int v)
{
	m_password_hash = v;
}

void Cuser::uin(int v)
{
	m_uin = v;
	if (m_uin)
		m_flags |= uf_uin;
	else
		m_flags &= ~uf_uin;
}

void Cuser::link_title(string v)
{
	m_link_title = v;
	if (!m_link_title.empty())
		m_flags |= uf_link_title;
	else
		m_flags &= ~uf_link_title;
}

void Cuser::link(string v)
{
	m_link = v;
	if (!m_link.empty())
		m_flags |= uf_link;
	else
		m_flags &= ~uf_link;
}

void Cuser::activate_code(int v)
{
	m_activate_code = v;
}

void Cuser::flags(int v)
{
	m_flags = v;
}

void Cuser::gl(t_gl v)
{
	m_gl = v;
}

void Cuser::add_flag(int v)
{
	m_flags |= v;
}

void Cuser::remove_flag(int v)
{
	m_flags &= ~v;
}

void Cuser::add_group(int v)
{
	m_gl.insert(v);
}

void Cuser::remove_group(int v)
{
	m_gl.erase(v);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* Cauthentication::e_text[] =
{
	"none", 
	"forbidden", 
	"unknown",
	"name in use",
	"mail in use", 
	"uin in use",
	"invalid name", 
	"invalid mail", 
	"invalid password", 
	"invalid uin", 
	"invalid link title", 
	"invalid link", 
	"invalid gl", 
	"invalid slot",
	"unknown user",
	"user deactive", 
	"user disabled",
	"read failed",
	"write failed"
};

Cauthentication::Cauthentication()
{
	m_current_user = 0;
	m_gl[0];
	m_ul[0].flags(m_ul[0].flags() | uf_may_create_user);
}

int Cauthentication::open_log(string fname)
{
	m_log.open(fname.c_str(), ios::app | ios::out);
	return m_log.fail();
}

void Cauthentication::log(string v)
{
	m_log << v << endl;
}

Cauthentication::t_error Cauthentication::error(t_error error, const char* fn, string t)
{
	m_log << fn;
	if (error != e_none)
		m_log << " failed";
	if (!t.empty())
		m_log << ": " << t;
	m_log << endl;
	return error;
}

int Cauthentication::password_hash(string v)
{
	int r = 0;
	for (int i = 0; i < v.length(); i++)
	{
		r += v[i];
	}
	return r;
}

void Cauthentication::group(int i, Cgroup e)
{
	m_gl[i] = e;
}

void Cauthentication::user(int i, Cuser e)
{
	m_ul[i] = e;
}

bool is_valid_id(string v)
{
	if (v.length() < 4)
		return false;
	for (int i = 0; i < v.length(); i++)
	{
		if ((v[i] < '0' || v[i] > '9') && (v[i] < 'A' || v[i] > 'Z') && (v[i] < 'a' || v[i] > 'z'))
		{
			switch (v[i])
			{
			case ' ':
			case '.':
			case '@':
				break;
			default:
				return false;
			}
		}
	}
	return true;
}

bool is_valid_mail_address(string v)
{
	return is_valid_id(v);
	for (int i = 0; i < v.length(); i++)
	{
		if (v[i] < 0x20)
			return false;
	}
}

string trim_id(string v)
{
	string r;
	for (int i = 0; i < v.length(); i++)
	{
		if (v[i] != ' ')
			r += tolower(v[i]);
	}
	return r;
}

int Cauthentication::find_group_by_name(string v) const
{
	v = trim_id(v);
	for (t_gl::const_iterator i = m_gl.begin(); i != m_gl.end(); i++)
	{
		if (trim_id(i->second.name()) == v)
			return i->first;
	}
	return 0;
}

int Cauthentication::find_user_by_name(string v) const
{
	v = trim_id(v);
	for (t_ul::const_iterator i = m_ul.begin(); i != m_ul.end(); i++)
	{
		if (trim_id(i->second.name()) == v)
			return i->first;
	}
	return 0;
}

int Cauthentication::find_user_by_mail(string v) const
{
	v = trim_id(v);
	for (t_ul::const_iterator i = m_ul.begin(); i != m_ul.end(); i++)
	{
		if (trim_id(i->second.mail()) == v)
			return i->first;
	}
	return 0;
}

int Cauthentication::find_user_by_uin(int v) const
{
	if (!v)
		return 0;
	for (t_ul::const_iterator i = m_ul.begin(); i != m_ul.end(); i++)
	{
		if (i->second.uin() == v)
			return i->first;
	}
	return 0;
}

bool Cauthentication::find_gf(Cuser e, int v) const
{
	for (Cuser::t_gl::const_iterator i = e.gl().begin(); i != e.gl().end(); i++)
	{
		if (group(*i).flags() & v)
			return true;
	}
	return false;
}

Cauthentication::t_error Cauthentication::activate_user(Clogin_entry e, int activate_code)
{
	const char* fn = "activate_user";
	if (!is_valid_id(e.name()))
		return error(e_invalid_name, fn, "invalid name");
	int i = find_user_by_name(e.name());
	if (!i)
		return error(e_unknown_user, fn, "unknown user: " + e.name());
	if (activate_code != user(i).activate_code())
		return error(e_invalid_activate_code, fn, "invalid activate code: " + e.name());
	m_ul[i].add_flag(uf_active);
	return error(e_none, fn, e.name());
}

Cauthentication::t_error Cauthentication::login(Clogin_entry e)
{
	const char* fn = "login";
	if (!is_valid_id(e.name()))
		return error(e_invalid_name, fn, "invalid name");
	int i = find_user_by_name(e.name());
	if (!i)
		return error(e_unknown_user, fn, "unknown user: " + e.name());
	if (password_hash(e.password()) != user(i).password_hash())
		return error(e_invalid_password, fn, "invalid password: " + e.name());
	if (~user(i).flags() & uf_active)
		return error(e_user_deactive, fn, "user deactive: " + e.name());;
	if (~user(i).flags() & uf_enabled)
		return error(e_user_disabled, fn, "user disabled: " + e.name());;
	m_current_user = i;
	return error(e_none, fn, e.name());
}

Cauthentication::t_error Cauthentication::create_group(Cgroup e)
{
	const char* fn = "create_group";
	if (~current_user().flags() & uf_may_create_group)
		return error(e_forbidden, fn, "forbidden");
	if (!is_valid_id(e.name()))
		return error(e_invalid_name, fn, "invalid name");;
	if (find_group_by_name(e.name()))
		return error(e_name_in_use, fn, "name in use");;
	e.owner(m_current_user);
	group(m_gl.rbegin()->first + 1, e);
	return error(e_none, fn, "");
}

Cauthentication::t_error Cauthentication::create_user(Cuser e)
{
	const char* fn = "create_user";
	if (~current_user().flags() & uf_may_create_user)
		return error(e_forbidden, fn, "forbidden");
	if (!is_valid_id(e.name()))
		return error(e_invalid_name, fn, "invalid name");
	if (!is_valid_mail_address(e.mail()))
		return error(e_invalid_mail, fn, "invalid mail");
	if (e.gl().size())
		return error(e_invalid_gl, fn, "non empty group list");
	if (find_user_by_name(e.name()))
		return error(e_name_in_use, fn, "name in use");
	if (find_user_by_mail(e.mail()))
		return error(e_mail_in_use, fn, "mail in use");
	if (find_user_by_uin(e.uin()))
		return error(e_uin_in_use, fn, "uin in use");
	user(m_ul.rbegin()->first + 1, e);
	return error(e_none, fn, "");
}

Cauthentication::t_error Cauthentication::update_user(int slot, Cuser e)
{
	const char* fn = "update_user";
	if (m_current_user != slot && !find_gf(current_user(), gf_may_update_user))
		return error(e_forbidden, fn, "forbidden");
	if (!is_valid_user(slot))
		return error(e_invalid_slot, fn, "invalid_slot");
	if (!is_valid_id(e.name()))
		return error(e_invalid_name, fn, "invalid name");
	if (!is_valid_mail_address(e.mail()))
		return error(e_invalid_mail, fn, "invalid mail");
	Cuser old_user = user(slot);
	m_ul.erase(slot);
	t_error er = e_none;
	if (!er && find_user_by_name(e.name()))
		er = error(e_name_in_use, fn, "name in use"); 
	if (!er && find_user_by_mail(e.mail()))
		er = error(e_mail_in_use, fn, "mail in use");
	if (!er && find_user_by_uin(e.uin()))
		er = error(e_uin_in_use, fn, "uin in use");
	if (er)
		return er;
	{
		old_user.name(e.name());
		old_user.mail(e.mail());
		old_user.uin(e.uin());
		old_user.link_title(e.link_title());
		old_user.link(e.link());
	}
	m_ul[slot] = old_user;
	return error(e_none, fn, "");
}

Cauthentication::t_error Cauthentication::activate_user(int slot)
{
	const char* fn = "activate_user";
	if (!find_gf(current_user(), gf_may_activate_user))
		return error(e_forbidden, fn, "forbidden");
	if (!is_valid_user(slot))
		return error(e_invalid_slot, fn, "invalid_slot");
	m_ul[slot].add_flag(uf_active);
	return error(e_none, fn, user(slot).name());
}

Cauthentication::t_error Cauthentication::deactivate_user(int slot)
{
	const char* fn = "deactivate_user";
	if (!find_gf(current_user(), gf_may_deactivate_user))
		return error(e_forbidden, fn, "forbidden");
	if (!is_valid_user(slot))
		return error(e_invalid_slot, fn, "invalid_slot");
	m_ul[slot].remove_flag(uf_active);
	return error(e_none, fn, user(slot).name());
}

Cauthentication::t_error Cauthentication::enable_user(int slot)
{
	const char* fn = "enable_user";
	if (!find_gf(current_user(), gf_may_enable_user))
		return error(e_forbidden, fn, "forbidden");
	if (!is_valid_user(slot))
		return error(e_invalid_slot, fn, "invalid_slot");
	m_ul[slot].add_flag(uf_enabled);
	return error(e_none, fn, user(slot).name());
}

Cauthentication::t_error Cauthentication::disable_user(int slot)
{
	const char* fn = "disable_user";
	if (!find_gf(current_user(), gf_may_disable_user))
		return error(e_forbidden, fn, "forbidden");
	if (!is_valid_user(slot))
		return error(e_invalid_slot, fn, "invalid_slot");
	m_ul[slot].remove_flag(uf_enabled);
	return error(e_none, fn, user(slot).name());
}

Cauthentication::t_error Cauthentication::add_user_to_group(int user_slot, int group_slot)
{
	const char* fn = "add_user_to_group";
	if (~current_user().flags() & uf_may_update_user_gl)
		return error(e_forbidden, fn, "forbidden");
	if (!is_valid_user(group_slot) || !is_valid_user(user_slot))
		return error(e_invalid_slot, fn, "invalid_slot");
	m_ul[user_slot].add_group(group_slot);
	return error(e_none, fn, user(user_slot).name() + " to " + group(group_slot).name());
}

Cauthentication::t_error Cauthentication::remove_user_from_group(int user_slot, int group_slot)
{
	const char* fn = "remove_user_from_group";
	if (~current_user().flags() & uf_may_update_user_gl)
		return error(e_forbidden, fn, "forbidden");
	if (!is_valid_user(group_slot) || !is_valid_user(user_slot))
		return error(e_invalid_slot, fn, "invalid_slot");
	m_ul[user_slot].remove_group(group_slot);
	return error(e_none, fn, user(user_slot).name() + " to " + group(group_slot).name());
}

Cauthentication::t_error Cauthentication::logout()
{
	const char* fn = "logout";
	m_current_user = 0;
	return error(e_none, fn, "");
}

int Cauthentication::read(Cfile31& f)
{
	const char* fn = "read";
	f.seek(0);
	f.read_int();
	if (f.fail())
		return error(e_read_failed, fn, "a");
	{
		int size = f.read_int();
		if (f.fail())
			return error(e_read_failed, fn, "b");
		while (size--)
		{
			int slot = f.read_int();
			Cgroup e;
			e.flags(f.read_int());
			e.name(f.read_str());
			e.owner(f.read_int());
			if (f.fail())
				return error(e_read_failed, fn, "c");
			if (slot)
				group(slot, e);
		}
	}
	{
		int size = f.read_int();
		if (f.fail())
			return error(e_read_failed, fn, "d");
		while (size--)
		{
			int slot = f.read_int();
			Cuser e;
			e.flags(f.read_int());
			e.name(f.read_str());
			e.mail(f.read_str());
			e.password_hash(f.read_int());
			if (e.flags() &  uf_uin)
				e.uin(f.read_int());
			if (e.flags() &  uf_link_title)
				e.link_title(f.read_str());
			if (e.flags() &  uf_link)
				e.link(f.read_str());
			if (~e.flags() & uf_active)
				e.activate_code(f.read_int());
			int gl_size = f.read_int();
			if (f.fail())
				return error(e_read_failed, fn, "e");
			while (gl_size--)
				e.add_group(f.read_int());
			if (f.fail())
				return error(e_read_failed, fn, "f");
			if (slot)
				user(slot, e);
		}
	}
	return error(e_none, fn, "");
}

int Cauthentication::write(Cfile31& f)
{
	const char* fn = "write";
	f.seek(0);
	f.write_int(0);
	{
		const t_gl& gl = m_gl;
		f.write_int(gl.size());
		for (t_gl::const_iterator i = gl.begin(); i != gl.end(); i++)
		{
			const Cgroup& e = i->second;
			f.write_int(i->first);
			f.write_int(e.flags());
			f.write_str(e.name());
			f.write_int(e.owner());
		}
	}
	{
		const t_ul& ul = m_ul;
		f.write_int(ul.size());
		for (t_ul::const_iterator i = ul.begin(); i != ul.end(); i++)
		{
			const Cuser& e = i->second;
			f.write_int(i->first);
			f.write_int(e.flags());
			f.write_str(e.name());
			f.write_str(e.mail());
			f.write_int(e.password_hash());
			if (e.flags() & uf_uin)
				f.write_int(e.uin());
			if (e.flags() & uf_link_title)
				f.write_str(e.link_title());
			if (e.flags() & uf_link)
				f.write_str(e.link());
			if (~e.flags() & uf_active)
				f.write_int(e.activate_code());
			const Cuser::t_gl& gl = e.gl();
			f.write_int(gl.size());
			for (Cuser::t_gl::const_iterator i = gl.begin(); i != gl.end(); i++)
				f.write_int(*i);
		}
	}
	if (f.fail())
		return 1;
	return error(e_none, fn, "");
}
