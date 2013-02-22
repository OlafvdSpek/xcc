#include "stdafx.h"
#include "object.h"
#include "seed_decoder.h"
#include "xd2_files.h"
#include "xd2_surface_cache.h"

Cxd2_files g_files;
const Cxd2_animation* g_icons;
const __int16* g_icon_map;
SDL_Color g_palet[0x100];
SDL_Surface* g_screen;
Cxd2_surface_cache g_surface_cache;
int view_x = 32 << 4;
int view_y = 32 << 4;

map<string, Chouse> g_houses;
map<string, Cobject_type> m_object_types;
list<Cobject> m_objects;
map<string, Cplayer> m_players;

void load_palet(const string& name, SDL_Color* colors)
{
	const shared_data& palet = g_files.data_map()[name];
	SDL_Color* w = colors;
	for (const byte* r = palet.data(); r < palet.end(); r += 3)
		*w++ = Csdl_color(r[0], r[1], r[2]);
}

void draw_image(const byte* d, int x, int y, int cx, int cy)
{
	Csdl_surface surface = SDL_CreateRGBSurfaceFrom(const_cast<byte*>(d), cx, cy, 8, cx, 0, 0, 0, 0);
	if (!surface)
		return;
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY, 0);
	SDL_SetPalette(surface, SDL_LOGPAL, g_palet, 0, 0x100);
	SDL_BlitSurface(surface, NULL, g_screen, &Csdl_rect(x, y));
}

void draw_image32(const byte* d, int x, int y, int cx, int cy)
{
	Csdl_surface surface = SDL_CreateRGBSurfaceFrom(const_cast<byte*>(d), cx, cy, 32, cx << 2, g_screen->format->Rmask, g_screen->format->Gmask, g_screen->format->Bmask, 0);
	if (surface)
		SDL_BlitSurface(surface, NULL, g_screen, &Csdl_rect(x, y));
}

void draw(const Cxd2_surface_base& s, int i, int x, int y)
{
	if (SDL_BlitSurface(s, &s.r(i), g_screen, &Csdl_rect(x, y)))
		throw runtime_error("SDL_BlitSurface()");
}

void draw(const Cxd2_animation& a, int i, int x, int y)
{
	draw(g_surface_cache.set(a, g_palet), i, x, y);
}

void draw(const Cxd2_shape& s, int i, int x, int y)
{
	draw(g_surface_cache.set(s, g_palet), i, x, y);
}

void draw_building(int i, int _x, int _y, int cx, int cy)
{
	for (int y = 0; y < cy; y++)
	{
		for (int x = 0; x < cx; x++)
			draw(*g_icons, g_icon_map[i++], _x + (x << 4),  _y + (y << 4));
	}
}

void show_animation(const Cxd2_animation& animation)
{
	for (int i = 0; i < animation.cf(); i++)
	{
		Csdl_surface surface = SDL_CreateRGBSurfaceFrom(const_cast<byte*>(animation.d(i)), animation.cx(), animation.cy(), 8, animation.cx(), 0, 0, 0, 0);
		if (!surface)
			return;
		SDL_SetPalette(surface, SDL_LOGPAL, g_palet, 0, 0x100);
		SDL_FillRect(g_screen, NULL, SDL_MapRGB(g_screen->format, 0, 0, 0));
		SDL_BlitSurface(surface, NULL, g_screen, NULL);
		SDL_Flip(g_screen);
	}
}

void show_animation(const string& name)
{
	show_animation(g_files.animations()[name]);
}

void show_image(const Cxd2_image& image, int x = 0, int y = 0)
{
	draw_image(image.d(), x, y, image.cx(), image.cy());
}

void show_image(const string& name)
{
	show_image(g_files.images()[name]);
}

void show_number(int x, int y, int n)
{
	x += 80;
	do
	{
		x -= 8;
		draw(g_files.shapes2(), n % 10 + 14, x, y);
		n /= 10;
	}
	while (n);
}

void show_fps()
{
	static int i = 0;
	static int t0 = time(NULL);
	int t = time(NULL) - t0;
	show_number(0, 100, i++);
	show_number(0, 108, t);
	if (t)
		show_number(0, 116, i / t);
}

