// html_template.cpp: implementation of the Chtml_template class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "html_template.h"

#include <stack>
#include "multi_line.h"
#include "string_conversion.h"

enum t_template_element {te_if, te_else, te_endif, te_echo, te_literal};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Chtml_template::Chtml_template()
{
}

Chtml_template::Chtml_template(Cvirtual_binary v)
{
	*this = v;
}

Chtml_template Chtml_template::operator =(Cvirtual_binary v)
{
	m_value = v;
	return *this;
}

string Chtml_template::apply(Chtml_template v)
{
	return apply(v.m_value);
}

string Chtml_template::apply(Cvirtual_binary v)
{
	m_value = v;
	return static_cast<string>(*this);
}

void Chtml_template::r(string name, int value)
{
	r(name, n(value));
}

void Chtml_template::r(string name, string value)
{
	m_map[name] = value;
}

Chtml_template::operator string() const
{
	typedef stack<bool> t_stack;

	string d;
	const char* r = reinterpret_cast<const char*>(m_value.data());
	const char* r_end = reinterpret_cast<const char*>(m_value.data_end());
	t_stack stack;
	stack.push(true);
	while (r < r_end)
	{
		switch (*r++)
		{
			case te_if:
				{
					string p = r;
					r += p.length() + 1;
					t_map::const_iterator k = m_map.find(p);
					if (stack.top())
						stack.push((k != m_map.end() && !k->second.empty() && k->second != "0") || p == "1");
					else
						stack.push(false);
				}
				break;
			case te_else:
				if (stack.top())
					stack.top() = false;
				else 
				{
					stack.pop();
					stack.push(stack.top());
				}
				break;
			case te_endif: 
				stack.pop();
				assert(!stack.empty());
				break;
			case te_echo:
				if (stack.top())
				{
					t_map::const_iterator k = m_map.find(r);
					if (k != m_map.end())
						d += k->second;
				}
				r += strlen(r) + 1;
				break;
			case te_literal:
				if (stack.top())
					d += r;
				r += strlen(r) + 1;
				break;
			default:
				assert(false);
		}
	}
	assert(!stack.empty());
	stack.pop();
	assert(stack.empty());
	return d;
}

Ctemplate_write::Ctemplate_write()
{
	clear();
}

int Ctemplate_write::import_line(string s)
{
	m_repeat_line = false;
	if (string_equal_ip(s, "#"))
	{
		close_literal();
		Cmulti_line l = s.substr(1);
		string c = l.get_next_line(' ');
		string p = l.get_next_line(' ');
		if (string_equal_i(c, "define"))
		{
			if (!m_name.empty())
			{
				m_repeat_line = true;
				return 1;
			}
			m_name = p;
			if (!l.empty())
			{
				while (!l.empty())
					import_line(l.get_next_line(' '));
				return 1;
			}
		}
		else if (string_equal_ip(c, "if"))
		{
			*m_w++ = te_if;
			strcpy(m_w, p.c_str());
			m_w += p.length() + 1;
		}
		else if (string_equal_ip(c, "else"))
		{
			*m_w++ = te_else;
		}
		else if (string_equal_ip(c, "endif"))
		{
			*m_w++ = te_endif;
		}
		else
			assert(false);
	}
	else
	{
		s += ' ';
		for (int i = 0; i < s.length(); )
		{
			char c = s[i];
			if (c == '<' && string_equal_ip(s.c_str() + i, "<%"))
			{
				i += 2;
				int j = s.find("%>", i);
				assert(j != string::npos);	
				close_literal();
				*m_w++ = te_echo;
				strcpy(m_w, s.substr(i, j - i).c_str());
				m_w += j - i + 1;
				i = j + 2;
				continue;
			}
			open_literal();
			*m_w++ = c;
			i++;
		}
	}
	return 0;
}

void Ctemplate_write::open_literal()
{
	if (!m_literal_open)
	{
		*m_w++ = te_literal;
		m_literal_open = true;
	}
}

void Ctemplate_write::close_literal()
{
	if (m_literal_open)
	{
		*m_w++ = 0;
		m_literal_open = false;
	}
}

Cvirtual_binary Ctemplate_write::value()
{
	close_literal();
	m_d.size(m_w - reinterpret_cast<const char*>(m_d.data()));
	return m_d;
}

void Ctemplate_write::clear()
{
	m_w = reinterpret_cast<char*>(m_d.write_start(4 << 10));
	m_literal_open = false;
	m_name.erase();
}

