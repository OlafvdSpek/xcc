// XCC Game Spy PlayerDoc.h : interface of the CXCCGameSpyPlayerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCCGAMESPYPLAYERDOC_H__8FD79312_24E1_42D1_8EDB_06DEF76C479F__INCLUDED_)
#define AFX_XCCGAMESPYPLAYERDOC_H__8FD79312_24E1_42D1_8EDB_06DEF76C479F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #include "xif_key.h"
#include "xif_key_r.h"

class CXCCGameSpyPlayerDoc : public CDocument
{
protected: // create from serialization only
	CXCCGameSpyPlayerDoc();
	DECLARE_DYNCREATE(CXCCGameSpyPlayerDoc)

// Attributes
public:
	const Cxif_key_r& key() const;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCGameSpyPlayerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXCCGameSpyPlayerDoc();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXCCGameSpyPlayerDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cxif_key_r m_key;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCGAMESPYPLAYERDOC_H__8FD79312_24E1_42D1_8EDB_06DEF76C479F__INCLUDED_)
