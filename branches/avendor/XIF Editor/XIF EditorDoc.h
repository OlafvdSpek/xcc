// XIF EditorDoc.h : interface of the CXIFEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XIFEDITORDOC_H__14AD0AAC_1DC3_11D4_B605_0000B4936994__INCLUDED_)
#define AFX_XIFEDITORDOC_H__14AD0AAC_1DC3_11D4_B605_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xif_key.h"

class CXIFEditorDoc : public CDocument
{
protected: // create from serialization only
	CXIFEditorDoc();
	DECLARE_DYNCREATE(CXIFEditorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXIFEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	Cxif_key& get_top();
	virtual ~CXIFEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXIFEditorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cxif_key m_top;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XIFEDITORDOC_H__14AD0AAC_1DC3_11D4_B605_0000B4936994__INCLUDED_)
