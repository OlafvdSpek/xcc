#pragma warning(disable: 4786)
#pragma warning(disable: 4800)

#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <minmax.h>
#include <set>
#include <time.h>
#ifndef _MSC_VER
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#endif
#include "cgi.h"
#include "crc.h"
#include "cookie.h"
#include "html.h"
#include "multi_line.h"
#include "string_conversion.h"
#include "strings.h"
#include "user_preferences.h"
#include "web_tools.h"

string config_file = "forum.ini";
string topics_file = "topics.dat";
Cstrings topic_names;
Cstrings topic_subjects;

enum t_action
{
	a_none, a_admin_login, a_admin_logout, a_ban_ip, a_disable_html_msg, a_edit_msg, a_enable_html_msg, a_import_into_cookie, a_post_msg,
	a_post_msg_submit, a_preferences_submit, a_set_msg_score, a_set_user_score, a_show_banned_msgs, a_show_index,
	a_show_ip, a_show_ladder, a_show_msg, a_show_newest_msgs, a_show_news, a_show_preferences, a_show_removed_msgs, 
	a_show_user, a_unban_ip, a_lock_msg, a_unlock_msg
};

enum t_config_text
{
	ci_use_signature,
	ci_use_uin,
	ci_use_link_once,
	ci_use_link,
	ci_use_icq_notification,
	ci_use_mail_notification,
	ci_use_ladder,
	ci_use_smilies,
	ci_flood_limit,
	ci_unknown,
	ct_base_url = ci_unknown,
	ct_css_url,
	ct_forum_mail,
	ct_forum_title,
	ct_home_dir,
	ct_private_dir,
	ct_public_dir,
	ct_public_url,
	ct_send_mail_cmd, 
	ht_index,
	ht_ladder,
	ht_message,
	ht_post_a_message,
	ht_preferences,
	ht_message_posted,
	ht_date,
	ht_uin,
	ht_link,
	ht_name,
	ht_c_posts,
	ht_subject,
	ht_admin_login,
	ht_admin,
	ht_ip,
	ht_score,
	ht_bottom,
	ht_field_error,
	ht_new_msg,
	ht_important_msg,
	ht_newest_msgs,
	ht_unknown
};

struct t_config_entry
{
	const char* ce_code;
	t_config_text ce_id;
	const char* ce_default_value;
};

t_config_entry config[] =
{	
	// {"", ct_, ""},
	{"use_signature", ci_use_signature, "1"},
	{"use_uin", ci_use_uin, "1"},
	{"use_link_once", ci_use_link_once, "1"},
	{"use_link", ci_use_link, "1"},
	{"use_icq_notification", ci_use_icq_notification, "1"},
	{"use_mail_notification", ci_use_mail_notification, "1"},
	{"use_ladder", ci_use_ladder, "1"},
	{"use_smilies", ci_use_smilies, "1"},
	{"flood_limit", ci_flood_limit, "15"},
	{"base_url", ct_base_url, "http://xcc.tiberian.com/"},
	{"css_url", ct_css_url, "/forum.css"},
	{"forum_mail", ct_forum_mail, "Forum"},
	{"forum_title", ct_forum_title, "Forum"},
	{"home_dir", ct_home_dir, "~/"},
	{"private_dir", ct_private_dir, "data/forum/"},
	{"public_dir", ct_public_dir, "htdocs/forum/"},
	{"public_url", ct_public_url, "/forum/"},
	{"send_mail_cmd", ct_send_mail_cmd, "/usr/sbin/sendmail -oi -t"},
	{"ht_index", ht_index, "Forum"},
	{"ht_ladder", ht_ladder, "Ladder"},
	{"ht_message", ht_message, "Message"},
	{"ht_post_a_message", ht_post_a_message, "Post a message"},
	{"ht_preferences", ht_preferences, "Preferences"},
	{"ht_message_posted", ht_message_posted, "Thanks"},
	{"ht_date", ht_date, "<th align=left>Date</th>"},
	{"ht_uin", ht_uin, "<th align=left>ICQ</th>"},
	{"ht_link", ht_link, "<th align=left>Link</th>"},
	{"ht_name", ht_name, "<th align=left>Name</th>"},
	{"ht_c_posts", ht_c_posts, "<th align=right>Posts</th>"},
	{"ht_subject", ht_subject, "<th align=left>Subject</th>"},
	{"ht_admin_login", ht_admin_login, "Admin login"},
	{"ht_admin", ht_admin, "Admin"},
	{"ht_ip", ht_ip, "<th align=left>IP</th>"},
	{"ht_score", ht_score, "<th align=left>Score</th>"},
	{"ht_bottom", ht_bottom, ""},
	{"ht_field_error", ht_field_error, "<img src=/forum/error.gif>"},
	{"ht_new_msg", ht_new_msg, "<font color=yellow>(new)<font>"},
	{"ht_important_msg", ht_important_msg, "<font color=yellow>(important)<font>"},
	{"ht_newest_msgs", ht_newest_msgs, "Newest messages"},
};

int config_int[ci_unknown];
string config_string[ht_unknown];

struct t_msg
{
	string name;
	string mail;
	string subject;
	string body;
	string signature;
	int uin;
	string link_once;
	string link_title;
	string link;
	int remote_addr;
	int flags;
	int parent;
};

struct t_ladder_entry
{
	int count;
	int last_post;
	string name;
};

int reverse32(int v)
{
	return v >> 24 & 0xff | v >> 8 & 0xff00 | v << 8 & 0xff0000 | v << 24 & 0xff000000;
}

string get_host_name(int ip)
{
#ifdef _MSC_VER
	return "";
#else
	int reverse_ip = reverse32(ip);
	hostent* he = gethostbyaddr(reinterpret_cast<const char*>(&reverse_ip), 4, AF_INET);
	return he ? he->h_name : "";
#endif
}

time_t get_time()
{
	time_t r;
	time(&r);
	return r;
}

struct t_topic
{
	t_topic()
	{
	}

	t_topic(const t_msg& msg):
		m_name(topic_names.add_string(msg.name)), m_subject(topic_subjects.add_string(msg.subject)), parent(msg.parent)
	{
		date = get_time();
		remote_addr = msg.remote_addr;
		score = 0;
	}

	const char* name() const
	{
		return topic_names.get_string(m_name);
	}

	const char* subject() const
	{
		return topic_subjects.get_string(m_subject);
	}

	void name(string v)
	{
		m_name = topic_names.add_string(v);
	}

	void subject(string v)
	{
		m_subject = topic_subjects.add_string(v);
	}

	bool hidden() const
	{
		return score < 0;
	}

	bool important() const
	{
		return score == 1;
	}

	bool news() const
	{
		return score == 2;
	}

	int m_name;
	int m_subject;
	int date;
	int parent;
	int remote_addr;
	int score;
};

typedef set<int> t_admin_hash;
typedef map<int, t_topic, greater<int> > t_topics;
typedef set<int> t_reverse_topic_entry;
typedef map<int, t_reverse_topic_entry> t_reverse_topics;
typedef map<string, string> t_smily_map;

bool admin = false;
t_admin_hash admin_hash;
Ccgi_input cgi;
Ccookie cookie = static_cast<Cmulti_line>(cgi.get_cookie());
string location;
t_topics topics;
bool topics_dirty = false;
t_reverse_topics reverse_topics;
t_smily_map smily_map;
fstream topic_f;
Cuser_preferences user_preferences;
int cb_names = 0;

int read_int(fstream& f)
{
	int r;
	f.read(reinterpret_cast<char*>(&r), sizeof(int));
	return r;
}

void write_int(fstream& f, int v)
{
	f.write(reinterpret_cast<char*>(&v), sizeof(int));
};

string read_str(fstream& f)
{
	int size = read_int(f);
	char* data = new char[size + 1];
	f.read(data, size);
	data[size] = 0;
	string r = data;
	delete[] data;
	return r;
}

void write_str(fstream& f, const string& v)
{
	int size = v.length();
	write_int(f, size);
	f.write(v.c_str(), size);
}

enum t_msg_flags
{
	mf_none,
	mf_mail = 1,
	mf_link_once = 2,
	mf_link_title = 4,
	mf_link = 8,
	mf_remote_addr = 0x10,
	mf_notify_mail = 0x20,
	mf_allow_html = 0x40,
	mf_uin = 0x80,
	mf_notify_icq = 0x100,
	mf_signature = 0x200,
	mf_enable_smilies = 0x400,
	mf_parent = 0x800,
	mf_locked = 0x1000,
	mf_old = mf_mail | mf_link_once | mf_link_title | mf_link | mf_remote_addr | mf_notify_mail
};

