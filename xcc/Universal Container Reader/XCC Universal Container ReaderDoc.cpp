#include "stdafx.h"
#include "XCC Universal Container Reader.h"

#include "XCC Universal Container ReaderDoc.h"
#include "formats_dlg.h"
#include "ucr_container_ws_ra_mix.h"

IMPLEMENT_DYNCREATE(CXCCUniversalContainerReaderDoc, CDocument)

BEGIN_MESSAGE_MAP(CXCCUniversalContainerReaderDoc, CDocument)
	//{{AFX_MSG_MAP(CXCCUniversalContainerReaderDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CXCCUniversalContainerReaderDoc::CXCCUniversalContainerReaderDoc()
{
	m_container = NULL;
}

CXCCUniversalContainerReaderDoc::~CXCCUniversalContainerReaderDoc()
{
}

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
