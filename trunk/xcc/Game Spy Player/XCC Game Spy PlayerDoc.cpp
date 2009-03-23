#include "stdafx.h"

#include "XCC Game Spy PlayerDoc.h"

IMPLEMENT_DYNCREATE(CXCCGameSpyPlayerDoc, CDocument)

BEGIN_MESSAGE_MAP(CXCCGameSpyPlayerDoc, CDocument)
END_MESSAGE_MAP()

void CXCCGameSpyPlayerDoc::Serialize(CArchive& ar)
{
	assert(!ar.IsStoring());
	int cb_s = ar.GetFile()->GetLength();
	Cvirtual_binary s;
	if (ar.Read(s.write_start(cb_s), cb_s) != cb_s
		|| m_key.import(s))
		AfxThrowArchiveException(CArchiveException::badIndex, ar.m_strFileName);
}