void draw_map(const byte* _map)
{
	SDL_FillRect(g_screen, NULL, SDL_MapRGB(g_screen->format, 0, 0, 0));
	int x0 = g_screen->w / 2 - view_x;
	int y0 = g_screen->h / 2 - view_y;
	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
			draw(*g_icons, _map[x | y << 6], (x << 4) + x0, (y << 4) + y0);
	}
}

void draw_buildings()
{
	if (1)
	{
		struct t_building
		{
			int cx;
			int cy;
			int cf;
		} buildings[] =
		{
			3, 3, 4,
			2, 2, 6,
			3, 2, 8,
			3, 2, 8,
			2, 2, 4,
			2, 2, 4,
			2, 2, 4,
			2, 2, 4,
			2, 2, 4,
			3, 3, 10,
			3, 2, 10,
			3, 2, 10,
			1, 1, 10,
			1, 1, 10,
			2, 2, 4,
			2, 2, 6,
			0
		};
		int icon = 0xb;
		int y = 0;
		for (const t_building* r = buildings; r->cx; r++)
		{
			for (int i = 0; i < r->cf; i++)
				draw_building(g_icon_map[icon] + i * r->cx * r->cy, i * (r->cx + 1) << 4, y, r->cx, r->cy);
			icon++;
			y += (r->cy + 1) << 4;
		}
	}
	int y = 0;
	for (auto& i : m_object_types)
	{
		if (!i.second.body)
			continue;
		int x = 640;
		for (int j = 0; j < 5; j++)
		{
			const Cxd2_image& image = g_files.shape(i.second.body + j);
			show_image(image, x, y);
			if (i.second.turret != -1)
			{
				const Cxd2_image& image = g_files.shape(i.second.turret + j);
				show_image(image, x, y);
			}
			x += image.cx() + 4;
		}
		y += g_files.shape(i.second.body + 5).cy() + 4;
	}
}

void draw_objects()
{
	int x0 = g_screen->w / 2 - view_x;
	int y0 = g_screen->h / 2 - view_y;
	for (auto& i : m_objects)
	{
		int x = i.l().x * 16 / 256 + x0;
		int y = i.l().y * 16 / 256 + y0;
		if (i.t().clas == oc_structure)
		{
			int f = 2;
			int cx = i.t().cx;
			int cy = i.t().cy;
			x -= 8;
			y -= 8;
			// draw_building(g_icon_map[icon] + i * r->cx * r->cy, i * (r->cx + 1) << 4, y, r->cx, r->cy);
			draw_building(g_icon_map[i.t().icon] + f * cx * cy, x, y, cx, cy);
		}
		else
		{
			int j = 0;
			const Cxd2_image& image = g_files.shape(i.t().body + j);
			x -= image.cx() / 2;
			y -= image.cy() / 2;
			show_image(image, x, y);
			if (i.t().turret != -1)
			{
				const Cxd2_image& image = g_files.shape(i.t().turret + j);
				show_image(image, x, y);
			}
		}
	}
}

void draw_minimap(const shared_data& minimap)
{
	static Csdl_surface surface = SDL_DisplayFormat(Csdl_surface(SDL_CreateRGBSurfaceFrom(const_cast<byte*>(minimap.data()), 64, 64, 32, 64 << 2, g_screen->format->Rmask, g_screen->format->Gmask, g_screen->format->Bmask, 0)));
	SDL_BlitSurface(surface, NULL, g_screen, &Csdl_rect(g_screen->w - 64, g_screen->h - 64));
}

void draw_sidebar(int x, int y, bool structures)
{
	for (auto& i : m_object_types)
	{
		if (!i.second.cameo || i.second.clas != oc_structure)
			continue;
		const Cxd2_image& image = g_files.shape(i.second.cameo);
		draw(g_files.shapes2(), i.second.cameo, x, y);
		y += image.cy() + 4;
	}
}

void draw_sidebar()
{
	int x = g_screen->w;
	draw_sidebar(x - 32, 0, true);
	draw_sidebar(x - 68, 0, false);
}

