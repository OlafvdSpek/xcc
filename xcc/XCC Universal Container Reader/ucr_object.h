// ucr_object.h: interface for the Cucr_object class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCR_OBJECT_H__B3ED9475_E990_46F5_9D6F_DE9D2FAEDB01__INCLUDED_)
#define AFX_UCR_OBJECT_H__B3ED9475_E990_46F5_9D6F_DE9D2FAEDB01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Cucr_object  
{
public:
	Cucr_object();
	Cucr_object(const Cvirtual_binary& d, const string& name, int offset, int size);
	virtual ~Cucr_object();

	virtual Cvirtual_binary d() const
	{
		return Cvirtual_binary(m_d.data() + offset(), size(), Csmart_ref<Cvirtual_binary>::create(m_d));
	}

	const string& name() const
	{
		return m_name;
	}

	void name(const string& v)
	{
		m_name = v;
	}

	int offset() const
	{
		return m_offset;
	}

	void offset(int v)
	{
		m_offset = v;
	}

	int size() const
	{
		return m_size;
	}
protected:
	Cvirtual_binary m_d;
	string m_name;
	int m_offset;
	int m_size;
};

#endif // !defined(AFX_UCR_OBJECT_H__B3ED9475_E990_46F5_9D6F_DE9D2FAEDB01__INCLUDED_)
