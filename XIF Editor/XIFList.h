#pragma once

#include <afxcview.h>
#include "XIF EditorDoc.h"

class CXIFList : public CListView
{
protected:
	CXIFList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CXIFList)

// Attributes
public:
	CXIFEditorDoc* GetDocument()
	{
		return static_cast<CXIFEditorDoc*>(m_pDocument);
	}

// Operations
public:
	int get_current_index();
	int get_free_id();
	void open_key(Cxif_key* key);
	void close_key();
	void insert_key();
	int insert_value(int id);
	void update_value(int i, int id);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXIFList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CXIFList();

	// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CXIFList)
	afx_msg void OnPopupEditValue();
	afx_msg void OnUpdatePopupEditName(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupEditValue(CCmdUI* pCmdUI);
	afx_msg void OnPopupInsertBin32();
	afx_msg void OnPopupInsertBinary();
	afx_msg void OnPopupInsertInt32();
	afx_msg void OnPopupInsertString();
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPopupLoadValuePcx();
	afx_msg void OnUpdatePopupLoadValuePcx(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cxif_key* m_key;
};