int read_msg(int slot, t_msg& msg)
{
	fstream f((config_string[ct_private_dir] + n(slot) + ".dat").c_str(), ios::binary | ios::in);
	if (!f.is_open())
		return 1;
	int old_pos = f.tellg();
	msg.flags = read_int(f);
	if (msg.flags)
	{
		f.seekg(old_pos);
		msg.flags = mf_old;
	}
	else
		msg.flags = read_int(f);
	msg.name = read_str(f);
	if (msg.flags & mf_mail)
		msg.mail = read_str(f);
	msg.subject = read_str(f);
	msg.body = read_str(f);
	if (msg.flags & mf_uin)
		msg.uin = read_int(f);
	else
		msg.uin = 0;
	if (msg.flags & mf_link_once)
		msg.link_once = read_str(f);
	if (msg.flags & mf_link_title)
		msg.link_title = read_str(f);
	if (msg.flags & mf_link)
		msg.link = read_str(f);
	if (msg.flags & mf_remote_addr)
		msg.remote_addr = a2ip(read_str(f));
	if (msg.flags & mf_signature)
		msg.signature = read_str(f);
	if (msg.flags & mf_parent)
		msg.parent = read_int(f);
	return f.fail();
}

int write_msg(int slot, const t_msg& msg)
{
	fstream f((config_string[ct_private_dir] + n(slot) + ".dat").c_str(), ios::binary | ios::out);
	if (f.fail())
		return 1;
	write_int(f, 0);
	write_int(f, msg.flags);
	write_str(f, msg.name);
	if (msg.flags & mf_mail)
		write_str(f, msg.mail);
	write_str(f, msg.subject);
	write_str(f, msg.body);
	if (msg.flags & mf_uin)
		write_int(f, msg.uin);
	if (msg.flags & mf_link_once)
		write_str(f, msg.link_once);
	if (msg.flags & mf_link_title)
		write_str(f, msg.link_title);
	if (msg.flags & mf_link)
		write_str(f, msg.link);
	if (msg.flags & mf_remote_addr)
		write_str(f, ip2a(msg.remote_addr));
	if (msg.flags & mf_signature)
		write_str(f, msg.signature);
	write_int(f, msg.parent);
	return f.fail();
}

#if 0
void send_icq_msg(const string& from, int to, const string& subject, const string& body)
{
#ifndef _MSC_VER
	FILE* icq = popen(send_icq_msg_cmd.c_str(), "w");
	if (icq)
	{
		/*
		char buffer[4096];
		sprintf(buffer, "to=%i&from=%s&fromemail=%s&subject=%s&body=%s&Send=SUBMIT", to, from.c_str(), from.c_str(), subject.c_str(), body.c_str());
		cout << "Content-type: text/html" << endl
			<< endl
			<< buffer << endl;
		// fprintf(icq, "to=%i&from=%s&fromemail=%s&subject=%s&body=%s&Send=SUBMIT", to, from.c_str(), from.c_str(), subject.c_str(), body.c_str());
		*/
		fprintf(icq, "to=43235472&from=Forum@XCC.Tiberian.Com&fromemail=Forum@XCC.Tiberian.Com&subject=Forum+reply+notification&body=Somebody+replied+to+your+message&Send=SUBMIT");
		pclose(icq);
	}
#endif
}
#endif

void send_mail(const string& from, const string& to, const string& subject, const string& body)
{
#ifndef _MSC_VER
	FILE* mail = popen(config_string[ct_send_mail_cmd].c_str(), "w");
	if (mail)
	{
		fprintf(mail, "To: %s\n", to.c_str());
		fprintf(mail, "From: %s\n", from.c_str());
		// if (!subject.empty())
		fprintf(mail, "Subject: %s\n", subject.c_str());
		fputs(body.c_str(), mail);
		pclose(mail);
	}
#endif
}

string report_error(const string& error_msg)
{
	location.erase();
	return error_msg;
}

void open_topic_f(bool write)
{
	topic_f.open((config_string[ct_private_dir] + topics_file).c_str(), ios::binary | ios::in | (write ? ios::out : 0));
}

int create_files()
{
	topic_f.open((config_string[ct_private_dir] + topics_file).c_str(), ios::binary | ios::out);
	write_int(topic_f, 0);
	write_int(topic_f, 0);
	write_int(topic_f, 0);
	topic_names.write(topic_f);
	topic_subjects.write(topic_f);
	topic_f.close();
	return topic_f.fail();
}

enum t_topic_flags
{
	tf_none,
	tf_score = 1,
	tf_remote_addr = 2,
	tf_new_format = 4
};

struct t_topic_header
{
	int name;
	int subject;
	int date;
	int parent;
	int remote_addr;
	int score;
	int slot;
};

int read_topics()
{
	int flags = tf_none;
	int size = read_int(topic_f);
	if (!size)
	{
		flags = read_int(topic_f);
		size = read_int(topic_f);
	}
	if (topic_f.fail())
		return 1;
	if (flags & tf_new_format)
	{
		if (topic_names.read(topic_f))
			return 1;
		if (topic_subjects.read(topic_f))
			return 1;
	}
	int slot;
	t_topic_header h;
	t_topic topic;
	while (size--)
	{
		if (flags & tf_new_format)
		{
			topic_f.read(reinterpret_cast<char*>(&h), sizeof(t_topic_header));
			if (topic_f.fail())
				return 1;
			topic.m_name = h.name;
			topic.m_subject = h.subject;
			topic.date = h.date;
			topic.parent = h.parent;
			topic.remote_addr = h.remote_addr;
			topic.score = h.score;
			slot = h.slot;
		}
		else
		{
			topic.name(read_str(topic_f));
			topic.subject(read_str(topic_f));
			topic.date = read_int(topic_f);
			topic.parent = read_int(topic_f);
			topic.remote_addr = flags & tf_remote_addr ? read_int(topic_f) : 0;
			topic.score = flags & tf_score ? read_int(topic_f) : 0;
			slot = read_int(topic_f);
			if (topic_f.fail())
				return 1;
		}
		if (topic.score < -9 || topic.score > 9 || topic.m_name < 0 || topic.m_name > 1 << 20)
			continue;
		topics[slot] = topic;
		reverse_topics[topic.parent].insert(slot);
	}
	return 0;
}

int write_topics()
{
	topic_f.seekp(0);
	write_int(topic_f, 0);
	write_int(topic_f, tf_remote_addr | tf_score | tf_new_format);
	write_int(topic_f, topics.size());
	topic_names.write(topic_f);
	topic_subjects.write(topic_f);
	if (topic_f.fail())
		return 1;
	t_topic_header h;
	for (t_topics::const_iterator i = topics.begin(); i != topics.end(); i++)
	{
		const t_topic& topic = i->second;
		h.name = topic.m_name;
		h.subject = topic.m_subject;
		h.date = topic.date;
		h.parent = topic.parent;
		h.remote_addr = topic.remote_addr;
		h.score = topic.score;
		h.slot = i->first;
		topic_f.write(reinterpret_cast<char*>(&h), sizeof(h));
		if (topic_f.fail())
			return 1;
	}
	return 0;
}

bool bad_upper(const string& v, int limit)
{
	if (v.length() < limit)
		return false;
	int c = 0;
	for (int i = 0; i < v.length(); i++)
	{
		if (v[i] != tolower(v[i]))
			c++;
	}
	return c << 1 > v.length();
}

/*
string remove_cr(string v)
{
	int i;
	while (i = v.find('\r'), i != string::npos)
	{
		v.erase(i);
	}
	return v;
}
*/

int get_c_lines(const string& v, bool ignore_quotes = false)
{
	int r = 0;
	int l = 0;
	while (l < v.length())
	{
		int p = v.find('\n', l);
		string line;
		if (p == string::npos)
		{
			line = v.substr(l);
			p = v.length();
		}
		else
			line = v.substr(l, p - l);
		if (ignore_quotes)
		{
			// line = remove_cr(line);
			trim(line);
			if (!line.empty() && line.find(">") != 0)
				r++;
		}
		else
			r++;
		l = p + 1;
	}
	return r;
}

bool get_admin()
{
	const char* id = "password";
	if (cgi.has_name(id))
	{
		if (!cgi.has_value(id))
			cookie.set_session_value(id, "");
		else
		{
			string password = cgi.get_value(id);
			if (admin_hash.find(get_hash(password)) != admin_hash.end())
			{
				cookie.set_session_value(id, password);
				return true;
			}
		}
	}
	else if (cookie.has_value(id))
	{
		if (admin_hash.find(get_hash(cookie.get_value(id))) != admin_hash.end())
			return true;
	}
	return false;
}

