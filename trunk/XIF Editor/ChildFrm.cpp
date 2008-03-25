#include "stdafx.h"
#include "XIF Editor.h"

#include "ChildFrm.h"

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return false;
	if (!m_wndSplitter.CreateView(0, 0,	RUNTIME_CLASS(CXIFTree), CSize(300, 0), pContext))
		return false;
	if (!m_wndSplitter.CreateView(0, 1,	RUNTIME_CLASS(CXIFList), CSize(0, 0), pContext))
		return false;
	m_tree = reinterpret_cast<CXIFTree*>(m_wndSplitter.GetPane(0, 0));
	m_list = reinterpret_cast<CXIFList*>(m_wndSplitter.GetPane(0, 1));
	m_tree->set_list(m_list);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}
