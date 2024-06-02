/*
* Descent 3 
* Copyright (C) 2024 Parallax Software
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.

--- HISTORICAL COMMENTS FOLLOW ---

 * $Logfile: /DescentIII/Main/grtext/grtextlib.h $
 * $Revision: 2 $
 * $Date: 4/27/98 3:46p $
 * $Author: Samir $
 *
 *
 *
 * $Log: /DescentIII/Main/grtext/grtextlib.h $
 *
 * 2     4/27/98 3:46p Samir
 * scaling fonts.
 *
 * 1     12/29/97 3:24p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#ifndef GRTEXTLIB_H
#define GRTEXTLIB_H

#include <cstdint>

struct tCharBlt {
  uint16_t ch;
  uint16_t clipped; // if =1, use sx,sy,sw,sh
  int x, y;
  float dsw, dsh; // scale vertical and horiz.
  int sx, sy;     // source rectangle within character in pixels.
  int sw, sh;
};

//	render a character
int grfont_BltChar(int font, tCharBlt *cbi);

#endif