bool is_complete()
{
	return cgi.has_value("name") && cgi.has_value("subject") && cgi.has_value("body") 
		&& cgi.get_value("name").length() < 32 && cgi.get_value("subject").length() < 72 && get_c_lines(cgi.get_value("body"), true)
		&& (get_admin() || (!bad_upper(cgi.get_value("name"), 8) && !bad_upper(cgi.get_value("subject"), 16)));
}

Chtml check_required(const string& name)
{
	return !cgi.has_name(name) || cgi.has_value(name) ? "" : config_string[ht_field_error];
}

int get_field_length()
{
	const char* id = "field_length";
	int r;
	if (cgi.has_value(id))
	{
		r = cgi.get_value_int(id);
		cookie.set_value(id, n(r));
	}
	else if (cookie.has_value(id))
		r = cookie.get_value_int(id);
	else
		r = 60;
	return r;
}

int get_time_offset()
{
	const char* id = "time_offset";
	int r;
	if (cgi.has_value(id))
	{
		r = cgi.get_value_int(id);
		cookie.set_value(id, n(r));
	}
	else if (cookie.has_value(id))
		r = cookie.get_value_int(id);
	else
		r = 0;
	return r;
}

string cnv_date(time_t time, bool use_day_name = false)
{
	time += 3600 * get_time_offset();
	const tm* date = localtime(&time);
	string r = nwzl(2, date->tm_hour) + ':' + nwzl(2, date->tm_min);
	if (use_day_name)
	{
		const char* day_name[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
		r += ' ';
		r += day_name[date->tm_wday];
	}
	return r + ' ' + nwzl(2, date->tm_mday) + '-' + nwzl(2, date->tm_mon + 1) + '-' + n(date->tm_year + 1900);
};

Chtml get_spaces(int count)
{
	Chtml r;
	while (count--)
		r += "&nbsp;";
	return r;
}

int get_days()
{
	const char* id = "days";
	int r;
	if (cgi.has_value(id))
	{
		r = cgi.get_value_int(id);
		cookie.set_value(id, n(r));
	}
	else if (cookie.has_value(id))
		r = cookie.get_value_int(id);
	else
		r = 7;
	return r;
}

int get_last_date()
{
	return get_time() - 24 * 3600 * get_days();
}

int get_mts()
{
	const char* id = "mts";
	int r;
	if (cgi.has_value(id))
	{
		r = cgi.get_value_int(id);
		cookie.set_value(id, n(r));
	}
	else if (cookie.has_value(id))
		r = cookie.get_value_int(id);
	else
		r = 8;
	return r;
}

int get_last_shown_msg()
{
	const char* id = "last_shown_msg_session";
	if (cookie.has_value(id))
		return cookie.get_value_int(id);
	int r = cookie.get_value_int("last_shown_msg");
	cookie.set_session_value(id, r);
	return r;
}

int get_thread_newest_msg(int slot)
{
	int r = slot;
	const t_reverse_topics::const_iterator rte = reverse_topics.find(slot);
	if (rte != reverse_topics.end())
	{
		for (t_reverse_topic_entry::const_iterator j = rte->second.begin(); j != rte->second.end(); j++)
		{
			t_topics::const_iterator i = topics.find(*j);
			if (i->second.hidden())
				continue;
			r = max(r, get_thread_newest_msg(i->first));
		}
	}
	return r;
}

int get_thread_date(int slot)
{
	slot = get_thread_newest_msg(slot);
	return slot ? topics.find(slot)->second.date : 0;
}

int get_thread_size(int slot)
{
	int r = 1;
	const t_reverse_topics::const_iterator rte = reverse_topics.find(slot);
	if (rte != reverse_topics.end())
	{
		for (t_reverse_topic_entry::const_iterator i = rte->second.begin(); i != rte->second.end(); i++)
		{
			if (topics.find(*i)->second.hidden())
				continue;
			r += get_thread_size(*i);
		}
	}
	return r;
}

Chtml head_forum(bool use_base = false)
{
	Chtml h;
	if (use_base)
		h += "<base href=" + config_string[ct_base_url] + ">\n";
	return head(h
		+ "<link rel=stylesheet href=" + config_string[ct_css_url] + ">\n"
		+ title(config_string[ct_forum_title]));
}

t_msg get_msg_input()
{
	t_msg r;
	r.name = cgi.get_value("name");
	r.mail = cgi.get_value("mail");
	r.subject = cgi.get_value("subject");
	r.body = cgi.get_value("body");
	r.signature = cgi.get_value("signature");
	r.uin = config_int[ci_use_uin] ? atoi(cgi.get_value("uin").c_str()) : 0;
	r.link_once = cgi.get_value("link_once");
	r.link_title = cgi.get_value("link_title");
	r.link = cgi.get_value("link");
	r.remote_addr = a2ip(get_env("REMOTE_ADDR"));
	r.flags = mf_parent;
	r.parent = atoi(cgi.get_value("parent").c_str());
	trim(r.name);
	trim(r.mail);
	trim(r.subject);
	if (!r.mail.empty())
		r.flags |= mf_mail;
	if (!r.signature.empty())
		r.flags |= mf_signature;
	if (r.uin)
		r.flags |= mf_uin;
	if (config_int[ci_use_link_once] && !r.link_once.empty())
		r.flags |= mf_link_once;
	if (config_int[ci_use_link] && !r.link_title.empty())
		r.flags |= mf_link_title;
	if (config_int[ci_use_link] && !r.link.empty())
		r.flags |= mf_link;
	if (cgi.has_value("notify_icq"))
		r.flags |= mf_notify_icq;
	if (cgi.has_value("notify_mail"))
		r.flags |= mf_notify_mail;
	if (cgi.has_value("enable_smilies"))
		r.flags |= mf_enable_smilies;
	if (r.remote_addr)
		r.flags |= mf_remote_addr;
	return r;
}

bool is_empty(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] > 0x20)
			return false;
	}
	return true;
}

Chtml web_magic_quotes(const string& v)
{
	string r;
	int l = 0;
	while (l < v.length())
	{
		int p = v.find('\n', l);
		string line;
		if (p == string::npos)
		{
			line = v.substr(l);
			p = v.length();
		}
		else
			line = v.substr(l, p - l);
		if (line.find("&gt;") == 0)
			r += html_span(line, "class=quote");
		else
			r += line;
		r += '\n';
		l = p + 1;
	}
	return r;
}

Chtml web_magic_smilies(const string& v, const string& id, const string& fname)
{
	string r;
	int l = 0;
	while (l < v.length())
	{
		int p = v.find(id, l);
		if (p == string::npos)
		{
			r += v.substr(l);
			break;
		}
		r += v.substr(l, p - l)
			+ "<img src=" + fname + ">";
		l = p + id.length();
	}
	return r;
}

Chtml web_magic_smilies(string r)
{
	for (t_smily_map::const_iterator i = smily_map.begin(); i != smily_map.end(); i++)
		r = web_magic_smilies(r, i->first, config_string[ct_public_url] + i->second);
	return r;
}

string checked_text(bool v)
{
	return v ? " checked" : "";
}

string enabled_text(bool v)
{
	return v ? "enabled" : "disabled";
}

bool is_new_msg(int slot, int last_shown_msg, bool collapsed)
{
	if (slot > last_shown_msg && topics.find(slot)->second.name() != cookie.get_value("name"))
		return true;
	if (collapsed)
	{
		const t_reverse_topics::const_iterator rte = reverse_topics.find(slot);
		if (rte != reverse_topics.end())
		{
			for (t_reverse_topic_entry::const_iterator i = rte->second.begin(); i != rte->second.end(); i++)
			{
				if (is_new_msg(*i, last_shown_msg, collapsed))
					return true;
			}
		}
	}
	return false;
}

string new_text(int slot, bool collapsed)
{
	return is_new_msg(slot, get_last_shown_msg(), collapsed) ? " " + config_string[ht_new_msg] : "";
}

string important_text(int slot)
{
	return topics.find(slot)->second.important() ? " " + config_string[ht_important_msg] : "";
}

string get_backward_location()
{
	string r = cgi.get_value("location");
	if (r.empty())
		r = get_env("HTTP_REFERER");
	return r;
}

