// XCC Mod CreatorDoc.h : interface of the CXCCModCreatorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCCMODCREATORDOC_H__CA392AEE_CC6E_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_XCCMODCREATORDOC_H__CA392AEE_CC6E_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xcc_mod.h"

class CXCCModCreatorDoc : public CDocument
{
protected: // create from serialization only
	CXCCModCreatorDoc();
	DECLARE_DYNCREATE(CXCCModCreatorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCModCreatorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void deactivate();
	void activate();
	void clear_game_dir() const;
	void launch();
	bool contains(Cxcc_mod::t_category_type category, string fname);
	int export(string fname);
	int insert(Cxcc_mod::t_category_type category, string fname);
	Cxcc_mod::t_options options() const;
	void options(Cxcc_mod::t_options options);
	void remove(Cxcc_mod::t_category_type category, string fname);
	void report(string fname) const;
	Cxcc_mod::t_category_file_list category_file_list(Cxcc_mod::t_category_type category);
	void SetModifiedFlag(BOOL bModified = true);
	virtual ~CXCCModCreatorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXCCModCreatorDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cxcc_mod m_mod;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMODCREATORDOC_H__CA392AEE_CC6E_11D4_B606_0000B4936994__INCLUDED_)
