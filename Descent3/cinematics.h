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

 * $Logfile: /DescentIII/main/cinematics.h $
 * $Revision: 7 $
 * $Date: 3/31/99 11:53a $
 * $Author: Samir $
 *
 *	D3 Cinematics interface with movie player
 *
 * $Log: /DescentIII/main/cinematics.h $
 *
 * 7     3/31/99 11:53a Samir
 * slow opengl code for movies.
 *
 * 6     3/17/99 4:18p Samir
 * redid movie code.
 *
 * 5     2/04/98 12:12p Samir
 * The movie frame interface now has an option to not advance to next
 * frame.
 *
 * 4     2/03/98 6:42p Samir
 * Movies in 3dfx mode.
 *
 * 3     9/19/97 2:34p Samir
 * Added movie frame management support.
 *
 * 2     9/12/97 4:12p Samir
 * first movie library
 *
 * $NoKeywords: $
 */

#ifndef CINEMATICS_H
#define CINEMATICS_H

#include "renderer.h"
#include "bitmap.h"

#include <cstdint>
#include <filesystem>

//	Movie Cinematic
struct tCinematic {
  intptr_t mvehandle;
  int filehandle;
  chunked_bitmap frame_chunk; // used internally, don't access.
};

bool InitCinematics();
void SetMovieProperties(int x, int y, int w, int h, renderer_type type);
bool PlayMovie(const std::filesystem::path &moviename);
tCinematic *StartMovie(const char *moviename, bool looping = false);
bool FrameMovie(tCinematic *mve, int x, int y, bool sequence = true);
void EndMovie(tCinematic *mve);

#endif
