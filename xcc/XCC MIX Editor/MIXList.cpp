// MIXList.cpp : implementation file
//

#include "stdafx.h"
#include "MIXList.h"
#include "XCC MIX Editor.h"
#include "XCC MIX EditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMIXList

CMIXList::CMIXList()
{
}

CMIXList::~CMIXList()
{
}


BEGIN_MESSAGE_MAP(CMIXList, CListCtrl)
	//{{AFX_MSG_MAP(CMIXList)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMIXList message handlers

void CMIXList::OnDropFiles(HDROP hDropInfo) 
{
	int c_files = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char fname[MAX_PATH];
	for (int i = 0; i < c_files; i++)
	{
		DragQueryFile(hDropInfo, i, fname, MAX_PATH);
		reinterpret_cast<CXCCMIXEditorDlg*>(GetParent())->add_file(fname);
	}
	DragFinish(hDropInfo);
}
