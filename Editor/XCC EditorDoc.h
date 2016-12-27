#pragma once

#include "cc_file.h"
#include "xcc_level.h"

class CXCCEditorDoc : public CDocument
{
public:
	Cxcc_level level;
protected: // create from serialization only
	CXCCEditorDoc();
	DECLARE_DYNCREATE(CXCCEditorDoc)

public:
	long load(const Cvirtual_binary& bin, const Cvirtual_binary& ini);
	//{{AFX_VIRTUAL(CXCCEditorDoc)
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	virtual ~CXCCEditorDoc();
protected:
	//{{AFX_MSG(CXCCEditorDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
