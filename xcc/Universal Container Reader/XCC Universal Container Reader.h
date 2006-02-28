// XCC Universal Container Reader.h : main header file for the XCC UNIVERSAL CONTAINER READER application
//

#if !defined(AFX_XCCUNIVERSALCONTAINERREADER_H__41459F30_D511_449B_8FF2_77188E355801__INCLUDED_)
#define AFX_XCCUNIVERSALCONTAINERREADER_H__41459F30_D511_449B_8FF2_77188E355801__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ucr_formats.h"
#include "ucr_library.h"

/////////////////////////////////////////////////////////////////////////////
// CXCCUniversalContainerReaderApp:
// See XCC Universal Container Reader.cpp for the implementation of this class
//

class CXCCUniversalContainerReaderApp : public CWinApp
{
public:
	static string data_fname();
	CXCCUniversalContainerReaderApp();

	const Cucr_format* mru_format() const
	{
		return m_mru_format;
	}

	const Cucr_formats& formats() const
	{
		return m_formats;
	}

	Cucr_library& library()
	{
		return m_library;
	}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXCCUniversalContainerReaderApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXCCUniversalContainerReaderApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	const Cucr_format* m_mru_format;
	Cucr_formats m_formats;
	Cucr_library m_library;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCCUNIVERSALCONTAINERREADER_H__41459F30_D511_449B_8FF2_77188E355801__INCLUDED_)
