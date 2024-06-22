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
*/

#ifndef MOVIE_H__
#define MOVIE_H__

#include "renderer.h"

#include <cstdint>

#define MVELIB_NOERROR 0
#define MVELIB_FILE_ERROR -1
#define MVELIB_NOTINIT_ERROR -2
#define MVELIB_DDGR_ERROR -3
#define MVELIB_INIT_ERROR -4
#define MVELIB_PLAYBACK_ERROR -5
#define MVELIB_PLAYBACK_ABORTED -6

class oeApplication;

int mve_Init(const char *dir, const char *sndcard);

// simply plays a movie.
int mve_PlayMovie(const char *mvename);

// used to copy movie data to a pointer, looping will loop, fhandle will be a pointer to a file handle to be returned
// handle to movie sequence is returned by function.
intptr_t mve_SequenceStart(const char *mvename, int *fhandle, bool looping = false);

//	frames movies started with SequenceStart.  Optionally, pass a pointer to a variable which will receive
//	bitmap handle containing data, nx and ny will contain adjusted x and y coordinates if needed.
//	passing -1 to x and y centers the frame on that axis
//	handle is the movie handle returned by mve_Sequence start
//	returned value is the handle passed into mve_SequenceFrame or new one if movie looped.
intptr_t mve_SequenceFrame(intptr_t handle, int fhandle, bool sequence, int *bm_handle);

bool mve_SequenceClose(intptr_t handle, int fhandle);

//	sets render frame boundaries.
void mve_SetRenderProperties(int16_t x, int16_t y, int16_t w, int16_t h, renderer_type type, bool hicolor);

// called every frame.
typedef void (*MovieFrameCallback_fp)(int x, int y, int movieFrameNum);
void mve_SetCallback(MovieFrameCallback_fp callBack);

// call to print out text.
void mve_Puts(int16_t x, int16_t y, ddgr_color col, const char *txt);

void mve_ClearRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

#endif
