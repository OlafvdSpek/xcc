#include "stdafx.h"
#include "XIF Editor.h"

#include "XIF EditorDoc.h"

IMPLEMENT_DYNCREATE(CXIFEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CXIFEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CXIFEditorDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CXIFEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		Cvirtual_binary d = m_top.vdata(true);
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
