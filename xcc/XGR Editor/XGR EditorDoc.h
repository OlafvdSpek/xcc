// XGR EditorDoc.h : interface of the CXGREditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XGREDITORDOC_H__7549A6BD_924E_40C9_AC58_9DD14AB17B98__INCLUDED_)
#define AFX_XGREDITORDOC_H__7549A6BD_924E_40C9_AC58_9DD14AB17B98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXGREditorDoc : public CDocument
{
protected: // create from serialization only
	CXGREditorDoc();
	DECLARE_DYNCREATE(CXGREditorDoc)

// Attributes
public:
	typedef map<string, Cvirtual_binary> t_map;

	const t_map& map() const
	{
		return m_map;
	}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXGREditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void insert(const string& name, const Cvirtual_binary& d);
	void erase(const string& name);
	void SetModifiedFlag(BOOL bModified = true);
	virtual ~CXGREditorDoc();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXGREditorDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_map m_map;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XGREDITORDOC_H__7549A6BD_924E_40C9_AC58_9DD14AB17B98__INCLUDED_)
