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
		if (m_top.save_start())
			AfxThrowArchiveException(CArchiveException::generic, ar.m_strFileName);
		else
		{
			ar.Write(m_top.key_data(), m_top.key_size());
			m_top.save_finish();
		}
	}
	else
	{
		int cb_s = ar.GetFile()->GetLength();
		byte* s = new byte[cb_s];
		if (ar.Read(s, cb_s) != cb_s ||
			m_top.load_key(s, cb_s))
			AfxThrowArchiveException(CArchiveException::badIndex, ar.m_strFileName);
		delete[] s;
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
