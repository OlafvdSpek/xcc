#include "stdafx.h"
#include "xd2_surface_cache.h"

Cxd2_animation_surface::Cxd2_animation_surface()
{
	m_ca = m_cx = m_cy = 0;
}

Cxd2_animation_surface::Cxd2_animation_surface(const Cxd2_animation& animation, SDL_Color* p)
{
	int max_cy = 2048 / animation.cy() * animation.cy();
	int ca = (animation.cf() * animation.cy() + max_cy - 1) / max_cy;
	int cb = (animation.cf() + ca - 1) / ca;
	Csdl_surface surface1 = SDL_CreateRGBSurface(0, ca * animation.cx(), cb * animation.cy(), 8, 0, 0, 0, 0);
	if (!surface1)
		return;
	SDL_SetPalette(surface1, SDL_LOGPAL, p, 0, 0x100);
	if (SDL_LockSurface(surface1))
		return;
	for (int i = 0; i < animation.cf(); i++)
	{
		const byte* r = animation.d(i);
		byte* w = reinterpret_cast<byte*>(surface1->pixels) + i % ca * animation.cx() + i / ca * surface1->pitch * animation.cy();
		for (int y = 0; y < animation.cy(); y++)
		{
			memcpy(w, r, animation.cx());
			r += animation.cx();
			w += surface1->pitch;
		}
	}
	SDL_UnlockSurface(surface1);
	m_source = SDL_DisplayFormat(surface1);
	m_ca = ca;
	m_cx = animation.cx();
	m_cy = animation.cy();
}

Cxd2_shape_surface::Cxd2_shape_surface()
{
}

Cxd2_shape_surface::Cxd2_shape_surface(const Cxd2_shape& shape, SDL_Color* p)
{
	typedef multimap<int, int, greater<int> > t_map;

	t_map map;
	int x = 0;
	int y = 2048;
	int cx = 0;
	int cy = 0;
	{
		for (int i = 0; i < shape.size(); i++)
			map.insert(t_map::value_type(shape.get(i).cx(), i));
	}
	t_map::const_iterator i;
	for (i = map.begin(); i != map.end(); i++)
	{
		const Cxd2_image& image = shape.get(i->second);
		if (y + image.cy() > 2048)
		{
			cy = max(cy, y);
			x = cx;
			y = 0;
			cx = x + image.cx();
		}
		y += image.cy();
	}
	Csdl_surface surface1 = SDL_CreateRGBSurface(0, cx, cy, 8, 0, 0, 0, 0);
	if (!surface1)
		return;
	SDL_SetPalette(surface1, SDL_LOGPAL, p, 0, 0x100);
	if (SDL_LockSurface(surface1))
		return;
	x = 0;
	y = 2048;
	cx = 0;
	m_vector.resize(shape.size());
	for (i = map.begin(); i != map.end(); i++)
	{
		const Cxd2_image& image = shape.get(i->second);
		if (y + image.cy() > 2048)
		{
			x = cx;
			y = 0;
			cx = x + image.cx();
		}
		{
			const byte* r = image.d();
			byte* w = reinterpret_cast<byte*>(surface1->pixels) + x + surface1->pitch * y;
			for (int y = 0; y < image.cy(); y++)
			{
				memcpy(w, r, image.cx());
				r += image.cx();
				w += surface1->pitch;
			}
		}
		m_vector[i->second] = Csdl_rect(x, y, image.cx(), image.cy());
		y += image.cy();
	}
	SDL_UnlockSurface(surface1);
	m_source = SDL_DisplayFormat(surface1);
}


Cxd2_surface_cache::Cxd2_surface_cache()
{
}

const Cxd2_animation_surface& Cxd2_surface_cache::set(const Cxd2_animation& animation, SDL_Color* p)
{
	if (has(&animation))
		return *reinterpret_cast<const Cxd2_animation_surface*>(&get(&animation));
	auto_ptr<Cxd2_animation_surface> surface(new Cxd2_animation_surface(animation, p));
	if (*surface)
	{
		m_map[&animation] = surface.get();
		return *surface.release();
	}
	static Cxd2_animation_surface z;
	return z;
}

const Cxd2_shape_surface& Cxd2_surface_cache::set(const Cxd2_shape& shape, SDL_Color* p)
{
	if (has(&shape))
		return *reinterpret_cast<const Cxd2_shape_surface*>(&get(&shape));
	auto_ptr<Cxd2_shape_surface> surface(new Cxd2_shape_surface(shape, p));
	if (*surface)
	{
		m_map[&shape] = surface.get();
		return *surface.release();
	}
	static Cxd2_shape_surface z;
	return z;
}