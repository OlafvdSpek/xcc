// XCC EditorDoc.cpp : implementation of the CXCCEditorDoc class
//

#include "stdafx.h"
#include "XCC Editor.h"
#include "XCC EditorDoc.h"
#include "bin_file.h"
#include "edit_map_dlg.h"
#include "fname.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCEditorDoc

IMPLEMENT_DYNCREATE(CXCCEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CXCCEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CXCCEditorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCEditorDoc construction/destruction

CXCCEditorDoc::CXCCEditorDoc()
{
	// TODO: add one-time construction code here

}

CXCCEditorDoc::~CXCCEditorDoc()
{
}

BOOL CXCCEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return false;

	level.clear();
	return true;
}



/////////////////////////////////////////////////////////////////////////////
// CXCCEditorDoc serialization

long CXCCEditorDoc::load(const word* bin, const byte* ini, dword size)
{
	CWaitCursor wait;
	DeleteContents();
	SetModifiedFlag(false);
	return level.load(bin, ini, size);
}

void CXCCEditorDoc::Serialize(CArchive& ar)
{
	Cfname fname = string(ar.m_strFileName);
	fname.set_ext(".bin");
	const dword max_size = 64 * 1024;
	word* bin_data;
	byte* ini_data;
	dword size;
	if (ar.IsStoring())
	{
		level.save(bin_data, ini_data, size);
		ar.Write(ini_data, size);
		Cfile32 f;
		f.open_write(fname);
		f.write(bin_data, 8192);
		f.close();
	}
	else
	{
		bin_data = new word[4096];
		ini_data = new byte[max_size];
		size = ar.Read(ini_data, max_size);
		Cbin_file f;
		f.open(fname);
		memcpy(bin_data, f.get_data(), 8192);
		f.close();
		if (load(bin_data, ini_data, size))
			AfxThrowArchiveException(CArchiveException::badIndex, ar.m_strFileName);
	}
	delete[] ini_data;
	delete[] bin_data;
}

/////////////////////////////////////////////////////////////////////////////
// CXCCEditorDoc diagnostics

#ifdef _DEBUG
void CXCCEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXCCEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXCCEditorDoc commands