Chtml msg_form(t_msg msg, int slot = 0, const string& location = "")
{
	if (msg.name.empty() && msg.mail.empty() && msg.link_title.empty() && msg.link.empty())
	{
		msg.name = cookie.get_value("name");
		msg.mail = cookie.get_value("mail");
		msg.signature = cookie.get_value("signature");
		msg.uin = cookie.get_value_int("uin");
		msg.link_title = cookie.get_value("link_title");
		msg.link = cookie.get_value("link");
		if (cookie.get_value_int("notify_icq"))
			msg.flags |= mf_notify_icq;
		if (cookie.get_value_int("notify_mail"))
			msg.flags |= mf_notify_mail;
		if (cookie.get_value_int("enable_smilies"))
			msg.flags |= mf_enable_smilies;
	}
	Chtml d;
	if (config_int[ci_use_smilies] && user_preferences.show_smilies)
	{
		for (t_smily_map::const_iterator i = smily_map.begin(); i != smily_map.end(); i++)
			d += p(i->first + ' ' + web_magic_smilies(i->first, i->first, config_string[ct_public_url] + i->second));
	}
	Chtml t = tr(td("Name:", "align=right") + td("<input type=text name=name size=" + n(get_field_length()) + " maxlength=31 value=\"" + web_encode(msg.name) +"\"" + static_cast<string>(slot ? " readonly" : "") + ">") + td(check_required("name") + td(d, "align=right rowspan=999 valign=top")))
			+ tr(td("Email:", "align=right") + td("<input type=text name=mail size=" + n(get_field_length()) + " value=\"" + web_encode(msg.mail) +"\">"))
			+ tr(td("Subject:", "align=right") + td("<input type=text name=subject size=" + n(get_field_length()) + " maxlength=63 value=\"" + web_encode(msg.subject) +"\"" + static_cast<string>(slot ? " readonly" : "") + ">") + td(check_required("subject")))
			+ tr(td("Message:<p>HTML " + enabled_text(false) + "<br>Smilies " + enabled_text(config_int[ci_use_smilies]) + "<br>UBB " + enabled_text(false), "align=right") + td(textarea(web_encode(msg.body, false), "cols=" + n(get_field_length()) + " rows=15 name=body wrap=physical")) + td(check_required("body")));
	if (config_int[ci_use_signature] && user_preferences.show_signatures)
		t += tr(td("Signature:", "align=right") + td(textarea(web_encode(msg.signature, false), "cols=" + n(get_field_length()) + " rows=4 name=signature wrap=physical")));
	if (config_int[ci_use_uin])
		t += tr(td("ICQ number (optional):", "align=right") + td("<input type=text name=uin size=" + n(get_field_length()) + " value=" + static_cast<string>(msg.uin ? n(msg.uin) : "") +">"));
	if (config_int[ci_use_link_once])
		t += tr(td("Link once (optional):", "align=right") + td("<input type=text name=link_once size=" + n(get_field_length()) + " value=\"" + web_encode(msg.link_once) +"\">"));
	if (config_int[ci_use_link])
		t += tr(td("Link title (optional):", "align=right") + td("<input type=text name=link_title size=" + n(get_field_length()) + " value=\"" + web_encode(msg.link_title) +"\">"))
			+ tr(td("Link (optional):", "align=right") + td("<input type=text name=link size=" + n(get_field_length()) + " value=\"" + web_encode(msg.link) +"\">"));
	if (config_int[ci_use_icq_notification])
		t += tr(td("") + td("<input type=checkbox name=notify_icq" + checked_text(msg.flags & mf_notify_icq) + "> Notify me by ICQ when somebody replies to this message"));
	if (config_int[ci_use_mail_notification])
		t += tr(td("") + td("<input type=checkbox name=notify_mail" + checked_text(msg.flags & mf_notify_mail) + "> Notify me by email when somebody replies to this message"));
	if (config_int[ci_use_smilies])
		t += tr(td("") + td("<input type=checkbox name=enable_smilies" + checked_text(msg.flags & mf_enable_smilies) + "> Enable smilies"));
	t += tr(td("") + td("<input type=submit value=Submit>"));
	return
		form(
			"<input type=hidden name=action value=" + n(a_post_msg_submit) + ">\n"
			"<input type=hidden name=parent value=" + n(msg.parent) + ">\n" +
			"<input type=hidden name=slot value=" + n(slot) + ">\n" +
			"<input type=hidden name=location value=" + (location.empty() ? cgi.get_value("location") : location) + ">\n" +
			table(t),
			"action=" + cgi.get_url() + " method=post");
}

int get_next_slot()
{
	return topics.empty() ? 1 : topics.begin()->first + 1;
};

void add_smily(string id, string fname)
{
	smily_map[id] = fname;
}

int read_config()
{
	int i;
	for (i = 0; i < ht_unknown; i++)
		config_string[i] = config[i].ce_default_value;
	fstream f(config_file.c_str(), ios::in);
	string s;
	while (getline(f, s))
	{
		if (s.empty() || s[0] == ';')
			continue;
		string name, value;
		split_key(s, name, value);
		name = to_lower(name);
		if (name == "add_smily")
		{
			Cmulti_line l = value;
			string id = l.get_next_line();
			add_smily(id, l.get_next_line());
		}
		else if (name == "admin_password")
			admin_hash.insert(atoi(value.c_str()));
		else
		{
			for (int i = 0; i < ht_unknown; i++)
			{
				if (name == config[i].ce_code)
				{
					config_string[config[i].ce_id] = value;
					break;
				}
			}
		}
	}
	for (i = 0; i < ci_unknown; i++)
		config_int[i] = atoi(config_string[i].c_str());
	// config_string[ct_private_dir] = "data/nldark/forum/";
	config_string[ct_private_dir] = config_string[ct_home_dir] + config_string[ct_private_dir];
	config_string[ct_public_dir] = config_string[ct_home_dir] + config_string[ct_public_dir];
	// config_string[ht_bottom] += "<div align=right><a href=\"mailto:Webmaster <XCC@XCC.TMFWeb.NL>\">Olaf van der Spek</a>'s <a href=\"http://xcc.tiberian.com/show_frame.php?src=/downloads/\">Forum</a> v0.90</div>";
	return 0;
}

Chtml an_self(const string& title, t_action action, const string& elements = "")
{
	return a(title, "href=" + cgi.get_url() + "?action=" + n(action) + "&" + elements);
}

Chtml an_set_msg_score(const string& title, int slot, int score)
{
	return an_self(title, a_set_msg_score, "slot=" + n(slot) + "&score=" + n(score));
}

Chtml an_set_user_score(const string& title, const string& name, int score)
{
	return an_self(title, a_set_user_score, "score=" + n(score) + "&user=" + web_encode(name));
}

Chtml an_show_msg(const string& title, int slot)
{
	return an_self(title, a_show_msg, "slot=" + n(slot));
}

Chtml get_name(const string& name, const string& mail)
{
	return mail.empty() ? html_span(web_encode(name), "class=name") : a(web_encode(name), "href=\"mailto:" + web_encode(name) + " <" + web_encode(mail) + ">\"");
}

Chtml get_subject(const string& subject, int parent)
{
	return !parent ? html_span(web_encode(subject), "class=subject") : an_show_msg(web_encode(subject), parent);
}

Chtml get_icq_link(int uin, int indicator_type)
{
	return uin ? a("<img border=0 src=http://wwp.icq.com/scripts/online.dll?icq=" + n(uin) + "&img=" + n(indicator_type) + ">", "target=_top href=http://wwp.icq.com/" + n(uin)) : "";
}

Chtml get_link(const string& link_title, const string& link)
{
	return link.empty() ? "" : a(web_encode(link_title.empty() ? link : link_title), "target=_top href=\"" + web_encode(link) + "\"");
}

t_msg create_reply(int slot, const t_msg& msg)
{
	t_msg r;
	r.subject = (msg.subject.find("Re: ") == string::npos ? "Re: " : "") + msg.subject;
	int i = 0;
	while (i < msg.body.length())
	{
		int p = msg.body.find('\n', i);
		string line;
		if (p == string::npos)
		{
			line = msg.body.substr(i) + '\n';
			p = msg.body.length();
		}
		else
			line = msg.body.substr(i, p - i + 1);
		if (!is_empty(line))
			r.body += "> ";
		r.body += line;
		i = p + 1;
	}
	r.flags = mf_none;
	r.parent = slot;
	return r;
};

Chtml get_admin_links()
{
	return an_self("Banned messages", a_show_banned_msgs)
		+ " | " + an_self("Logout", a_admin_logout)
		+ " | " + an_self("News", a_show_news)
		+ " | " + an_self("Removed messages", a_show_removed_msgs);
}

