// XCC MixerDoc.cpp : implementation of the CXCCMixerDoc class
//

#include "stdafx.h"
#include "XCC Mixer.h"

#include "XCC MixerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerDoc

IMPLEMENT_DYNCREATE(CXCCMixerDoc, CDocument)

BEGIN_MESSAGE_MAP(CXCCMixerDoc, CDocument)
	//{{AFX_MSG_MAP(CXCCMixerDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerDoc construction/destruction

CXCCMixerDoc::CXCCMixerDoc()
{
}

CXCCMixerDoc::~CXCCMixerDoc()
{
}

BOOL CXCCMixerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CXCCMixerDoc serialization

void CXCCMixerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerDoc diagnostics

#ifdef _DEBUG
void CXCCMixerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXCCMixerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXCCMixerDoc commands
