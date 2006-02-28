// XMLCommandLineInfo.cpp: implementation of the CXMLCommandLineInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XMLCommandLineInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXMLCommandLineInfo::CXMLCommandLineInfo()
{
	m_activate = false;
}

void CXMLCommandLineInfo::ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast)
{
	if (bFlag)
		ParseParamFlag(pszParam);
	else
		ParseParamNotFlag(pszParam);
	ParseLast(bLast);
}

void CXMLCommandLineInfo::ParseParamFlag(const char* pszParam)
{
	if (!strcmp(pszParam, "-activate"))
		m_activate = true;
	else
		CCommandLineInfo::ParseParamFlag(pszParam);
}