Chtml get_links()
{
	Chtml r;
	if (!admin)
		r += an_self("Admin", a_admin_login) + " | ";
	r += an_self("Index", a_show_index);
	if (config_int[ci_use_ladder])
		r += " | " + an_self("Ladder", a_show_ladder);
	return r
		+ " | " + an_self("Post a message", a_post_msg)
		+ " | " + an_self("Preferences", a_show_preferences);
}

Chtml get_links2()
{
	return
		an_self("Newest messages", a_show_newest_msgs);
}

Chtml get_top(t_config_text title)
{
	Chtml r;
	if (user_preferences.show_top_links)
	{
		if (admin)
			r += br(get_admin_links ());
		r += br(get_links2()) + br(get_links());
	}
	return table(tr(td(html_span(config_string[title], "class=page_title"), "valign=bottom") + td(br(config_string[ct_forum_title]) + r, "align=right valign=bottom")), "width=100%") + hr();
}

Chtml get_bottom(Chtml text)
{
	Chtml r;
	if (user_preferences.show_bottom_links)
	{
		r += br(get_links()) + br(get_links2());
		if (admin)
			r += br(get_admin_links ());
	}
	
	return hr() + table(tr(td(text, "valign=top") + td(r + br(config_string[ct_forum_title]) + "<a href=\"mailto:Webmaster <XCC@XCC.TMFWeb.NL>\">Olaf van der Spek</a>'s <a href=\"http://xcc.tiberian.com/show_frame.php?src=/downloads/\">Forum</a> v0.90", "align=right valign=top")), "width=100%") + config_string[ht_bottom];
	return hr() + table(tr(td(text, "valign=top") + td(r + br(config_string[ct_forum_title]), "align=right valign=top")), "width=100%") + config_string[ht_bottom];
}

Chtml thread_header(bool no_parent)
{
	Chtml r;
	if (user_preferences.show_date)
		r += config_string[ht_date];
	if (no_parent)
	{
		if (user_preferences.show_c_posts)
			r += config_string[ht_c_posts];
		if (user_preferences.show_updated_by)
			r += config_string[ht_name];
		if (user_preferences.show_updated_on)
			r += config_string[ht_date];
	}
	return config_string[ht_subject] + config_string[ht_name] + r;
}

Chtml show_thread(int slot, int level, int last_date)
{
	Chtml r;
	int current_date = get_time();
	typedef multimap<int, int> t_msg_list;
	t_msg_list msg_list;
	const t_reverse_topics::const_iterator rte = reverse_topics.find(slot);
	if (rte != reverse_topics.end())
	{
		for (t_reverse_topic_entry::const_iterator i = rte->second.begin(); i != rte->second.end(); i++)
		{
			if (topics.find(*i)->second.hidden())
				continue;
			int date = get_thread_date(*i);
			if (date > last_date || topics.find(*i)->second.important())
				msg_list.insert(t_msg_list::value_type(~date, *i));
		}
	}
	int mts = slot ? INT_MAX : get_mts();
	Chtml r_normal;
	for (t_msg_list::const_iterator j = msg_list.begin(); j != msg_list.end(); j++)
	{
		t_topics::const_iterator i = topics.find(j->second);
		const t_topic& topic = i->second;
		int c_posts = get_thread_size(i->first);
		bool collapsed = c_posts > mts;
		Chtml& r_target = i->second.important() ? r : r_normal;
		Chtml r;
		if (user_preferences.show_date)
			r += td(cnv_date(topic.date), "nowrap");
		if (!i->second.parent)
		{
			if (user_preferences.show_c_posts)
				r += td(n(c_posts), "align=right");
			if (user_preferences.show_updated_by)
				r += td(topics.find(get_thread_newest_msg(i->first))->second.name());
			if (user_preferences.show_updated_on)
				r += td(cnv_date(get_thread_date(i->first)));
		}
		r_target += tr(
			td(get_spaces(4 * level) + an_show_msg(web_encode(topic.subject()), i->first) + important_text(i->first) + new_text(i->first, collapsed)) +
			td(web_encode(topic.name())) +
			r);
		if (!collapsed)
			r_target += show_thread(i->first, level + 1, last_date);
	}
	r += r_normal;
	return r;
}

Chtml html_size_stats()
{
	int topic_size = sizeof(t_topic) * topics.size();
	return "Size: " +  n(topic_names.size() + topic_subjects.size() + topic_size) + " (" + n(topic_names.size()) + ", " + n(topic_subjects.size()) + ", " + n(topic_size) + ")";
}

Chtml forum()
{
	open_topic_f(false);
	if (read_topics())
		return "Error: unable to read topics\n";
	Chtml r =
		get_top(ht_index) +
		table(tr(thread_header(true)) + show_thread(0, 0, get_last_date())) +
		get_bottom(br("Count messages: " + n(static_cast<int>(topics.size()))) +
			br("Count threads: " + n(static_cast<int>(reverse_topics[0].size()))) +
			br("Current time: " + cnv_date(get_time())) +
			br("Last msg time: " + cnv_date(get_thread_date(0)))
			+ br(html_size_stats()));
	return r;
}

Chtml page_forward()
{
	return "";
		get_top(ht_admin)
		+ "Click " + a("here", "href=" + location) + " to continue."
		+ get_bottom("");
}

Chtml page_admin_login()
{
	if (!admin)
	{
		return
			get_top(ht_admin_login)
			+ form(
			"<input type=hidden name=action value=" + n(a_admin_login) + ">\n"
			+ "<input type=hidden name=location value=" + get_backward_location() + ">\n"
			+ table(
			tr(td("Password:", "align=right") + td("<input type=password name=password size=60 maxlength=31>") + td(check_required("password")))
			+ tr(td("") + td("<input type=submit value=Submit>"))),
			"action=" + cgi.get_url() + " method=post")
			+ get_bottom(n(get_hash(cgi.get_value("password"))));
	}
	location = get_backward_location();
	return page_forward();
}

Chtml page_admin_logout()
{
	cookie.set_session_value("password", "");
	location = get_env("HTTP_REFERER");
	return page_forward();
}

string trim_white(string r)
{
	trim(r);
	return r;
}

Chtml page_bad_upper(Cstrings& strings, int limit)
{
	Chtml page;
	int o = 0;
	while (o < strings.size())
	{
		string subject = strings.get_string(o);
		o += subject.length() + 1;
		page += tr(bad_upper(subject, limit) ? td("&nbsp;") + td(subject) : td(subject) + td("&nbsp;"));
	}
	return table(tr(th("Good") + th("Bad")) + page, "border=1 width=100%");
}

Chtml ladder()
{
	if (!config_int[ci_use_ladder])
		return forum();
	open_topic_f(false);
	if (read_topics())
		return "Error: unable to read topics\n";
	// return page_bad_upper(topic_names, 8) + hr() + page_bad_upper(topic_subjects, 16);
	typedef map<string, t_ladder_entry> t_poster_list;
	t_poster_list poster_list;
	for (t_topics::const_iterator i = topics.begin(); i != topics.end(); i++)
	{
		if (i->second.hidden())
			continue;
		string name = to_lower(trim_white(i->second.name()));
		t_ladder_entry& j = poster_list[name];
		if (j.name.empty())
		{
			j.count = 0;
			j.last_post = i->first;
		}
		j.count++;
		j.name = i->second.name();
	}
	typedef multimap<int, t_poster_list::const_iterator, greater<int> > t_ladder;
	t_ladder ladder;
	for (t_poster_list::const_iterator j = poster_list.begin(); j != poster_list.end(); j++)
		ladder.insert(t_ladder::value_type(j->second.count, j));
	typedef set<string> t_string_set;
	t_string_set ip_set;
	Chtml t;
	for (t_ladder::const_iterator k = ladder.begin(); k != ladder.end(); k++)
	{
		Chtml r;
		t_msg msg;
		if (!read_msg(k->second->second.last_post, msg))
		{
			r = td(get_name(k->second->second.name, msg.mail)) +
				td(n(k->first), "align=right") +
				td(get_icq_link(msg.uin, 5)) + td(get_link(msg.link_title, msg.link));
			if (admin)
				r += td(ip2a(msg.remote_addr)) + td(an_self("Index", a_show_user, "name=" + uri_encode(msg.name)));
		}
		else
			r = td(web_encode(k->second->second.name)) + td(n(k->first), "align=right");
		t += tr(r);
	}
	Chtml h;
	if (admin)
		h += config_string[ht_ip];
	return
		get_top(ht_ladder) +
		table(tr(config_string[ht_name] + config_string[ht_c_posts] + config_string[ht_uin] + config_string[ht_link] + h) + t) +
		get_bottom("Count users: " + n(static_cast<int>(ladder.size())));
}

