// sdl_surface.h: interface for the Csdl_surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDL_SURFACE_H__212BAE40_65D1_11D7_B607_0000C006A2C2__INCLUDED_)
#define AFX_SDL_SURFACE_H__212BAE40_65D1_11D7_B607_0000C006A2C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Csdl_surface
{
public:
	void clear();
	const Csdl_surface& operator=(const Csdl_surface& v);
	Csdl_surface(const Csdl_surface& v);

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

#endif // !defined(AFX_SDL_SURFACE_H__212BAE40_65D1_11D7_B607_0000C006A2C2__INCLUDED_)
