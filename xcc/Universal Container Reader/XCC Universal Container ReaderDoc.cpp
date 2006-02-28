// XCC Universal Container ReaderDoc.cpp : implementation of the CXCCUniversalContainerReaderDoc class
//

#include "stdafx.h"
#include "XCC Universal Container Reader.h"

#include "XCC Universal Container ReaderDoc.h"
#include "formats_dlg.h"
#include "ucr_container_ws_ra_mix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCUniversalContainerReaderDoc

IMPLEMENT_DYNCREATE(CXCCUniversalContainerReaderDoc, CDocument)

BEGIN_MESSAGE_MAP(CXCCUniversalContainerReaderDoc, CDocument)
	//{{AFX_MSG_MAP(CXCCUniversalContainerReaderDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCUniversalContainerReaderDoc construction/destruction

CXCCUniversalContainerReaderDoc::CXCCUniversalContainerReaderDoc()
{
	m_container = NULL;
}

CXCCUniversalContainerReaderDoc::~CXCCUniversalContainerReaderDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
// CXCCUniversalContainerReaderDoc commands

BOOL CXCCUniversalContainerReaderDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (m_container)
		delete m_container;
	/*
	Cformats_dlg dlg(app()->formats());
	{
		const char* p = strrchr(lpszPathName, '.');
		if (p)
			dlg.hint_extension(p + 1);
	}
	if (IDOK != dlg.DoModal())
		return false;
	*/
	assert(app()->mru_format());
	m_container = new Cucr_container_simple(*app()->mru_format());
	// m_container = new Cucr_container_ws_ra_mix;
	int error = m_container->open(Cvirtual_binary(lpszPathName));
	// ReportSaveLoadException(lpszPathName, &fe, FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
	return !error;
}