Chtml page_update_topics()
{
	open_topic_f(true);
	if (read_topics())
		return "Error: unable to read topics\n";
	Chtml t;
	for (t_topics::iterator i = topics.begin(); i != topics.end(); i++)
	{
		if (i->second.remote_addr)
			continue;
		t_msg msg;
		if (!read_msg(i->first, msg) && msg.remote_addr)
		{
			i->second.remote_addr = msg.remote_addr;
			t += tr(td(ip2a(msg.remote_addr)));
		}
	}
	topics_dirty = true;
	return
		get_top(ht_admin)
		+ table(tr(config_string[ht_ip]) + t)
		+ get_bottom("");
}

Chtml page_show_ip(int ip)
{
	open_topic_f(false);
	if (read_topics())
		return "Error: unable to read topics\n";
	int c_posts = 0;
	Chtml t;
	for (t_topics::const_iterator i = topics.begin(); i != topics.end(); i++)
	{
		if (i->second.remote_addr == ip || get_net_part(i->second.remote_addr) == ip)
		{
			t_msg msg;
			if (!read_msg(i->first, msg))
			{
				c_posts++;
				t += tr(td(an_show_msg(web_encode(i->second.subject()), i->first))
					+ td(i->second.name())
					+ td(cnv_date(i->second.date))
					+ td(ip2a(msg.remote_addr))
					+ td(n(i->second.score) + " " + an_set_msg_score("+", i->first, i->second.score + 1) + " " + an_set_msg_score("-", i->first, i->second.score - 1)));
			}
		}
	}
	return
		get_top(ht_admin)
		+ table(tr(config_string[ht_subject] + config_string[ht_name] + config_string[ht_date] + config_string[ht_ip] + config_string[ht_score]) + t)
		+ get_bottom("Count messages: " + n(c_posts));
}

Chtml page_show_user(string name)
{
	open_topic_f(false);
	if (read_topics())
		return "Error: unable to read topics\n";
	int c_posts = 0;
	typedef set<unsigned int> t_ip_set;
	t_ip_set ip_set;
	t_ip_set net_mask_set;
	Chtml t;
	name = to_lower(trim_white(name));
	for (t_topics::const_iterator i = topics.begin(); i != topics.end(); i++)
	{
		if (to_lower(trim_white(i->second.name())) != name)
			continue;
		c_posts++;
		t += tr(td(an_show_msg(web_encode(i->second.subject()), i->first)) 
			+ td(i->second.name()) 
			+ td(cnv_date(i->second.date))
			+ td(ip2a(i->second.remote_addr))
			+ td(n(i->second.score) + " " + an_set_msg_score("+", i->first, i->second.score + 1) + " " + an_set_msg_score("-", i->first, i->second.score - 1)));
		ip_set.insert(i->second.remote_addr);
	}
	t += tr(td("*", "align=center") + td("*", "align=center") + td("*", "align=center") + td("*", "align=center") + td(an_set_user_score("R", name, -2) + " " + an_set_user_score("B", name, -1) + " " + an_set_user_score("N", name, 0)));
	Chtml t2;
	{
		for (t_ip_set::const_iterator i = ip_set.begin(); i != ip_set.end(); i++)
		{
			t2 += tr(td(an_self(ip2a(*i), a_show_ip, "ip=" + ip2a(*i))) + td(get_host_name(*i)) + td(an_self("Ban", a_ban_ip, "ip=" + ip2a(*i))));
			net_mask_set.insert(get_net_part(*i));
		}
	}
	Chtml t3;
	{
		for (t_ip_set::const_iterator i = net_mask_set.begin(); i != net_mask_set.end(); i++)
		{
			t3 += tr(td(an_self(ip2a(*i), a_show_ip, "ip=" + ip2a(*i))) + td(an_self("Ban", a_ban_ip, "ip=" + ip2a(*i))));
		}
	}
	return
		get_top(ht_admin)
		+ table(tr(config_string[ht_subject] + config_string[ht_name] + config_string[ht_date] + config_string[ht_ip] + config_string[ht_score]) + t)
		+ hr()
		+ table(tr(config_string[ht_ip] + config_string[ht_name]) + t2)
		+ hr()
		+ table(tr(config_string[ht_ip]) + t3)
		+ get_bottom("Count messages: " + n(c_posts));
}

Chtml page_show_msgs_with_score(int score)
{
	open_topic_f(false);
	if (read_topics())
		return "Error: unable to read topics\n";
	int c_posts = 0;
	Chtml t;
	for (t_topics::const_iterator i = topics.begin(); i != topics.end(); i++)
	{
		if (i->second.score != score)
			continue;
		c_posts++;
		t += tr(td(an_show_msg(web_encode(i->second.subject()), i->first)) 
			+ td(i->second.name()) 
			+ td(cnv_date(i->second.date))
			+ td(ip2a(i->second.remote_addr))
			+ td(n(i->second.score) + " " + an_set_msg_score("+", i->first, i->second.score + 1) + " " + an_set_msg_score("-", i->first, i->second.score - 1)));
	}
	return
		get_top(ht_admin)
		+ table(tr(config_string[ht_subject] + config_string[ht_name] + config_string[ht_date] + config_string[ht_ip] + config_string[ht_score]) + t)
		+ get_bottom("Count messages: " + n(c_posts));
}

Chtml post_msg()
{
	return
		get_top(ht_post_a_message) +
		msg_form(get_msg_input()) +
		get_bottom("");
};

Chtml preferences()
{
	return
		get_top(ht_preferences)
		+ form(
			"<input type=hidden name=action value=" + n(a_preferences_submit) + ">\n" +
			"<input type=hidden name=location value=" + get_env("HTTP_REFERER") + ">\n" +
			br("View messages of the last <input type=text name=days size=3 maxlength=3 value=" + n(get_days()) + "> days " +
				"with a maximum of <input type=text name=mts size=3 maxlength=3 value=" + n(get_mts()) + "> messages per thread.") +
			br("<input type=checkbox check name=top_links" + checked_text(user_preferences.show_top_links) + "> Enable top links") +
			br("<input type=checkbox name=bottom_links" + checked_text(user_preferences.show_bottom_links) + "> Enable bottom links") +
			br("<input type=checkbox name=show_signatures" + checked_text(user_preferences.show_signatures) + "> Enable signatures") +
			br("<input type=checkbox name=show_smilies" + checked_text(user_preferences.show_smilies) + "> Enable smilies") +
			br("<input type=checkbox name=show_c_posts" + checked_text(user_preferences.show_c_posts) + "> Show count posts") +
			br("<input type=checkbox name=show_date" + checked_text(user_preferences.show_date) + "> Show when a message is posted") +
			br("<input type=checkbox name=show_updated_by" + checked_text(user_preferences.show_updated_by) + "> Show by who a topic is updated") +
			br("<input type=checkbox name=show_updated_on" + checked_text(user_preferences.show_updated_on) + "> Show when a topic is updated") +
			br("Field length: <input type=text name=field_length size=3 maxlength=3 value=" + n(get_field_length()) + "> characters") +
			br("Newest limit: <input type=text name=newest_limit size=3 maxlength=3 value=" + n(user_preferences.newest_limit) + "> hours") +
			br("Time offset: <input type=text name=time_offset size=3 maxlength=3 value=" + n(get_time_offset()) + "> hours") +
			p("<input type=submit value=Submit>"), "action=" + cgi.get_url() + " method=get") +
		get_bottom("");
}

Chtml page_preferences_submit()
{
	get_days();
	get_mts();
	get_field_length();
	get_time_offset();
	user_preferences.process(cgi, cookie);
	location = cgi.get_value("location");
	return page_forward();
}

