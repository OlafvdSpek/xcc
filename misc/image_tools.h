/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

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

#include <palet.h>

void resize_image_down(const byte* s, byte* d, int cx, int cy, int c_planes, int cx_d, int cy_d);
void resize_image_up(const byte* s, byte* d, int cx, int cy, int c_planes, int cx_d, int cy_d);
void resize_image_down(const t_palet32entry* s, t_palet32entry* d, int cx, int cy, int cx_d, int cy_d);
void resize_image_up(const t_palet32entry* s, t_palet32entry* d, int cx, int cy, int cx_d, int cy_d);