// XCC EditorDoc.h : interface of the CXCCEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCCEDITORDOC_H__4E596E2C_F686_11D2_B601_D35C3DCCB8F1__INCLUDED_)
#define AFX_XCCEDITORDOC_H__4E596E2C_F686_11D2_B601_D35C3DCCB8F1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "cc_file.h"
#include "xcc_level.h"

class CXCCEditorDoc : public CDocument
{
public:
	Cxcc_level level;
protected: // create from serialization only
	CXCCEditorDoc();
	DECLARE_DYNCREATE(CXCCEditorDoc)

// Attributes
public:

// Operations
public:
	long load(const word* bin, const byte* ini, dword size);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXCCEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXCCEditorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCEDITORDOC_H__4E596E2C_F686_11D2_B601_D35C3DCCB8F1__INCLUDED_)
