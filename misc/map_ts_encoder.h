/*
    XCC Utilities and Library
    Copyright (C) 2001  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "ini_reader.h"
#include <virtual_binary.h>
#include "virtual_image.h"
#include "xif_key.h"

struct t_iso_map_pack_entry4
{
	__int16 tile;
	unsigned __int8 sub_tile;
	unsigned __int8 z;
};

class Cmap_ts_encoder : public Cini_reader
{
public:
	struct t_header
	{
		string description;
		string gamemode;
		int cx;
		int cy;
		int cmax_players;
	};

	void header(t_header v);
	int write_map(string fname, const string& ini);
	static bool wrong_version(const Cxif_key& k);
	static void write_map(ostream& os, const Cxif_key& k, const Cvirtual_binary palet);
	static bool write_mmx(const Cxif_key& k);
	static void write_pkt(ostream& os, const Cxif_key& k, string title);
	int process_section_start(string_view) override;
	bool process_section() const override;
	int process_key(string_view, string_view) override;
	void process_section_end() override;
	void encode(const Cvirtual_binary palet);
	Cvirtual_image create_heightmap() const;
	Cvirtual_image create_preview() const;
	void extract_map(t_iso_map_pack_entry4* d) const;
	Cmap_ts_encoder(ostream& f, bool encode4);

	Cvirtual_binary iso_map_pack() const
	{
		return m_iso_map_pack;
	}

	Cvirtual_binary overlay_pack() const
	{
		return m_overlay_pack;
	}

	Cvirtual_binary overlay_data_pack() const
	{
		return m_overlay_data_pack;
	}

	Cvirtual_binary preview_pack() const
	{
		return m_preview_pack;
	}
private:
	void map_encode4(const void* s, void* d, int count);
	static void map_decode4(const void* s, void* d, int count, const t_header& header);
	int overlay_encode4(const byte* s, byte* d) const;
	static int overlay_decode4(const byte* s, byte* d, const t_header& header);
	static int overlay_data_decode4(const byte* s, byte* d, const byte* overlay, const t_header& header);
	ostream& m_f;
	Cvirtual_binary m_d;
	byte* m_w;
	bool m_encode4;
	string m_section_name;
	Cvirtual_binary m_iso_map_pack;
	Cvirtual_binary m_overlay_pack;
	Cvirtual_binary m_overlay_data_pack;
	Cvirtual_binary m_preview_pack;
	t_header m_header;
};
