#include "stdafx.h"
#include "palet_filter.h"

#include "fname.h"

int Cpalet_filter::Clist_entry::q(t_file_type ft, int cx, int cy, string fname) const
{
	int r = 0;
	if (m_ft == ft)
		r += 2;
	if (!m_cx)
		r++;
	else if (m_cx == cx)
		r += 2;
	if (!m_cy)
		r++;
	else if (m_cy == cy)
		r += 2;
	if (m_fname.empty())
		r++;
	else if (fname_filter(fname, m_fname))
		r += 2;
	return r;
}

Cpalet_filter::Cpalet_filter()
{
	m_list.push_back(Clist_entry(game_td, "desert.pal", ft_shp, "*.des"));
	m_list.push_back(Clist_entry(game_td, "temperat.pal", ft_shp, "*.tem"));
	m_list.push_back(Clist_entry(game_td, "winter.pal", ft_shp, "*.win"));

	m_list.push_back(Clist_entry(game_ts, "cameo.pal", ft_shp_ts, "*icon*", 64, 48));
	m_list.push_back(Clist_entry(game_ts, "dropship.pal", ft_shp_ts, "drop000?*"));
	m_list.push_back(Clist_entry(game_ts, "isosno.pal", ft_tmp_ts, "*.sno", 48, 24));
	m_list.push_back(Clist_entry(game_ts, "isotem.pal", ft_tmp_ts, "*.tem", 48, 24));
	m_list.push_back(Clist_entry(game_ts, "unitsno.pal", ft_shp_ts, "*.sno"));
	m_list.push_back(Clist_entry(game_ts, "unittem.pal", ft_shp_ts));
	m_list.push_back(Clist_entry(game_ts, "unittem.pal", ft_shp_ts, "*.tem"));

	m_list.push_back(Clist_entry(game_ts, "mousepal.pal", ft_shp_ts, "mouse*", 55, 43));

	m_list.push_back(Clist_entry(game_ra2, "cameo.pal", ft_shp_ts, "*icon*", 60, 48));
	m_list.push_back(Clist_entry(game_ra2, "isosno.pal", ft_tmp_ts, "*.sno", 60, 30));
	m_list.push_back(Clist_entry(game_ra2, "isotem.pal", ft_tmp_ts, "*.tem", 60, 30));
	m_list.push_back(Clist_entry(game_ra2, "isourb.pal", ft_tmp_ts, "*.urb", 60, 30));
	m_list.push_back(Clist_entry(game_ra2, "unitsno.pal", ft_shp_ts, "*.sno"));
	m_list.push_back(Clist_entry(game_ra2, "unittem.pal", ft_shp_ts));
	m_list.push_back(Clist_entry(game_ra2, "unittem.pal", ft_shp_ts, "*.tem"));
	m_list.push_back(Clist_entry(game_ra2, "uniturb.pal", ft_shp_ts, "*.urb"));

	m_list.push_back(Clist_entry(game_ra2, "gls.pal", ft_shp_ts, "gls?.*"));
	m_list.push_back(Clist_entry(game_ra2, "grfxtxt.pal", ft_shp_ts, "grfxtxt*"));
	m_list.push_back(Clist_entry(game_ra2, "ldscrna.pal", ft_shp_ts, "ls??0a??*", 640, 400));
	m_list.push_back(Clist_entry(game_ra2, "ldscrna.pal", ft_shp_ts, "ls??0a??*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ldscrna.pal", ft_shp_ts, "ls??0b??*"));
	m_list.push_back(Clist_entry(game_ra2, "ldscrns.pal", ft_shp_ts, "ls??0s??*", 640, 400));
	m_list.push_back(Clist_entry(game_ra2, "ldscrns.pal", ft_shp_ts, "ls??0s??*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "mousepal.pal", ft_shp_ts, "mouse*", 55, 43));
	m_list.push_back(Clist_entry(game_ra2, "mpls.pal", ft_shp_ts, "ls??0*", 640, 480));
	m_list.push_back(Clist_entry(game_ra2, "mpls.pal", ft_shp_ts, "ls??0*", 800, 600));

	m_list.push_back(Clist_entry(game_ra2, "glsmd.pal", ft_shp_ts, "glslmd.*"));
	m_list.push_back(Clist_entry(game_ra2, "isodes.pal", ft_tmp_ts, "*.des", 60, 30));
	m_list.push_back(Clist_entry(game_ra2, "isolun.pal", ft_tmp_ts, "*.lun", 60, 30));
	m_list.push_back(Clist_entry(game_ra2, "isoubn.pal", ft_tmp_ts, "*.ubn", 60, 30));

	m_list.push_back(Clist_entry(game_ra2, "ls800a01.pal", ft_shp_ts, "ls800a01*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800a02.pal", ft_shp_ts, "ls800a02*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800a03.pal", ft_shp_ts, "ls800a03*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800a04.pal", ft_shp_ts, "ls800a04*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800a05.pal", ft_shp_ts, "ls800a05*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800a06.pal", ft_shp_ts, "ls800a06*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800a07.pal", ft_shp_ts, "ls800a07*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800ca.pal", ft_shp_ts, "ls800ca*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "ls800cs.pal", ft_shp_ts, "ls800cs*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "ls800cwa.pal", ft_shp_ts, "ls800cwa*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "ls800cy.pal", ft_shp_ts, "ls800cy*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "ls800s01.pal", ft_shp_ts, "ls800s01*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800s02.pal", ft_shp_ts, "ls800s02*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800s03.pal", ft_shp_ts, "ls800s03*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800s04.pal", ft_shp_ts, "ls800s04*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800s05.pal", ft_shp_ts, "ls800s05*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800s06.pal", ft_shp_ts, "ls800s06*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "ls800s07.pal", ft_shp_ts, "ls800s07*", 800, 520));
	m_list.push_back(Clist_entry(game_ra2, "mplsc.pal", ft_shp_ts, "ls800cuba*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "mplsf.pal", ft_shp_ts, "ls800france*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "mplsg.pal", ft_shp_ts, "ls800germany*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "mplsi.pal", ft_shp_ts, "ls800iraq*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "mplsk.pal", ft_shp_ts, "ls800korea*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "mplsl.pal", ft_shp_ts, "ls800libya*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "mplsobs.pal", ft_shp_ts, "ls800obs*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "mplsr.pal", ft_shp_ts, "ls800russia*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "mplsu.pal", ft_shp_ts, "ls800ustates*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "mplsuk.pal", ft_shp_ts, "ls800ukingdom*", 800, 600));
	m_list.push_back(Clist_entry(game_ra2, "mpyls.pal", ft_shp_ts, "ls800yuri*", 800, 600));
}

void Cpalet_filter::select(t_file_type ft, int cx, int cy, string fname)
{
	m_vector.clear();
	int best_q = INT_MIN;
	for (auto& i : m_list)
	{
		int q = i.q(ft, cx, cy, fname);
		if (q < best_q)
			continue;
		if (q > best_q)
			m_vector.clear();
		best_q = q;
		m_vector.push_back(&i);
	}
	m_vector_i = m_vector.begin();
}


string Cpalet_filter::pick(t_game& game)
{
	if (m_vector.empty())
		return "";
	t_list::const_pointer i = *m_vector_i++;
	if (m_vector_i == m_vector.end())
		m_vector_i = m_vector.begin();
	game = i->game();
	return i->palet();
}