#pragma once

#include "xif_key_r.h"

class CXCCGameSpyPlayerDoc : public CDocument
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CXCCGameSpyPlayerDoc)
public:
	virtual void Serialize(CArchive& ar);

	const Cxif_key_r& key() const
	{
		return m_key;
	}
protected:
	DECLARE_MESSAGE_MAP()
private:
	Cxif_key_r m_key;
};
