// XCC Universal Container ReaderView.h : interface of the CXCCUniversalContainerReaderView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCCUNIVERSALCONTAINERREADERVIEW_H__12585D6C_AEF0_4E7D_868C_414970863D4A__INCLUDED_)
#define AFX_XCCUNIVERSALCONTAINERREADERVIEW_H__12585D6C_AEF0_4E7D_868C_414970863D4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXCCUniversalContainerReaderView : public CListView
{
protected: // create from serialization only
	CXCCUniversalContainerReaderView();
	DECLARE_DYNCREATE(CXCCUniversalContainerReaderView)

// Attributes
public:
	CXCCUniversalContainerReaderDoc* GetDocument();

	const Cucr_container& container()
	{
		return GetDocument()->container();
	}

// Operations
public:
	int compare(int id_a, int id_b);
	void sort_items(int i, bool reverse);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCUniversalContainerReaderView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	void auto_size();
	virtual ~CXCCUniversalContainerReaderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CXCCUniversalContainerReaderView)
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPopupCopyTo();
	afx_msg void OnUpdatePopupCopyTo(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditInvertSelection();
	afx_msg void OnPopupOpen();
	afx_msg void OnUpdatePopupOpen(CCmdUI* pCmdUI);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	string m_buffer[4];
	int m_buffer_w;
	string m_output_dir;
	int m_sort_column;
	bool m_sort_reverse;
};

#ifndef _DEBUG  // debug version in XCC Universal Container ReaderView.cpp
inline CXCCUniversalContainerReaderDoc* CXCCUniversalContainerReaderView::GetDocument()
   { return (CXCCUniversalContainerReaderDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCUNIVERSALCONTAINERREADERVIEW_H__12585D6C_AEF0_4E7D_868C_414970863D4A__INCLUDED_)
