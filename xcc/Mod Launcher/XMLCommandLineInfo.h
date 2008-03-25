#pragma once

class CXMLCommandLineInfo: public CCommandLineInfo  
{
public:
	virtual void ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast);
	void ParseParamFlag(const char* pszParam);
	CXMLCommandLineInfo();

	bool m_activate;
};
