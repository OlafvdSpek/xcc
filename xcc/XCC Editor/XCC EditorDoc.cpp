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

long CXCCEditorDoc::load(const Cvirtual_binary& bin, const Cvirtual_binary& ini)
{
	CWaitCursor wait;
	DeleteContents();
	SetModifiedFlag(false);
	return level.load(bin, ini);
}

void CXCCEditorDoc::Serialize(CArchive& ar)
{
	Cfname fname = string(ar.m_strFileName);
	fname.set_ext(".bin");
	Cvirtual_binary bin_data;
	Cvirtual_binary ini_data;
	if (ar.IsStoring())
	{
		level.save(bin_data, ini_data);
		ar.Write(ini_data.data(), ini_data.size());
		bin_data.export(fname);
	}
	else
	{
		ini_data.write_start(64 << 10);
		ini_data.size(ar.Read(ini_data.data_edit(), ini_data.size()));
		Cbin_file f;
		f.open(fname);
		bin_data = f.get_vdata();
		f.close();
		if (load(bin_data, ini_data))
			AfxThrowArchiveException(CArchiveException::badIndex, ar.m_strFileName);
	}
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
