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

		ostream& export(ostream& os, int t) const;
		Csection();
		Csection(const string& _name, const string& _value);
	};

	typedef map<string, pair<string, Csection> > t_sections;

	ostream& export(ostream& os) const;
	int import(const Cvirtual_binary& d);
	Cgr_ini_reader();
	Cgr_ini_reader(const Cvirtual_binary& d);

	const t_sections& sections() const
	{
		return m_sections;
	}
protected:
	t_sections m_sections;
private:
	void eat_white();
	void eat_newline();
	int read_string(const string& a, string& v);
	int read_section(Csection& section);
	int read_sections();

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

	t_sections& sections()
	{
		return m_sections;
	}

	const t_sections& sections() const
	{
		return m_sections;
	}

};

ostream& operator<<(ostream& os, const Cgr_ini_reader& v);
ostream& operator<<(ostream& os, const Cgr_ini_reader::Csection& v);

#endif // !defined(AFX_GR_INI_READER_H__B14F22AB_6A52_4075_8719_F5E30E7AD8B2__INCLUDED_)
