// XCC Mod CreatorDoc.cpp : implementation of the CXCCModCreatorDoc class
//

#include "stdafx.h"
#include "XCC Mod Creator.h"

#include "XCC Mod CreatorDoc.h"

#include "file32.h"

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
		Cxif_key k = m_mod.save(false);
		if (k.save_start())
			AfxThrowArchiveException(CArchiveException::generic, ar.m_strFileName);
		else
		{
			ar.Write(k.key_data(), k.key_size());
			k.save_finish();
		}
	}
	else
	{
		Cxif_key k;
		int cb_s = ar.GetFile()->GetLength();
		byte* s = new byte[cb_s];
		if (ar.Read(s, cb_s) != cb_s ||
			k.load_key(s, cb_s) || m_mod.load(k))
			AfxThrowArchiveException(CArchiveException::badIndex, ar.m_strFileName);
		delete[] s;
	}
}

int CXCCModCreatorDoc::export(string fname)
{
	Cxif_key k = m_mod.save(true);
	int error = k.save_start();
	if (!error)
	{
		error = file32_write(fname, k.key_data(), k.key_size());
		k.save_finish();
	}
	return error;
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

void CXCCModCreatorDoc::clear_game_dir()
{
	m_mod.clear_game_dir();
}
