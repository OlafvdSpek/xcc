// XIF EditorDoc.cpp : implementation of the CXIFEditorDoc class
//

#include "stdafx.h"
#include "XIF Editor.h"

#include "XIF EditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXIFEditorDoc

IMPLEMENT_DYNCREATE(CXIFEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CXIFEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CXIFEditorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXIFEditorDoc construction/destruction

CXIFEditorDoc::CXIFEditorDoc()
{
	// TODO: add one-time construction code here

}

CXIFEditorDoc::~CXIFEditorDoc()
{
}

BOOL CXIFEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CXIFEditorDoc serialization

void CXIFEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		Cvirtual_binary d = m_top.vdata();
		ar.Write(d.data(), d.size());
	}
	else
	{
		Cvirtual_binary s;
		int cb_s = ar.GetFile()->GetLength();
		if (ar.Read(s.write_start(cb_s), cb_s) != cb_s ||
			m_top.load_key(s))
			AfxThrowArchiveException(CArchiveException::badIndex, ar.m_strFileName);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CXIFEditorDoc diagnostics

#ifdef _DEBUG
void CXIFEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXIFEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXIFEditorDoc commands

Cxif_key& CXIFEditorDoc::get_top()
{
	return m_top;
}
