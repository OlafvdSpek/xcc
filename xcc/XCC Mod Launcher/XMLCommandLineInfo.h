// XMLCommandLineInfo.h: interface for the CXMLCommandLineInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLCOMMANDLINEINFO_H__A565D635_3941_4A01_9812_13BAE4785048__INCLUDED_)
#define AFX_XMLCOMMANDLINEINFO_H__A565D635_3941_4A01_9812_13BAE4785048__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXMLCommandLineInfo : public CCommandLineInfo  
{
public:
	virtual void ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast);
	void ParseParamFlag(const char* pszParam);
	CXMLCommandLineInfo();

	bool m_activate;
};

#endif // !defined(AFX_XMLCOMMANDLINEINFO_H__A565D635_3941_4A01_9812_13BAE4785048__INCLUDED_)
