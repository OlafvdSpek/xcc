#pragma once

#include "ListCtrlEx.h"
#include "MainFrm.h"
#include "resource.h"

class CSelectPaletDlg : public ETSLayoutDialog
{
public:
	void check_selection();
	void update_list(int parent_id, int current_palet);
	void insert_tree_entry(int parent_id, HTREEITEM parent_item);
	void set(CMainFrame* main_frame, t_pal_map_list pal_map_list, t_pal_list pal_list);
	CSelectPaletDlg(CWnd* pParent = NULL);   // standard constructor

	int current_palet() const
	{
		return m_current_palet;
	}

	void current_palet(int v)
	{
		m_current_palet = v;
	}

	//{{AFX_DATA(CSelectPaletDlg)
	enum { IDD = IDD_SELECT_PALET };
	CButton	m_ok;
	CTreeCtrl	m_tree;
	CListCtrlEx	m_list;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CSelectPaletDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CSelectPaletDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_pal_map_list m_pal_map_list;
	t_pal_list m_pal_list;
	int m_current_palet;
	CMainFrame* m_main_frame;
};
