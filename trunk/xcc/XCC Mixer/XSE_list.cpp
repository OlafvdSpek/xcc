// XSE_list.cpp : implementation file
//

#include "stdafx.h"
#include "XSE_dlg.h"
#include "XSE_list.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXSE_list

CXSE_list::CXSE_list()
{
}

CXSE_list::~CXSE_list()
{
}


BEGIN_MESSAGE_MAP(CXSE_list, CListCtrl)
	//{{AFX_MSG_MAP(CXSE_list)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXSE_list message handlers

void CXSE_list::OnDropFiles(HDROP hDropInfo) 
{
	int c_files = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char fname[MAX_PATH];
	for (int i = 0; i < c_files; i++)
	{
		DragQueryFile(hDropInfo, i, fname, MAX_PATH);
		reinterpret_cast<CXSE_dlg*>(GetParent())->add_file(fname);
	}
	DragFinish(hDropInfo);
}
