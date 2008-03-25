#pragma once

#include "xif_key_r.h"

class CXCCGameSpyPlayerDoc : public CDocument
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CXCCGameSpyPlayerDoc)

public:
	const Cxif_key_r& key() const
	{
		return m_key;
	}

public:

	//{{AFX_VIRTUAL(CXCCGameSpyPlayerDoc)
public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:

protected:

protected:
	//{{AFX_MSG(CXCCGameSpyPlayerDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Cxif_key_r m_key;
};
