// XCC Mod CreatorDoc.cpp : implementation of the CXCCModCreatorDoc class
//

#include "stdafx.h"
#include "XCC Mod Creator.h"

#include "mainfrm.h"
#include "XCC Mod CreatorDoc.h"

#include "file32.h"
#include "fname.h"
#include "string_conversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCModCreatorDoc

IMPLEMENT_DYNCREATE(CXCCModCreatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CXCCModCreatorDoc, CDocument)
	//{{AFX_MSG_MAP(CXCCModCreatorDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCModCreatorDoc construction/destruction

CXCCModCreatorDoc::CXCCModCreatorDoc()
{
}

CXCCModCreatorDoc::~CXCCModCreatorDoc()
{
}

BOOL CXCCModCreatorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_mod.clear();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CXCCModCreatorDoc serialization

void CXCCModCreatorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		Cvirtual_binary d = m_mod.save(false).vdata();
		ar.Write(d.data(), d.size());
	}
	else
	{
		Cfname fname = static_cast<string>(ar.m_strFileName);
		bool import = to_lower(fname.get_fext()) == ".xmlf";
		if (import)
		{
			fname.set_ext(".xmcf");
			SetModifiedFlag();
			SetPathName(static_cast<string>(fname).c_str(), false);
		}
		fname.set_ext("");
		fname.make_path();
		Cxif_key k;
		int cb_s = ar.GetFile()->GetLength();
		byte* s = new byte[cb_s];
		if (ar.Read(s, cb_s) != cb_s 
			|| k.load_key(s, cb_s) 
			|| m_mod.load(k, fname))
			AfxThrowArchiveException(CArchiveException::badIndex, ar.m_strFileName);
		delete[] s;
	}
}

int CXCCModCreatorDoc::export(string fname, Cvirtual_binary exe)
{
	if (exe.data())
	{
		Cvirtual_binary mod = m_mod.save(true).vdata();
		Cfile32 f;
		int error = f.open_write(fname);
		if (!error)
			error = f.write(exe.data(), exe.size());
		if (!error)
			error = f.write(mod.data(), mod.size());
		if (!error)
			error = f.write(mod.size());
		f.close();
		return error;
	}
	return m_mod.save(true).vdata().export(fname);
}

/////////////////////////////////////////////////////////////////////////////
// CXCCModCreatorDoc diagnostics

#ifdef _DEBUG
void CXCCModCreatorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXCCModCreatorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXCCModCreatorDoc commands

void CXCCModCreatorDoc::SetModifiedFlag(BOOL bModified)
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

bool CXCCModCreatorDoc::contains(Cxcc_mod::t_category_type category, string fname)
{
	return m_mod.contains(category, fname);
}

int CXCCModCreatorDoc::insert(Cxcc_mod::t_category_type category, string fname)
{
	SetModifiedFlag();
	return m_mod.insert(category, fname);
}

void CXCCModCreatorDoc::remove(Cxcc_mod::t_category_type category, string fname)
{
	SetModifiedFlag();
	m_mod.remove(category, fname);
}

Cxcc_mod::t_category_file_list CXCCModCreatorDoc::category_file_list(Cxcc_mod::t_category_type category)
{
	return m_mod.category_file_list(category);
}

Cxcc_mod::t_options CXCCModCreatorDoc::options() const
{
	return m_mod.options();
}

void CXCCModCreatorDoc::options(Cxcc_mod::t_options options)
{
	SetModifiedFlag();
	m_mod.options(options);
}

void CXCCModCreatorDoc::activate()
{
	m_mod.activate();
}

void CXCCModCreatorDoc::launch()
{
	m_mod.activate();
	m_mod.launch_game(false);
}

void CXCCModCreatorDoc::deactivate()
{
	m_mod.deactivate(false);
}

void CXCCModCreatorDoc::clear_game_dir() const
{
	m_mod.clear_game_dir();
}

void CXCCModCreatorDoc::report(string fname) const
{
	m_mod.report(fname);
}
