// INIDoc.h : interface of the CINIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIDOC_H__CBA4B64B_0846_11D5_B606_0000B4936994__INCLUDED_)
#define AFX_INIDOC_H__CBA4B64B_0846_11D5_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CCrystalTextBuffer.h"

class CINIDoc: public CDocument
{
protected: // create from serialization only
	CINIDoc();
	DECLARE_DYNCREATE(CINIDoc)

// Attributes
public:
	class CINIBuffer: public CCrystalTextBuffer
	{
	public:
		typedef map<string, int> t_section_list;

		virtual void UpdateViews(CCrystalTextView *pSource, CUpdateContext *pContext, DWORD dwUpdateFlags, int nLineIndex = -1);

		CINIBuffer(CINIDoc*pDoc) 
		{
			m_pOwnerDoc = pDoc; 
			m_section_list_valid = false;
		};

		virtual void SetModified(BOOL bModified = TRUE)
		{ 
			m_pOwnerDoc->SetModifiedFlag(bModified); 
		};

		const t_section_list& section_list()
		{
			if (!m_section_list_valid)
				create_section_list();
			return m_section_list;
		}

		bool view_validate()
		{
			if (m_section_list_view_valid)
				return true;
			m_section_list_view_valid = true;
			return false;
		}
	private:
		void create_section_list();

		CINIDoc* m_pOwnerDoc;		
		bool m_section_list_valid;
		bool m_section_list_view_valid;
		t_section_list m_section_list;
	};
	
	CFont m_font;
	CINIBuffer m_xTextBuffer;

// Operations
public:
	virtual void SetModifiedFlag(BOOL bModified = true);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CINIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CINIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CINIDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INIDOC_H__CBA4B64B_0846_11D5_B606_0000B4936994__INCLUDED_)
