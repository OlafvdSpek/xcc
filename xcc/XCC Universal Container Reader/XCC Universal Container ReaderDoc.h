// XCC Universal Container ReaderDoc.h : interface of the CXCCUniversalContainerReaderDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCCUNIVERSALCONTAINERREADERDOC_H__A575A397_AE97_4117_BF92_DCE307C0A524__INCLUDED_)
#define AFX_XCCUNIVERSALCONTAINERREADERDOC_H__A575A397_AE97_4117_BF92_DCE307C0A524__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ucr_container_simple.h"

class CXCCUniversalContainerReaderDoc : public CDocument
{
protected: // create from serialization only
	CXCCUniversalContainerReaderDoc();
	DECLARE_DYNCREATE(CXCCUniversalContainerReaderDoc)

// Attributes
public:
	const Cucr_container& container() const
	{
		return *m_container;
	}

	CXCCUniversalContainerReaderApp* app()
	{
		return reinterpret_cast<CXCCUniversalContainerReaderApp*>(AfxGetApp());
	}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCUniversalContainerReaderDoc)
	public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXCCUniversalContainerReaderDoc();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXCCUniversalContainerReaderDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cucr_container* m_container;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCUNIVERSALCONTAINERREADERDOC_H__A575A397_AE97_4117_BF92_DCE307C0A524__INCLUDED_)
