// INIDoc.cpp : implementation of the CINIDoc class
//

#include "stdafx.h"
#include "XCC INI Editor.h"

#include "inichildfrm.h"
#include "INIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CINIDoc

IMPLEMENT_DYNCREATE(CINIDoc, CDocument)

BEGIN_MESSAGE_MAP(CINIDoc, CDocument)
	//{{AFX_MSG_MAP(CINIDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CINIDoc::CINIBuffer::create_section_list()
{
	t_section_list section_list;
	for (int l = 0; l < GetLineCount(); l++)
	{
		const SLineInfo& line = GetLine(l);
		if (line.cc_index(SLineInfo::te_header_name))
		{
			section_list[line.t_index(SLineInfo::te_header_name)] = l;
		}
	}
	if (section_list != m_section_list)
	{
		m_section_list = section_list;
		m_section_list_view_valid = false;
	}
	m_section_list_valid = true;
}

void CINIDoc::CINIBuffer::UpdateViews(CCrystalTextView *pSource, CUpdateContext *pContext, DWORD dwUpdateFlags, int nLineIndex)
{
	CCrystalTextBuffer::UpdateViews(pSource, pContext, dwUpdateFlags, nLineIndex);
	m_section_list_valid = false;
	// reinterpret_cast<CINIChildFrame*>(GetParentFrame())->GetLeftPane()->Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
// CINIDoc construction/destruction

CINIDoc::CINIDoc():
	m_xTextBuffer(this)
{
	m_font.CreatePointFont(110, "Courier");
}

CINIDoc::~CINIDoc()
{
}

BOOL CINIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_xTextBuffer.InitNew();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CINIDoc serialization

void CINIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CINIDoc diagnostics

#ifdef _DEBUG
void CINIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CINIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CINIDoc commands

void CINIDoc::DeleteContents() 
{
	m_xTextBuffer.FreeAll();
	
	CDocument::DeleteContents();
}

BOOL CINIDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	return m_xTextBuffer.LoadFromFile(lpszPathName);
}

BOOL CINIDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	m_xTextBuffer.SaveToFile(lpszPathName);
	return TRUE;
}

void CINIDoc::SetModifiedFlag(BOOL bModified)
{
	if (IsModified() == bModified)
		return;
	CDocument::SetModifiedFlag(bModified);
	CString title = GetTitle();
	if (bModified)
	{
		if (title.Find('*') < 0)
			title += '*';
	}
	else
	{
		if (title.Find('*') >= 0)
			title.Delete(title.GetLength() - 1);
	}
	SetTitle(title);
}

