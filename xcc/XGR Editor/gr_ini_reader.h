// gr_ini_reader.h: interface for the Cgr_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GR_INI_READER_H__B14F22AB_6A52_4075_8719_F5E30E7AD8B2__INCLUDED_)
#define AFX_GR_INI_READER_H__B14F22AB_6A52_4075_8719_F5E30E7AD8B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

bool opens_sub_section(const string& v);

class Cgr_ini_reader  
{
public:
	class Csection
	{
	public:
		typedef vector<Csection> t_sections;

		string name;
		string value;
		t_sections sections;		

		Csection()
		{
		}

		Csection(const string& _name, const string& _value)
		{
			name = _name;
			value = _value;
		}

		ostream& export(ostream& os, int t) const
		{
			if (!name.empty())
			{
				os << string(t, '\t') << name;
				if (!value.empty())
					os << '=' << value;
				os << endl;
			}
			for (Csection::t_sections::const_iterator i = sections.begin(); i != sections.end(); i++)
				i->export(os, t + 1);
			if (opens_sub_section(name))
				os << string(t, '\t') << "End" << endl;
			return os;
		}
	};

	typedef map<string, pair<string, Csection> > t_sections;

	const t_sections& sections() const
	{
		return m_sections;
	}

	ostream& export(ostream& os) const
	{
		for (t_sections::const_iterator i = m_sections.begin(); i != m_sections.end(); i++)
			export(os, i);
		return os;
	}

	static void export(ostream& os, t_sections::const_iterator i)
	{
		if (i->second.first.empty())
			os << i->first << endl;
		else
			os << i->second.first << ' ' << i->first << endl;
		ostream& operator<<(ostream& os, const Cgr_ini_reader::Csection& v);
		os << i->second.second
			<< "End" << endl
			<< endl;
	}

	Cgr_ini_reader();
	Cgr_ini_reader(const Cvirtual_binary& d);

	int import(const Cvirtual_binary& d)
	{
		m_s = m_r = reinterpret_cast<const char*>(d.data());
		m_s_end = m_s + d.size();
		return read_sections();
	}

	void eat_white()
	{
		while (m_r < m_s_end && (*m_r == '\t' || *m_r == ' '))
			m_r++;
	}

	void eat_newline()
	{
		while (m_r < m_s_end && (*m_r == '\t' || *m_r == '\n' || *m_r == '\r' || *m_r == ' '))
			m_r++;
		if (m_r < m_s_end && *m_r == ';')
		{
			while (m_r < m_s_end && *m_r != '\n' && *m_r != '\r')
				m_r++;
			eat_newline();
		}
	}

	int read_string(const string& a, string& v)
	{
		const char* t = m_r;
		const char* u = m_r;
		while (m_r < m_s_end && a.find_first_of(*m_r) == string::npos)
		{
			if (*m_r != '\t' && *m_r != ' ')
				u = m_r + 1;
			m_r++;
		}
		v = string(t, u - t);
		eat_white();
		return 0;
	}

	int read_section(Csection& section)
	{
		while (m_r < m_s_end)
		{
			eat_newline();
			string entry_name;
			if (read_string("\n\r ;=", entry_name))
				return 1;
			if (!stricmp(entry_name.c_str(), "End"))
				return 0;
			if (m_r < m_s_end && *m_r == '=')
				m_r++;				
			eat_white();
			string entry_value;
			if (read_string("\n\r;", entry_value))
				return 1;
			section.sections.push_back(Csection(entry_name, entry_value));
			if (opens_sub_section(entry_name))
			{
				if (read_section(*section.sections.rbegin()))
					return 1;
			}
		}
		return 1;
	}

	int read_sections()
	{
		m_sections.clear();
		eat_newline();
		while (m_r < m_s_end)
		{
			string section_t;
			string section_name;
			if (read_string("\t\n\r ;", section_t)
				|| read_string("\t\n\r ;", section_name))
				return 1;
			if (section_name.empty())
			{
				section_name = section_t;
				section_t.erase();
			}
			/*
			if (!stricmp(section_name.c_str(), "End"))
				cout << section_name << endl;
			*/
			m_sections[section_name].first = section_t;
			if (read_section(m_sections.find(section_name)->second.second))
				return 1;
			eat_newline();
		}
		return 0;
	}
protected:
	t_sections m_sections;
private:
	const char* m_s;
	const char* m_r;
	const char* m_s_end;

};

class Cgr_ini_editor: public Cgr_ini_reader
{
public:
	void erase(const string& v)
	{
		m_sections.erase(v);
	}
};

#endif // !defined(AFX_GR_INI_READER_H__B14F22AB_6A52_4075_8719_F5E30E7AD8B2__INCLUDED_)
