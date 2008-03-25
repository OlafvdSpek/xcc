#pragma once

#include "xif_key.h"

class CXIFEditorDoc : public CDocument
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CXIFEditorDoc)

public:

	//{{AFX_VIRTUAL(CXIFEditorDoc)
public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	Cxif_key& get_top()
	{
		return m_top;
	}

protected:

protected:
	//{{AFX_MSG(CXIFEditorDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cxif_key m_top;
};
