#include "html.h"

bool web_is_protocol_name(string v);
bool web_is_server_name(const string& v);
bool web_is_mail(const string& v);
bool web_is_link(const string& v);
Chtml web_name(const string& name, const string& mail);
Chtml web_link(const string& link_title, const string& link);
Chtml web_magic_anchors(const string& v);