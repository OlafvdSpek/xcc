#pragma once

#include "xd2_animation.h"
#include "xd2_shape.h"

class Cxd2_surface_base: public Csdl_surface
{
public:
	virtual SDL_Rect r(int i) const = 0;
};

class Cxd2_animation_surface: public Cxd2_surface_base
{
public:
	Cxd2_animation_surface();
	Cxd2_animation_surface(const Cxd2_animation& animation, SDL_Color* p);	

	SDL_Rect r(int i) const
	{
		return Csdl_rect(i % m_ca * m_cx, i / m_ca * m_cy, m_cx, m_cy);
	}
private:
	int m_ca;
	int m_cx;
	int m_cy;
};

class Cxd2_shape_surface: public Cxd2_surface_base
{
public:
	Cxd2_shape_surface();
	Cxd2_shape_surface(const Cxd2_shape& shape, SDL_Color* p);

	virtual SDL_Rect r(int i) const
	{
		return m_vector[i];
	}
private:
	typedef vector<Csdl_rect> t_vector;

	t_vector m_vector;
};

class Cxd2_surface_cache  
{
public:
	const Cxd2_animation_surface& set(const Cxd2_animation& animation, SDL_Color* p);
	const Cxd2_shape_surface& set(const Cxd2_shape& shape, SDL_Color* p);
	Cxd2_surface_cache();

	const Cxd2_surface_base& get(const void* v) const
	{
		return *m_map.find(v)->second;
	}

	bool has(const void* v) const
	{
		return m_map.find(v) != m_map.end();
	}
private:
	typedef map<const void*, Cxd2_surface_base*> t_map;

	t_map m_map;
};
