// ucr_container.h: interface for the Cucr_container class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCR_CONTAINER_H__3EF41799_3C8D_4C27_AC4E_EA4291EE49AD__INCLUDED_)
#define AFX_UCR_CONTAINER_H__3EF41799_3C8D_4C27_AC4E_EA4291EE49AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ucr_format.h"
#include "ucr_object.h"

class Cucr_container  
{
public:
	virtual int open(const Cvirtual_binary& d) = 0;
	virtual void close() = 0;
	virtual int size() const = 0;
	virtual const Cucr_object& operator[](int i) const = 0;

	virtual ~Cucr_container()
	{
	}
};

template <class T>
class Cucr_container_template: public Cucr_container
{
public:
	void close()
	{
		m_objects.clear();
	}

	int size() const
	{
		return m_objects.size();
	}

	const const Cucr_object& operator[](int i) const
	{
		return m_objects[i];
	}
protected:
	typedef vector<T> t_objects;

	t_objects m_objects;
};

#endif // !defined(AFX_UCR_CONTAINER_H__3EF41799_3C8D_4C27_AC4E_EA4291EE49AD__INCLUDED_)