int get_icon_minimap_color(int i)
{
	int red = 0;
	int green = 0;
	int blue = 0;
	const int c = g_icons->cx() * g_icons->cy();
	const byte* r = g_icons->d(i);
	for (int j = 0; j < c; j++)
	{
		SDL_Color v = g_palet[*r++];
		red += v.r;
		green += v.g;
		blue += v.b;
	}
	return SDL_MapRGB(g_screen->format, red / c, green / c, blue / c);
}

shared_data create_minimap(const byte* s)
{
	shared_data d(0x4000);
	int* w = reinterpret_cast<int*>(d.data());
	for (int i = 0; i < 0x1000; i++)
		*w++ = get_icon_minimap_color(s[i]);
	return d;
}

template<class T>
void read_config(const string& dir, T& v)
{
	WIN32_FIND_DATA fd;
	HANDLE h = FindFirstFile((dir + "/*.ini").c_str(), &fd);
	if (h == INVALID_HANDLE_VALUE)
		return;
	do
	{
		ifstream f(dir + "/" + fd.cFileName);
		map<string, string> d;
		for (string s; getline(f, s); )
		{
			size_t i = s.find(';');
			if (i != string::npos)
				s.erase(i);
			i = s.find('=');
			if (i == string::npos)
				continue;
			d[trim_copy(s.substr(0, i))] = trim_copy(s.substr(i + 1));
		}
		string& code = d["code"] = fd.cFileName;
		code.erase(code.rfind('.'));
		v[code] = d;
	}
	while (FindNextFile(h, &fd));
	FindClose(h);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	read_config("dune/houses", g_houses);
	read_config("dune/players", m_players);
	read_config("dune/objects", m_object_types);
	{
		Cxif_key_r key;
		if (key.import(file_get("c:/vc/xd2/xd2 files.xif")) || g_files.load(key))
			return 1;
	}
	if (SDL_Init(SDL_INIT_VIDEO))
		return 1;
	SDL_WM_SetCaption("XD2", NULL);
#ifdef NDEBUG
	g_screen = SDL_SetVideoMode(0, 0, 32, SDL_DOUBLEBUF | SDL_FULLSCREEN | SDL_HWSURFACE);
#else
	g_screen = SDL_SetVideoMode(1280, 1024, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_RESIZABLE);
#endif
	if (!g_screen)
		return 1;
	const SDL_VideoInfo* vi = SDL_GetVideoInfo();
	load_palet("ibm.pal", g_palet);
	g_icons = &g_files.animations()["icon.icn"];
	shared_data map(0x1000);
	{
		const __int16* s = g_icon_map = reinterpret_cast<const __int16*>(g_files.data_map()["icon.map"].data());
		s += s[9];
		Cseed_decoder::decode(392, map.data());
		byte* w = map.data();
		for (int i = 0; i < 0x1000; i++)
			w[i] = s[w[i]];
	}
	m_objects.push_back(Cobject(0, 0, find_ref(m_players, "goodguy"), find_ref(m_object_types, "mcv")));
	m_objects.push_back(Cobject(1, 0, find_ref(m_players, "goodguy"), find_ref(m_object_types, "const yard")));
	shared_data minimap = create_minimap(map.data());
	while (1)
	{
		draw_map(map.data());
		// draw_buildings();
		draw_objects();
		draw_sidebar();
		draw_minimap(minimap);
		// show_fps();
		SDL_Flip(g_screen);
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return 0;
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_RIGHT:
					if (event.button.x >= g_screen->w - 64 && event.button.x < g_screen->w
						&& event.button.y >= g_screen->h - 64 && event.button.y < g_screen->h)
					{
						view_x = (event.button.x - g_screen->w + 64) << 4;
						view_y = (event.button.y - g_screen->h + 64) << 4;
					}
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.state & SDL_BUTTON(3)
					&& event.motion.x >= g_screen->w - 64 && event.motion.x < g_screen->w
					&& event.motion.y >= g_screen->h - 64 && event.motion.y < g_screen->h)
				{
					view_x = (event.motion.x - g_screen->w + 64) << 4;
					view_y = (event.motion.y - g_screen->h + 64) << 4;
				}
				break;
			case SDL_VIDEORESIZE:
				g_screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_RESIZABLE);
				break;
			case SDL_QUIT:
				return 0;
				break;
			}
		}
		for (auto& i : m_objects)
			i.tick();
	}
	SDL_Quit();
	return 0;
}
