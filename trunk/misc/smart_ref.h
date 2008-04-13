#pragma once

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
