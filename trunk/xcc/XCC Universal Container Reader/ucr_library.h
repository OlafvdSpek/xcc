// ucr_library.h: interface for the Cucr_library class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCR_LIBRARY_H__C669055D_A076_4615_9173_BF71ECCF1C69__INCLUDED_)
#define AFX_UCR_LIBRARY_H__C669055D_A076_4615_9173_BF71ECCF1C69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Cucr_library  
{
public:
	typedef set<string> t_containers;
	typedef set<string> t_directories;

	void insert_directory(const string& v);
	void erase_directory(const string& v);
	void scan(const Cucr_formats& formats);
	Cxif_key export() const;
	void import(const Cxif_key& key);
	Cucr_library();

	const t_containers& containers() const
	{
		return m_containers;
	}

	const t_directories& directories() const
	{
		return m_directories;
	}
private:
	Cxif_key export_containers() const;
	Cxif_key export_directories() const;
	void import_containers(const Cxif_key& key);
	void import_directories(const Cxif_key& key);
	void scan(const Cucr_format& format);
	void scan(const Cucr_format& format, string dir);
	void scan(const Cucr_format& format, string dir, string ext);

	t_containers m_containers;
	t_directories m_directories;
};

#endif // !defined(AFX_UCR_LIBRARY_H__C669055D_A076_4615_9173_BF71ECCF1C69__INCLUDED_)
