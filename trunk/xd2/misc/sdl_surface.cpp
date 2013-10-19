#include "sdl_surface.h"

Csdl_surface::Csdl_surface(const Csdl_surface& v)
{
	m_source = v.m_source ? v.m_source->refcount++, v.m_source : NULL;
}

const Csdl_surface& Csdl_surface::operator=(const Csdl_surface& v)
{
	if (this != &v)
	{
		SDL_FreeSurface(m_source);
		m_source = v.m_source ? v.m_source->refcount++, v.m_source : NULL;
	}
	return *this;
}

void Csdl_surface::clear()
{
	SDL_FreeSurface(m_source);
	m_source = NULL;
}