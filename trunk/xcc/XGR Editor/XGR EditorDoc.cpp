// XGR EditorDoc.cpp : implementation of the CXGREditorDoc class
//

#include "stdafx.h"
#include "XGR Editor.h"

#include "XGR EditorDoc.h"

#include "big_file.h"
#include "big_file_write.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXGREditorDoc

IMPLEMENT_DYNCREATE(CXGREditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CXGREditorDoc, CDocument)
	//{{AFX_MSG_MAP(CXGREditorDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXGREditorDoc construction/destruction

CXGREditorDoc::CXGREditorDoc()
{
}

CXGREditorDoc::~CXGREditorDoc()
{
}

BOOL CXGREditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CXGREditorDoc commands

BOOL CXGREditorDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	Cbig_file f;
	if (f.open(lpszPathName))
		return false;
	m_map.clear();
	const Cbig_file::t_index& index = f.index();
	for (Cbig_file::t_index::const_iterator i = index.begin(); i != index.end(); i++)
		m_map[i->first] = f.get_vdata().sub_bin(i->second.offset, i->second.size);
	f.close();
	return true;
}

BOOL CXGREditorDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	{
		for (t_map::iterator i = m_map.begin(); i != m_map.end(); i++)
			i->second.data_edit();
	}
	Cbig_file_write f;
	for (t_map::const_iterator i = m_map.begin(); i != m_map.end(); i++)
		f.insert(i->first, i->second);
	if (f.write().export("c:/temp/XGR Editor output.big"))
		return false;
	SetModifiedFlag(false);
	return true;
}

void CXGREditorDoc::erase(const string& name)
{
	m_map.erase(name);
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

void CXGREditorDoc::insert(const string& name, const Cvirtual_binary& d)
{
	m_map[name] = d;
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

void CXGREditorDoc::SetModifiedFlag(BOOL bModified)
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

