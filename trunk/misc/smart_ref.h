// smart_ref.h: interface for the Csmart_ref class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMART_REF_H__B515E7F7_D780_4F96_B252_2574DB328E4D__INCLUDED_)
#define AFX_SMART_REF_H__B515E7F7_D780_4F96_B252_2574DB328E4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Csmart_ref_base
{
public:
	Csmart_ref_base* attach()
	{
		mc_references++;
		return this;
	}

	void detach()
	{
		if (!--mc_references)
			delete this;
	}

	Csmart_ref_base()
	{
		mc_references = 0;
	}
	
	virtual ~Csmart_ref_base()
	{
	}
private:
	int mc_references;
};

template <class T>
class Csmart_ref: public Csmart_ref_base
{
public:
	static Csmart_ref_base* create(const T& d)
	{
		return new Csmart_ref(d);
	}

	Csmart_ref(const T& d)
	{
		m_d = d;
	}
private:
	T m_d;
};

#endif // !defined(AFX_SMART_REF_H__B515E7F7_D780_4F96_B252_2574DB328E4D__INCLUDED_)
