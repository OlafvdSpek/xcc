// cgi_input.h: interface for the Ccgi_input class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGI_INPUT_H__BA6CFA71_E9CA_11D3_B81A_0000F81AF3F7__INCLUDED_)
#define AFX_CGI_INPUT_H__BA6CFA71_E9CA_11D3_B81A_0000F81AF3F7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <map>
#include <string>

using namespace std;

enum t_cgi_error {
	cgi_error_none, 
	cgi_error_unsupported_request_method,
	cgi_error_unsupported_content_type,
	cgi_error_unsupported_content_length,
	cgi_error_unable_to_read_content,
	cgi_error_server_name_unavailable,
	cgi_error_script_name_unavailable};

extern const char* cgi_error_text[];

enum t_content_type {ct_application, ct_multipart, ct_unknown};
enum t_request_method {rm_get, rm_post, rm_unknown};

typedef map<string, string> t_cgi_input;

class Ccgi_input  
{
public:
	Ccgi_input();
	t_cgi_error read();
	static string get_cookie();
	string get_value(const string& name) const;
	int get_value_int(const string& name) const;
	bool has_name(const string& name) const;
	bool has_value(const string& name) const;

	const t_cgi_input& get_input() const
	{
		return m_input;
	}

	string get_url() const
	{
		return m_url;
	}
private:
	t_cgi_input m_input;
	string m_url;
};

t_cgi_input get_cgi_pairs(const string& pairs);
string get_env(const string& name);
string uri_decode(const string& v);
string uri_encode(const string v);
string web_decode(const string& v);
string web_encode(const string& v, bool add_br = true);
int get_hash(const string& v);
string xor_decode(const string& v);
string xor_encode(const string& v);

#endif // !defined(AFX_CGI_INPUT_H__BA6CFA71_E9CA_11D3_B81A_0000F81AF3F7__INCLUDED_)
