#pragma once

#include "XCC TMP EditorDoc.h"
#include "XCC TMP EditorView.h"
#include "virtual_image.h"	// Added by ClassView

class CLeftView : public CListView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CXCCTMPEditorDoc* GetDocument()
	{ 
		return (CXCCTMPEditorDoc*)m_pDocument; 
	}

// Operations
public:
	void autosize_colums();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void set_other_pane(CXCCTMPEditorView* other_pane);
	int load();
	int load_image(Cvirtual_image& image);
	int save_image(const Cvirtual_image& image);
	int compare(int id_a, int id_b);
	void invert_selection();
	void select_all();
	void sort_list(int i, bool reverse);
	void sync();
	int get_current_id();
	virtual ~CLeftView();

protected:

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CLeftView)
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnPopupDelete();
	afx_msg void OnUpdatePopupDelete(CCmdUI* pCmdUI);
	afx_msg void OnPopupInsert();
	afx_msg void OnUpdatePopupInsert(CCmdUI* pCmdUI);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPopupCopyExtraImage();
	afx_msg void OnUpdatePopupCopyExtraImage(CCmdUI* pCmdUI);
	afx_msg void OnPopupPasteExtraImage();
	afx_msg void OnUpdatePopupPasteExtraImage(CCmdUI* pCmdUI);
	afx_msg void OnPopupLoadaspcxExtraimage();
	afx_msg void OnUpdatePopupLoadaspcxExtraimage(CCmdUI* pCmdUI);
	afx_msg void OnPopupLoadaspcxImage();
	afx_msg void OnUpdatePopupLoadaspcxImage(CCmdUI* pCmdUI);
	afx_msg void OnPopupSaveaspcxExtraimage();
	afx_msg void OnPopupSaveaspcxImage();
	afx_msg void OnPopupProperties();
	afx_msg void OnUpdatePopupProperties(CCmdUI* pCmdUI);
	afx_msg void OnPopupCopyComplete();
	afx_msg void OnPopupPasteComplete();
	afx_msg void OnPopupLoadComplete();
	afx_msg void OnPopupSaveComplete();
	afx_msg void OnPopupDeleteExtraimage();
	afx_msg void OnUpdatePopupDeleteExtraimage(CCmdUI* pCmdUI);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	string m_buffer[4];
	int m_buffer_w;
	CXCCTMPEditorView* m_other_pane;
	int m_sort_column;
	bool m_sort_reverse;
};
