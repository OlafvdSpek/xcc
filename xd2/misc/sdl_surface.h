#pragma once

class Csdl_surface
{
public:
	void clear();
	const Csdl_surface& operator=(const Csdl_surface&);
	Csdl_surface(const Csdl_surface&);

	operator SDL_Surface*() const
	{
		return m_source;
	}

	SDL_Surface* operator->() const
	{
		return m_source;
	}

	Csdl_surface(SDL_Surface* v = NULL)
	{
		m_source = v;
	}

	~Csdl_surface()
	{
		SDL_FreeSurface(m_source);
	}
protected:
	SDL_Surface* m_source;
};
