#include "stdafx.h"

#include "mainfrm.h"
#include "XCC Mod CreatorDoc.h"

#include <boost/algorithm/string.hpp>
#include "file32.h"
#include "fname.h"
#include "string_conversion.h"

using namespace boost;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CXCCModCreatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CXCCModCreatorDoc, CDocument)
	//{{AFX_MSG_MAP(CXCCModCreatorDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

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

void CXCCModCreatorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		m_mod.compact();
		Cvirtual_binary d = m_mod.save(false, -1).vdata();
		ar.Write(d.data(), d.size());
	}
	else
	{
		Cfname fname = static_cast<string>(ar.m_strFileName);
		bool import = to_lower_copy(fname.get_fext()) == ".xmlf";
		if (import)
		{
			fname.set_ext(".xmcf");
			SetModifiedFlag();
			SetPathName(static_cast<string>(fname).c_str(), false);
		}
		fname.set_ext("");
		fname.make_path();
		Cxif_key k;
		Cvirtual_binary s(NULL, ar.GetFile()->GetLength());
		if (ar.Read(s.data_edit(), s.size()) != s.size())
			AfxThrowArchiveException(CArchiveException::badIndex, ar.m_strFileName);
		if (s.size() >= 4)
		{
			int cb_mod = *reinterpret_cast<const __int32*>(s.data_end() - 4);
			if (cb_mod >= 4 && s.size() >= 4 + cb_mod && !memcmp(s.data_end() - 4 - cb_mod, "XIF\x1a", 4))
				s = Cvirtual_binary(s.data_end() - 4 - cb_mod, cb_mod);
		}
		if (k.load_key(s)
			|| m_mod.load(k, fname))
			AfxThrowArchiveException(CArchiveException::badIndex, ar.m_strFileName);
	}
}

static Cvirtual_binary compress(const Cxif_key& v, int compression)
{
	switch (compression)
	{
	case 0:
		return v.vdata(true);
	case 2:
		return v.vdata();
	}
	return v.export_bz();
}

int CXCCModCreatorDoc::export(string fname, Cvirtual_binary exe, int compression)
{
	int error;
	if (exe.data())
	{
		Cvirtual_binary mod = compress(m_mod.save(true, -1), compression);
		Cfile32 f;
		error = f.open_write(fname);
		if (!error)
			error = f.write(exe.data(), exe.size());
		if (!error)
			error = f.write(mod.data(), mod.size());
		if (!error)
			error = f.write(mod.size());
		f.close();
	}
	else
		error = compress(m_mod.save(true, -1), compression).save(fname);
	if (!error)
		error = m_mod.save_modules(fname);
	return error;
}

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
	UpdateAllViews(NULL);
	return m_mod.insert(category, fname);
}

void CXCCModCreatorDoc::remove(Cxcc_mod::t_category_type category, string fname)
{
	m_mod.remove(category, fname);
	SetModifiedFlag();
	UpdateAllViews(NULL);
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
	m_mod.options(options);
	SetModifiedFlag();
}

int CXCCModCreatorDoc::activate()
{
	return m_mod.activate();
}

int CXCCModCreatorDoc::launch()
{
	int error = m_mod.activate();
	if (!error)
		m_mod.launch_game(false);
	return error;
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

Cxcc_mod::t_file_properties CXCCModCreatorDoc::file_properties(Cxcc_mod::t_category_type category, string fname) const
{
	return m_mod.file_properties(category, fname);
}

void CXCCModCreatorDoc::file_properties(Cxcc_mod::t_category_type category, string fname, Cxcc_mod::t_file_properties properties)
{
	m_mod.file_properties(category, fname, properties);
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

int CXCCModCreatorDoc::add_mode(string name)
{
	return m_mod.add_mode(name);
}

int CXCCModCreatorDoc::add_module(string name)
{
	return m_mod.add_module(name);
}