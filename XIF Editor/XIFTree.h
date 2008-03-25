#pragma once

#include <afxcview.h>
#include "XIF EditorDoc.h"
#include "XIFList.h"

class CXIFTree : public CTreeView
{
protected:
	CXIFTree();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CXIFTree)

// Attributes
public:
	CXIFEditorDoc* GetDocument()
	{
		return static_cast<CXIFEditorDoc*>(m_pDocument);
	}

// Operations
public:
	HTREEITEM get_current_index();
	Cxif_key& get_key(HTREEITEM e);
	void insert_key(int id, Cxif_key& key, HTREEITEM parent);
	void set_list(CXIFList* list);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXIFTree)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CXIFTree();

	// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CXIFTree)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPopupRemove();
	afx_msg void OnUpdatePopupRemove(CCmdUI* pCmdUI);
	afx_msg void OnPopupInsert();
	afx_msg void OnUpdatePopupInsert(CCmdUI* pCmdUI);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CXIFList* m_list;
};