Chtml show_msg(int slot, bool allow_reply)
{
	if (!slot)
		return "Error: invalid slot\n";
	t_msg msg;
	if (read_msg(slot, msg))
		return "Error: unable to read message " + n(slot) + "\n";
	if (!topic_f.is_open())
	{
		open_topic_f(false);
		if (read_topics())
			return "Error: unable to read topics\n";
	}
	msg.parent = topics[slot].parent;
	string body = fix_endl(msg.body);
	if (!topics.find(slot)->second.news())
		body = msg.flags & mf_allow_html ? fix_br(body) : web_magic_anchors(web_encode(body));
	if (config_int[ci_use_smilies] && msg.flags & mf_enable_smilies && user_preferences.show_smilies)
		body = web_magic_smilies(body);
	body = web_magic_quotes(body);
	Chtml r =
		br(get_name(msg.name, msg.mail) + " posted a message about " + html_span(web_encode(msg.subject), "class=subject") + (msg.parent ? " in reply to " + get_subject(topics[msg.parent].subject(), msg.parent) : "")) +
		p(body);
	if (config_int[ci_use_signature] && !msg.signature.empty() && user_preferences.show_signatures && get_c_lines(msg.signature) <= 4)
		r += p(msg.flags & mf_allow_html ? fix_br(fix_endl(msg.signature)) : web_magic_anchors(web_encode(fix_endl(msg.signature))), "class=signature");
	if (config_int[ci_use_uin] && msg.uin)
		r += p(get_icq_link(msg.uin, 2));
	if (config_int[ci_use_link_once] && !msg.link_once.empty())
		r += p(get_link("", msg.link_once));
	if (config_int[ci_use_link] && !msg.link.empty())
		r += p(get_link(msg.link_title, msg.link));
	if (admin)
	{
		Chtml d;
		if (msg.flags & mf_allow_html)
			d += an_self("Disable HTML", a_disable_html_msg, "slot=" + n(slot));
		else
			d += an_self("Enable HTML", a_enable_html_msg, "slot=" + n(slot));
		d += " | ";
		if (msg.flags & mf_locked)
			d += an_self("Unlock", a_unlock_msg, "slot=" + n(slot));
		else
			d += an_self("Lock", a_lock_msg, "slot=" + n(slot));
		int score = topics[slot].score;
		r += p(table(tr(td(br("Host: " + web_encode(get_host_name(msg.remote_addr))) + br("IP: " + ip2a(msg.remote_addr)) + br("Score: " + n(score) + " " + an_set_msg_score("+", slot, score + 1) + " " + an_set_msg_score("-", slot, score - 1)), "valign=bottom") + td(an_self("Edit", a_edit_msg, "slot=" + n(slot)) + " | " + d + " | " + an_self("Index", a_show_user, "name=" + uri_encode(msg.name)), "align=right valign=bottom")), "width=100%"));
	}
	else if (allow_reply && !cookie.has_value("name"))
		r += p("If this is your post, click " + an_self("here", a_import_into_cookie, "slot=" + n(slot)) + " to import name, mail, signature and link into your cookie.");
	string thread = show_thread(slot, 0, 0);
	if (!thread.empty())
	{
		r +=
			hr() +
			table(tr(thread_header(false)) + thread);
	}
	if (msg.flags & mf_locked)
	{
		r +=
			hr() +
			br("This message/thread has been locked.");
	}
	else if (allow_reply)
	{
		r +=
			hr() +
			br("If you would like to post a reply, use the form below.") +
			msg_form(create_reply(slot, msg));
	}
	else
	{
		r +=
			hr() +
			br("If you would like to post a reply, use " + an_show_msg("this", slot) + " link.");
	}
	cookie.set_value("last_shown_msg", max(cookie.get_value_int("last_shown_msg"), slot));
	return
		get_top(ht_message)
		+ r
		+ get_bottom("");
}

Chtml page_set_mf(int slot, int add, int remove)
{
	if (!admin)
		return page_admin_login();
	if (!slot)
		return "Error: invalid slot\n";
	t_msg msg;
	if (read_msg(slot, msg))
		return "Error: unable to read message " + n(slot) + "\n";
	msg.flags |= add;
	msg.flags &= ~remove;
	if (write_msg(slot, msg))
		return "Error: unable to write message\n";
	location = get_env("HTTP_REFERER");
	return
		get_top(ht_admin)
		+ "Click " + an_self("here", a_show_index) + " to return to the index.\n"
		+ get_bottom("");
}

Chtml page_edit_msg(int slot)
{
	if (!slot)
		return "Error: invalid slot\n";
	t_msg msg;
	if (read_msg(slot, msg))
		return "Error: unable to read message " + n(slot) + "\n";
	return
		get_top(ht_admin)
		+ msg_form(msg, slot, get_env("HTTP_REFERER"))
		+ get_bottom("");
}

Chtml page_set_msg_score(int slot, int score)
{
	open_topic_f(true);
	if (read_topics())
		return "Error: unable to read topics\n";
	t_topics::iterator i = topics.find(slot);
	if (i == topics.end())
		return "Error: invalid slot\n";
	i->second.score = score;
	topics_dirty = true;
	location = get_env("HTTP_REFERER");
	return
		get_top(ht_admin)
		+ "Click " + an_self("here", a_show_index) + " to return to the index.\n"
		+ get_bottom("");
}

Chtml page_set_user_score(string name, int score)
{
	open_topic_f(true);
	if (read_topics())
		return "Error: unable to read topics\n";
	name = to_lower(trim_white(name));
	for (t_topics::iterator i = topics.begin(); i != topics.end(); i++)
	{
		if (to_lower(trim_white(i->second.name())) != name)
			continue;
		i->second.score = score;
		topics_dirty = true;
	}
	location = get_env("HTTP_REFERER");
	return
		get_top(ht_admin)
		+ "Click " + an_self("here", a_show_index) + " to return to the index.\n"
		+ get_bottom("");
}

Chtml post_msg_submit()
{
	if (!is_complete())
		return post_msg();
	t_msg msg = get_msg_input();
	int slot = cgi.get_value_int("slot");
	bool edit = admin && slot;
	if (edit)
	{
		t_msg old_msg;
		if (!read_msg(slot, old_msg))
			msg.flags |= old_msg.flags & (mf_allow_html | mf_locked);
	}
	else
	{
		open_topic_f(true);
		if (read_topics())
		{
			return "Error: unable to read topics\n";
		}
		int current_date = get_time();
		for (t_topics::const_iterator i = topics.begin(); i != topics.end(); i++)
		{
			const t_topic& topic = i->second;
			if (current_date - topic.date > config_int[ci_flood_limit])
				break;
			if (topic.remote_addr != msg.remote_addr)
				continue;
			return "Error: flood protection, last message: " + an_show_msg(web_encode(topic.subject()), i->first);
		}
		slot = get_next_slot();
	}
	if (write_msg(slot, msg))
		return "Error: unable to write message\n";
	if (!edit)
	{
		topics[slot] = msg;
		topics_dirty = true;
		cookie.set_value("name", msg.name);
		cookie.set_value("mail", msg.mail);
		cookie.set_value("signature", msg.signature);
		cookie.set_value("uin", n(msg.uin));
		cookie.set_value("link_title", msg.link_title);
		cookie.set_value("link", msg.link);
		cookie.set_value("notify_icq", static_cast<bool>(msg.flags & mf_notify_icq));
		cookie.set_value("notify_mail", static_cast<bool>(msg.flags & mf_notify_mail));
		cookie.set_value("enable_smilies", static_cast<bool>(msg.flags & mf_enable_smilies));
		t_msg parent_msg;
		if (msg.parent && !read_msg(msg.parent, parent_msg))
		{
			if (config_int[ci_use_icq_notification] && parent_msg.uin && parent_msg.flags & mf_notify_icq)
			{
				string icq_msg = msg.name + " replied to " + parent_msg.subject + " on " + config_string[ct_forum_title] + "\n"
					+ "<a href=" + cgi.get_url() + "?action=" + n(a_show_msg) + "&slot=" + n(slot) + ">msg</a>";
				// send_icq_msg("", 0, "", "");
				// send_mail(forum_mail, n(parent_msg.uin) + "@pager.icq.com", "Forum reply notification", icq_msg);
				// send_mail(forum_mail, "OvdSpek@LIACS.NL", "Forum reply notification", icq_msg);
				send_mail(config_string[ct_forum_mail], n(parent_msg.uin) + "@pager.icq.com", "Forum reply notification", icq_msg);
				// send_mail(config_string[ct_forum_mail], n(parent_msg.uin) + "@pager.icq.com", "", icq_msg);
			}
			if (config_int[ci_use_mail_notification] && !parent_msg.mail.empty() && parent_msg.flags & mf_notify_mail)
			{
				Chtml email = "Content-type: text/html\n\n" +
					html(head_forum(true) + body(show_msg(slot, false)));
				send_mail(config_string[ct_forum_mail], web_encode(parent_msg.mail), "Forum reply notification", email);
			}
		}
	}
	location = cgi.get_value("location");
	return
		get_top(ht_message_posted) +
		"Your message has been posted, click " + an_self("here", a_show_index) + " to return to the index.\n" +
		get_bottom("");
};

