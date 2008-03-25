#pragma once

#include "xcc_mod.h"

class CXCCModCreatorDoc : public CDocument
{
protected: // create from serialization only
	CXCCModCreatorDoc();
	DECLARE_DYNCREATE(CXCCModCreatorDoc)

public:

	//{{AFX_VIRTUAL(CXCCModCreatorDoc)
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	int add_mode(string name);
	int add_module(string name);
	int activate();
	void clear_game_dir() const;
	void deactivate();
	int launch();
	bool contains(Cxcc_mod::t_category_type category, string fname);
	Cxcc_mod::t_file_properties file_properties(Cxcc_mod::t_category_type category, string fname) const;
	void file_properties(Cxcc_mod::t_category_type category, string fname, Cxcc_mod::t_file_properties properties);
	int export(string fname, Cvirtual_binary exe, int compression);
	int insert(Cxcc_mod::t_category_type category, string fname);
	Cxcc_mod::t_options options() const;
	void options(Cxcc_mod::t_options options);
	void remove(Cxcc_mod::t_category_type category, string fname);
	void report(string fname) const;
	Cxcc_mod::t_category_file_list category_file_list(Cxcc_mod::t_category_type category);
	void SetModifiedFlag(BOOL bModified = true);
	virtual ~CXCCModCreatorDoc();

	const Cxcc_mod& mod() const
	{
		return m_mod;
	}

protected:
	//{{AFX_MSG(CXCCModCreatorDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cxcc_mod m_mod;
};
