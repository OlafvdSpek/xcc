// XCC MixerDoc.h : interface of the CXCCMixerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCCMIXERDOC_H__9452141C_D8CC_11D3_9F8E_0000F81AF9BE__INCLUDED_)
#define AFX_XCCMIXERDOC_H__9452141C_D8CC_11D3_9F8E_0000F81AF9BE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CXCCMixerDoc : public CDocument
{
protected: // create from serialization only
	CXCCMixerDoc();
	DECLARE_DYNCREATE(CXCCMixerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCMixerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXCCMixerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXCCMixerDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCMIXERDOC_H__9452141C_D8CC_11D3_9F8E_0000F81AF9BE__INCLUDED_)