Chtml page_import_into_cookie(int slot)
{
	if (!slot)
		return "Error: invalid slot\n";
	t_msg msg;
	if (read_msg(slot, msg))
		return "Error: unable to read message " + n(slot) + "\n";
	cookie.set_value("name", msg.name);
	cookie.set_value("mail", msg.mail);
	cookie.set_value("signature", msg.signature);
	cookie.set_value("uin", n(msg.uin));
	cookie.set_value("link_title", msg.link_title);
	cookie.set_value("link", msg.link);
	cookie.set_value("notify_icq", static_cast<bool>(msg.flags & mf_notify_icq));
	cookie.set_value("notify_mail", static_cast<bool>(msg.flags & mf_notify_mail));
	cookie.set_value("enable_smilies", static_cast<bool>(msg.flags & mf_enable_smilies));
	location = get_env("HTTP_REFERER");
	return "";
}

Chtml page_show_newest_messages()
{
	open_topic_f(false);
	if (read_topics())
		return "Error: unable to read topics\n";
	int current_date = get_time();
	Chtml page;
	for (t_topics::const_iterator i = topics.begin(); i != topics.end(); i++)
	{
		const t_topic& topic = i->second;
		if (topic.hidden())
			continue;
		if (current_date - topic.date > 3600 * user_preferences.newest_limit)
			break;
		Chtml r;
		if (user_preferences.show_date)
			r += td(cnv_date(topic.date), "nowrap");
		page += tr(
			td(an_show_msg(web_encode(topic.subject()), i->first))
			+ td(web_encode(topic.name()))
			+ r);
	}
	return 
		get_top(ht_newest_msgs) 
		+ "<meta http-equiv=refresh content=15>" 
		+ table(thread_header(false) + page)
		+ get_bottom(br("Count messages: " + n(static_cast<int>(topics.size())))
			+ br("Count threads: " + n(static_cast<int>(reverse_topics[0].size())))
			+ br("Current time: " + cnv_date(get_time()))
			+ br("Last msg time: " + cnv_date(get_thread_date(0)))
			+ br(html_size_stats()));
}

Chtml page_show_news()
{
	open_topic_f(false);
	if (read_topics())
		return "Error: unable to read topics\n";
	Chtml page;
	for (t_topics::const_iterator i = topics.begin(); i != topics.end(); i++)
	{
		t_msg msg;
		if (i->second.news() && !read_msg(i->first, msg))
		{
			page += table(tr(td("<img src=/Image2.gif> " + msg.subject) + td("Posted by " + get_name(msg.name, msg.mail) + " on " + cnv_date(i->second.date, true), "align=right")), "width=100%") + html_ul(msg.body + p(an_self("Comments", a_show_msg, "slot=" + n(i->first))) + " (" + n(get_thread_size(i->first) - 1) + ")");
		}
	}
	return page;
}

int main()
{
	if (0)
	{
		cout << "Content-type: text/html" << endl
			<< endl;
		if (read_config())
		{
			cout << "Error: unable to read config" << endl;
			return 0;
		}
		open_topic_f(false);
		if (read_topics())
		{
			cout << "Error: unable to read topics" << endl;
			return 0;
		}
		cout << topics.size() << endl;
		int current_date = get_time();
		Chtml page;
		for (t_topics::const_iterator i = topics.begin(); i != topics.end(); i++)
		{
			const t_topic& topic = i->second;
			if (topic.score < -9 || topic.score > 9 || topic.m_name < 0 || topic.m_name > 1 << 20)
			{
				page += tr(td("Skipping " + n(i->first)) + td(n(topic.m_subject)) + td(n(topic.m_name)));
				continue;
			}
			if (topic.hidden() || current_date - topic.date > 3600)
				continue;
			continue;
			Chtml r;
			if (user_preferences.show_date)
				r += td(cnv_date(topic.date), "nowrap");
			page += tr(
#if 0
				td(an_show_msg(web_encode(n(topic.m_subject)/*topic.subject()*/), i->first))
				+ td(web_encode(n(topic.m_name)/*topic.name()*/))
#else
				td(an_show_msg(web_encode(topic.subject()), i->first))
				+ td(web_encode(topic.name()))
#endif
				+ r);
		}
		cout << table(page) << endl;
		return 0;
	}
	Chtml page;
	t_cgi_error error = cgi.read();
	if (error != cgi_error_none)
	{
		page = br(cgi_error_text[error]);
	}
	else
	{
		if (read_config())
			page = "Error: unable to read config\n";
		else if (cgi.has_name("show_news"))
		{
			cout << "Content-type: text/html" << endl
				<< endl
				<< page_show_news();
			return 0;
		}
		else
		{
			admin = get_admin();
			if (admin)
			{
				config_int[ci_use_icq_notification] = true;
				config_int[ci_use_ladder] = true;
				open_topic_f(false);
				if (!topic_f.is_open() && cgi.has_name("create"))
					create_files();
				else
					topic_f.close();
			}
			user_preferences.load(cookie);
			int slot = cgi.get_value_int("slot");
			t_action action = static_cast<t_action>(cgi.get_value_int("action"));
			switch (action)
			{
			case a_admin_login:
				page = page_admin_login();
				break;
			case a_import_into_cookie:
				page = page_import_into_cookie(slot);
				break;
			case a_post_msg:
				page = post_msg();
				break;
			case a_post_msg_submit:
				page = post_msg_submit();
				break;
			case a_preferences_submit:
				page = page_preferences_submit();
				break;
			case a_show_ladder:
				page = ladder();
				break;
			case a_show_msg:
				page = show_msg(slot, true);
				break;
			case a_show_newest_msgs:
				page = page_show_newest_messages();
				break;
			case a_show_news:
				page = page_show_news();
				break;
			case a_show_preferences:
				page = preferences();
				break;
			default:
				if (admin)
				{
					switch (action)
					{
					case a_admin_logout:
						page = page_admin_logout();
						break;
					case a_disable_html_msg:
						page = page_set_mf(slot, 0, mf_allow_html);
						break;
					case a_edit_msg:
						page = page_edit_msg(slot);
						break;
					case a_enable_html_msg:
						page = page_set_mf(slot, mf_allow_html, 0);
						break;
					case a_lock_msg:
						page = page_set_mf(slot, mf_locked, 0);
						break;
					case a_set_msg_score:
						page = page_set_msg_score(slot, cgi.get_value_int("score"));
						break;
					case a_set_user_score:
						page = page_set_user_score(cgi.get_value("user"), cgi.get_value_int("score"));
						break;
					case a_show_banned_msgs:
						page = page_show_msgs_with_score(-1);
						break;
					case a_show_removed_msgs:
						page = page_show_msgs_with_score(-2);
						break;
					case a_show_ip:
						page = page_show_ip(a2ip(cgi.get_value("ip")));
						break;
					case a_show_user:
						page = page_show_user(cgi.get_value("name"));
						break;
					case a_unlock_msg:
						page = page_set_mf(slot, 0, mf_locked);
						break;
					default:
						page = forum();
					}
				}
				else
					page = forum();
			}
			if (topic_f.is_open())
			{
				if (topics_dirty)
				{
					if (write_topics())
						page = "Error: unable to write topics\n";
				}
				topic_f.close();
			}
			if (cgi.has_name("debug"))
			{
				page = table(tr(th("Name", "align=left") + th("Value", "align=left"))
					+ tr(td("Admin:") + td(n(admin)))
					+ tr(td("Cookie:") + td(web_encode(cgi.get_cookie())))
					+ tr(td("Home dir:") + td(web_encode(config_string[ct_home_dir])))
					+ tr(td("Private dir:") + td(web_encode(config_string[ct_private_dir])))
					+ tr(td("Public dir:") + td(web_encode(config_string[ct_public_dir])))
					+ tr(td("Document root:") + td(get_env("DOCUMENT_ROOT")))
					+ tr(td("Script filename:") + td(get_env("SCRIPT_FILENAME"))))
					+ hr()
					+ page; 
			}
			if (admin && cgi.has_name("show_config"))
			{
				Chtml t;
				for (int i = 0; i < ht_unknown; i++)
				{
					t += tr(td(config[i].ce_code) + td(web_encode(config_string[config[i].ce_id])));
				}
				page = table(tr(th("Name", "align=left") + th("Value", "align=left")) + t)
					+ hr() 
					+ page;
			}
		}
	}
	if (cgi.has_name("show_header"))
	{
		cout << "Content-type: text/html" << endl
			<< endl;
	}
	if (!location.empty())
	{
		cout << cookie
			<< "Location: " << location << endl
			<< endl;
	}
	else
	{
		cout << "Content-type: text/html" << endl
			<< cookie
			<< endl
			<< html(head_forum() + body(page));
	}
	return 0;
}